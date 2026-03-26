#pragma once
#include <iostream>
#include <vector>
#include <string>

class Logger {
public:
    void logAssignment(int droneId, int deliveryId, double distance, double batteryLeft, int priority) const {
        std::string urgency = (priority == 3) ? "High" : (priority == 2 ? "Medium" : "Low");
        
        std::cout << "\n[ASSIGNED] Delivery #" << deliveryId << " (Priority: " << urgency << ")\n"
                  << "  -> Drone " << droneId << " matches constraints\n"
                  << "  -> Travel Distance: " << distance << " units\n"
                  << "  -> Estimated Battery: " << batteryLeft << "%\n"
                  << "----------------------------------------\n";
    }

    void logRejection(int deliveryId, const std::vector<std::string>& reasons) const {
        std::cout << "\n[REJECTED] Delivery #" << deliveryId << "\n"
                  << "  Status: Cannot be processed\n"
                  << "  Reasons:\n";
        for (const auto& reason : reasons) {
            std::cout << "  - " << reason << "\n";
        }
        std::cout << "----------------------------------------\n";
    }
    
    void logMessage(const std::string& msg) const {
        std::cout << msg << std::endl;
    }
};
