#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Drone.h"
#include "Delivery.h"

// Base class for all delivery constraints
class DeliveryConstraint {
public:
    virtual ~DeliveryConstraint() = default;
    
    // Returns failure reason if invalid, otherwise empty string
    virtual std::string validate(const Drone* d, const Delivery& del, const std::string& weather, const std::vector<Location>& noFlyZones) const = 0;
};

class BatteryConstraint : public DeliveryConstraint {
public:
    std::string validate(const Drone* d, const Delivery& del, const std::string& weather, const std::vector<Location>& noFlyZones) const override {
        double distToSource = d->getLocation().calculateDistance(del.getSource());
        double distDelivery = del.getSource().calculateDistance(del.getDestination());
        
        if (!d->canCompleteTrip(distToSource + distDelivery)) {
            return "Inadequate battery for distance";
        }
        return "";
    }
};

class NoFlyZoneConstraint : public DeliveryConstraint {
public:
    std::string validate(const Drone* d, const Delivery& del, const std::string& weather, const std::vector<Location>& noFlyZones) const override {
        for (const auto& zone : noFlyZones) {
            if (del.getDestination() == zone || del.getSource() == zone) {
                return "Restricted airspace (No-fly zone)";
            }
        }
        return "";
    }
};

class WeatherConstraint : public DeliveryConstraint {
public:
    std::string validate(const Drone* d, const Delivery& del, const std::string& weather, const std::vector<Location>& noFlyZones) const override {
        // High priority (3) deliveries can bypass weather restrictions
        if (weather == "Bad" && del.getPriority() < 3) {
            return "Severe weather conditions";
        }
        return "";
    }
};

class ConstraintManager {
private:
    std::vector<Location> noFlyZones;
    std::vector<std::unique_ptr<DeliveryConstraint>> constraints;

public:
    ConstraintManager() {
        constraints.push_back(std::make_unique<BatteryConstraint>());
        constraints.push_back(std::make_unique<NoFlyZoneConstraint>());
        constraints.push_back(std::make_unique<WeatherConstraint>());
    }

    void addNoFlyZone(const Location& loc) {
        noFlyZones.push_back(loc);
    }

    // Identify all reasons why a drone cannot fulfill a specific delivery
    std::vector<std::string> getFailureReasons(const Drone* d, const Delivery& del, const std::string& weather) const {
        std::vector<std::string> reasons;
        for (const auto& constraint : constraints) {
            std::string result = constraint->validate(d, del, weather, noFlyZones);
            if (!result.empty()) {
                reasons.push_back(result);
            }
        }
        return reasons;
    }
};
