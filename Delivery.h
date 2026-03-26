#pragma once
#include "Location.h"
#include <string>
#include <iostream>

enum class DeliveryStatus {
    Pending,
    Assigned,
    Rejected
};

class Delivery {
private:
    int deliveryId;
    Location source;
    Location destination;
    int priority; // 1 (Low) to 3 (High)
    DeliveryStatus status;

public:
    Delivery(int id, const Location& src, const Location& dest, int p)
        : deliveryId(id), source(src), destination(dest), priority(p), status(DeliveryStatus::Pending) {}

    int getId() const { return deliveryId; }
    Location getSource() const { return source; }
    Location getDestination() const { return destination; }
    int getPriority() const { return priority; }
    DeliveryStatus getStatus() const { return status; }

    void setStatus(DeliveryStatus s) { status = s; }

    // Human-readable status string
    std::string getStatusString() const {
        switch (status) {
            case DeliveryStatus::Assigned: return "Assigned";
            case DeliveryStatus::Rejected: return "Rejected";
            default: return "Pending";
        }
    }

    void displayDetails() const {
        std::cout << "Delivery [" << deliveryId << "]"
                  << " | Priority: " << priority 
                  << " | Status: " << getStatusString() 
                  << " | Dest: (" << destination.getX() << "," << destination.getY() << ")\n";
    }
};
