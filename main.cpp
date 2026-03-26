#include "FleetManager.h"
#include <iostream>

int main() {
    std::cout << "Starting Drone Fleet Management System Simulation...\n";
    
    // System setup
    FleetManager fleet;
    fleet.loadConfig("config.txt");

    const int totalCycles = 3;
    for (int cycle = 1; cycle <= totalCycles; ++cycle) {
        std::cout << "\n===============================";
        std::cout << "\n  SIMULATION RUN: CYCLE " << cycle;
        std::cout << "\n===============================\n";
        
        // Simulate dynamic environment changes
        if (cycle == 2) {
            std::cout << "[ENV] Storm detected - Switching to Bad Weather status.\n";
            fleet.setWeather("Bad");
            
            // Add priority requests during the storm
            std::cout << "[INFO] High-priority requests added to queue.\n";
            fleet.addDelivery(Delivery(201, Location(2, 2), Location(5, 5), 3)); 
            fleet.addDelivery(Delivery(202, Location(10, 10), Location(15, 15), 1));
        } 
        else if (cycle == 3) {
            std::cout << "[ENV] Storm passed - Weather restored to Good.\n";
            fleet.setWeather("Good");
        }

        fleet.processDeliveries();
        fleet.displayFleetStatus();
        
        std::cout << "Cycle " << cycle << " simulation complete.\n";
    }

    // Final session summary
    fleet.displaySystemMetrics();

    return 0;
}
