#pragma once
#include <vector>
#include <algorithm>
#include <set>
#include "Drone.h"
#include "Delivery.h"
#include "ConstraintManager.h"
#include "Logger.h"

class AssignmentEngine {
public:
    // Core logic for matching a delivery request to the most suitable available drone
    bool assignDelivery(const std::vector<Drone*>& drones, Delivery& delivery, const ConstraintManager& cm, const std::string& weather, const Logger& logger) const {
        
        std::vector<std::pair<double, Drone*>> candidateDrones;
        
        // Identify available drones and calculate distance to pickup
        for (auto* d : drones) {
            if (d->isStillAvailable()) {
                if (d->needsRecharge()) {
                    d->rechargeBattery();
                }
                double dist = d->getLocation().calculateDistance(delivery.getSource());
                candidateDrones.push_back({dist, d});
            }
        }

        // Prioritize drones that are closer to the source
        std::sort(candidateDrones.begin(), candidateDrones.end(), [](const auto& a, const auto& b){
            return a.first < b.first;
        });

        std::set<std::string> uniqueFailureReasons;
        bool hasAvailableDrones = !candidateDrones.empty();

        for (auto& pair : candidateDrones) {
            Drone* drone = pair.second;
            std::vector<std::string> failureReasons = cm.getFailureReasons(drone, delivery, weather);
            
            if (failureReasons.empty()) {
                // Optimal drone found fulfilling all constraints
                drone->assign();
                delivery.setStatus(DeliveryStatus::Assigned);
                
                double distToPickup = drone->getLocation().calculateDistance(delivery.getSource());
                double distToDropoff = delivery.getSource().calculateDistance(delivery.getDestination());
                double totalTripDistance = distToPickup + distToDropoff;
                
                drone->finishDelivery(totalTripDistance, delivery.getDestination());
                
                logger.logAssignment(drone->getId(), delivery.getId(), totalTripDistance, drone->getBattery(), delivery.getPriority());
                return true;
            } else {
                // Collect unique reasons for rejection across all candidates
                for (const auto& reason : failureReasons) {
                    uniqueFailureReasons.insert(reason);
                }
            }
        }

        // Mark as rejected if no candidate met the criteria
        delivery.setStatus(DeliveryStatus::Rejected);
        std::vector<std::string> finalReasons(uniqueFailureReasons.begin(), uniqueFailureReasons.end());
        
        if (!hasAvailableDrones) {
            finalReasons.push_back("No drones are currently available in the fleet");
        }
        
        logger.logRejection(delivery.getId(), finalReasons);
        return false;
    }
};
