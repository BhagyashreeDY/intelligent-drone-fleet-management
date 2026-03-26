#pragma once
#include "Location.h"
#include <string>
#include <iostream>

class Drone {
protected:
    int droneId;
    double batteryLevel;
    Location currentLocation;
    bool isAvailable;
    std::string type;

    // Abstract method for battery usage per distance unit
    virtual double getConsumptionRate() const = 0;

public:
    Drone(int id, double battery, const Location& startLoc, std::string t)
        : droneId(id), batteryLevel(battery), currentLocation(startLoc), isAvailable(true), type(t) {}
    
    virtual ~Drone() = default;

    int getId() const { return droneId; }
    double getBattery() const { return batteryLevel; }
    Location getLocation() const { return currentLocation; }
    bool isStillAvailable() const { return isAvailable; }

    // Check if drone battery is below operational threshold
    bool needsRecharge() const { return batteryLevel < 20.0; }

    void rechargeBattery() {
        batteryLevel = 100.0;
        std::cout << "[RECHARGE] Drone " << droneId << " restored to 100%.\n";
    }

    // Verify if battery can sustain the travel distance
    virtual bool canCompleteTrip(double distance) const {
        return batteryLevel >= (distance * getConsumptionRate());
    }

    void assign() { isAvailable = false; }

    void finishDelivery(double distance, const Location& newLoc) {
        isAvailable = true;
        batteryLevel -= (distance * getConsumptionRate());
        currentLocation = newLoc;
    }

    virtual void displayStatus() const {
        std::cout << "Drone [" << droneId << "] (" << type << ")"
                  << " | Battery: " << batteryLevel << "%"
                  << " | Loc: (" << currentLocation.getX() << "," << currentLocation.getY() << ")\n";
    }
};

// Specialized drone types with specific consumption profiles

class LightDrone : public Drone {
protected:
    double getConsumptionRate() const override { return 1.2; }
public:
    LightDrone(int id, double battery, const Location& startLoc) 
        : Drone(id, battery, startLoc, "Light") {}
};

class HeavyDrone : public Drone {
protected:
    double getConsumptionRate() const override { return 2.8; }
public:
    HeavyDrone(int id, double battery, const Location& startLoc) 
        : Drone(id, battery, startLoc, "Heavy") {}
};
