#pragma once
#include <iostream>
#include <vector>
#include <string>

class Logger {
public:
    void logMessage(const std::string& msg) const {
        std::cout << "[INFO] " << msg << "\n";
    }

    void logAssignment(int droneId, int deliveryId, double distance, double batteryLeft, int priority) const {
        std::cout << "[SUCCESS] Drone " << droneId << " assigned to Delivery " << deliveryId 
                  << " | Trip: " << distance << " units"
                  << " | Post-battery: " << batteryLeft << "%"
                  << " | Prio: " << priority << "\n";
    }

    void logRejection(int deliveryId, const std::vector<std::string>& reasons) const {
        std::cout << "[REJECTED] Delivery " << deliveryId << " could not be assigned. Reasons:\n";
        for (const auto& r : reasons) {
            std::cout << "  - " << r << "\n";
        }
    }
};
