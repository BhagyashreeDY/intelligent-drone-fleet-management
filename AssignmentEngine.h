#pragma once
#include <vector>
#include <algorithm>
#include <set>
#include <limits>
#include "Drone.h"
#include "Delivery.h"
#include "ConstraintManager.h"
#include "Logger.h"

struct OptimizationWeights {
    double distance = 1.0;
    double battery = 1.0;
    double priority = 1.0;
    double usage = 1.0;
};

class AssignmentEngine {
private:
    double droneSpeed = 12.0;

    double estimateTime(double distance) const {
        return distance / droneSpeed;
    }

    void displayScoreBreakdown(int droneId, double dist, double batt, int prio, int usage, const OptimizationWeights& w, double finalScore) const {
        std::cout << "[INTEL] Score Breakdown for Drone " << droneId << ":\n"
                  << "  - Distance Component: " << (w.distance * dist) << " (dist: " << dist << ")\n"
                  << "  - Battery Component : -" << (w.battery * batt) << " (batt: " << batt << "%)\n"
                  << "  - Priority Component: -" << (w.priority * prio) << " (prio: " << prio << ")\n"
                  << "  - Usage Penalty     : +" << (w.usage * usage) << " (deliveries: " << usage << ")\n"
                  << "  - Final Score       : " << finalScore << " (Lower is better)\n";
    }

public:
    bool assignDelivery(const std::vector<Drone*>& drones, Delivery& delivery, const ConstraintManager& cm, const std::string& weather, const Logger& logger, const OptimizationWeights& weights) const {
        
        bool isRelaxedPass = false;
        
    retry_assignment:
        std::cout << "[SYSTEM CHECK] Validating drone safety constraints...\n";
        // Use a pair of score and drone pointer for selection
        std::vector<std::pair<double, Drone*>> scoredDrones;
        std::set<std::string> uniqueFailureReasons;

        for (auto* d : drones) {
            if (!d->isStillAvailable()) continue;

            if (d->needsRecharge()) d->rechargeBattery();

            std::vector<std::string> failures = cm.getFailureReasons(d, delivery, weather, isRelaxedPass);
            
            if (failures.empty()) {
                double dist = d->getLocation().calculateDistance(delivery.getSource());
                
                // Calculate weighted performance score
                double score = (weights.distance * dist) 
                             - (weights.battery * d->getBattery()) 
                             - (weights.priority * delivery.getPriority())
                             + (weights.usage * d->getCompletedDeliveries());

                scoredDrones.push_back({score, d});
            } else {
                for (const auto& f : failures) uniqueFailureReasons.insert(f);
            }
        }

        if (!scoredDrones.empty()) {
            std::sort(scoredDrones.begin(), scoredDrones.end(), [](const auto& a, const auto& b){
                return a.first < b.first;
            });

            Drone* selected = scoredDrones[0].second;
            double bestScore = scoredDrones[0].first;

            selected->assign();
            delivery.setStatus(DeliveryStatus::Assigned);
            
            double distToPickup = selected->getLocation().calculateDistance(delivery.getSource());
            double distToDropoff = delivery.getSource().calculateDistance(delivery.getDestination());
            double totalTrip = distToPickup + distToDropoff;
            
            selected->finishDelivery(totalTrip, delivery.getDestination());
            
            // Transparency output
            displayScoreBreakdown(selected->getId(), distToPickup, selected->getBattery() + (totalTrip * 0.1), // battery before drain approximation for log
                                  delivery.getPriority(), selected->getCompletedDeliveries() - 1, weights, bestScore);
            
            std::cout << "[INTEL] Estimated Travel Time: " << estimateTime(totalTrip) << " units\n";

            logger.logAssignment(selected->getId(), delivery.getId(), totalTrip, selected->getBattery(), delivery.getPriority());
            return true;
        }

        // Pass 2: If strict Pass failed, try relaxing soft constraints
        if (!isRelaxedPass) {
            std::cout << "[PASS 1 FAILED] No drones met strict criteria. Retrying with relaxed constraints...\n";
            isRelaxedPass = true;
            goto retry_assignment;
        }

        // Final rejection if even relaxed constraints failed
        delivery.setStatus(DeliveryStatus::Rejected);
        std::vector<std::string> finalReasons(uniqueFailureReasons.begin(), uniqueFailureReasons.end());
        if (drones.empty()) finalReasons.push_back("No drones in fleet");
        
        logger.logRejection(delivery.getId(), finalReasons);
        return false;
    }
};
