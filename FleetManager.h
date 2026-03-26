#pragma once
#include <vector>
#include <algorithm>
#include <fstream>
#include <memory>
#include <sstream>
#include "Drone.h"
#include "Delivery.h"
#include "AssignmentEngine.h"
#include "ConstraintManager.h"
#include "Logger.h"

class FleetManager {
private:
    std::vector<std::unique_ptr<Drone>> drones;
    std::vector<Delivery> deliveries;
    AssignmentEngine engine;
    ConstraintManager cm;
    std::string currentWeather;
    Logger logger;

public:
    FleetManager(const std::string& weather = "Good") : currentWeather(weather) {}

    void addDrone(std::unique_ptr<Drone> d) { 
        drones.push_back(std::move(d)); 
    }

    void addDelivery(const Delivery& d) { 
        deliveries.push_back(d); 
    }

    void addNoFlyZone(const Location& loc) { 
        cm.addNoFlyZone(loc); 
    }

    void setWeather(const std::string& weather) { 
        currentWeather = weather; 
    }

    // Initialize fleet and deliveries from a text-based configuration
    void loadConfig(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "[ERROR] Could not open config: " << filename << "\n";
            return;
        }

        std::string line;
        while (std::getline(file, line)) {
            if (line.empty() || line[0] == '#') continue;

            std::stringstream ss(line);
            std::string category;
            std::getline(ss, category, ':');

            if (category == "WEATHER") {
                ss >> currentWeather;
            } else if (category == "DRONE") {
                int id;
                std::string droneType;
                double battery, x, y;
                char comma;
                
                ss >> id >> comma;
                std::getline(ss, droneType, ',');
                
                // Cleanup whitespace from type string
                droneType.erase(0, droneType.find_first_not_of(" "));
                droneType.erase(droneType.find_last_not_of(" ") + 1);
                
                ss >> battery >> comma >> x >> comma >> y;
                
                if (droneType == "Light") {
                    addDrone(std::make_unique<LightDrone>(id, battery, Location(x, y)));
                } else if (droneType == "Heavy") {
                    addDrone(std::make_unique<HeavyDrone>(id, battery, Location(x, y)));
                }
            } else if (category == "NOFLYZONE") {
                double x, y;
                char comma;
                ss >> x >> comma >> y;
                addNoFlyZone(Location(x, y));
            } else if (category == "DELIVERY") {
                int id, priority;
                double sx, sy, dx, dy;
                char comma;
                ss >> id >> comma >> sx >> comma >> sy >> comma >> dx >> comma >> dy >> comma >> priority;
                addDelivery(Delivery(id, Location(sx, sy), Location(dx, dy), priority));
            }
        }
        std::cout << "[SYSTEM] Configuration loaded from " << filename << "\n";
    }

    // Process all pending deliveries based on priority
    void processDeliveries() {
        if (deliveries.empty()) {
            std::cout << "[SYSTEM] No deliveries in queue.\n";
            return;
        }

        // Sort by priority (higher value first)
        std::sort(deliveries.begin(), deliveries.end(), [](const Delivery& a, const Delivery& b) {
            return a.getPriority() > b.getPriority(); 
        });

        logger.logMessage("\n--- Processing Cycle (Weather: " + currentWeather + ") ---");
        
        std::vector<Drone*> dronePtrs;
        for (const auto& d : drones) dronePtrs.push_back(d.get());

        for (auto& delivery : deliveries) {
            if (delivery.getStatus() == DeliveryStatus::Pending) {
                engine.assignDelivery(dronePtrs, delivery, cm, currentWeather, logger);
            }
        }
    }

    // Generate outcome report for the session
    void displaySystemMetrics() const {
        int successful = 0;
        int failed = 0;
        
        for (const auto& del : deliveries) {
            if (del.getStatus() == DeliveryStatus::Assigned) successful++;
            else if (del.getStatus() == DeliveryStatus::Rejected) failed++;
        }

        int total = successful + failed;
        double efficiency = total > 0 ? (static_cast<double>(successful) / total) * 100.0 : 0.0;

        std::cout << "\n=== DELIVERY SESSION METRICS ===\n";
        std::cout << "Total Requests  : " << deliveries.size() << "\n";
        std::cout << "Successfully Assigned : " << successful << "\n";
        std::cout << "Rejections      : " << failed << "\n";
        std::cout << "Fleet Efficiency : " << efficiency << "%\n";
        std::cout << "===============================\n";
    }

    void displayFleetStatus() const {
        std::cout << "\n=== ACTIVE FLEET STATUS ===\n";
        for (const auto& drone : drones) {
            drone->displayStatus();
        }
        std::cout << "===========================\n";
    }
};
