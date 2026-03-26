#pragma once
#include "Location.h"
#include <string>

enum class DeliveryStatus {
    Pending,
    Assigned,
    Rejected,
    Completed
};

class Delivery {
private:
    int deliveryId;
    Location source;
    Location destination;
    int priority; // 1: Low, 2: Medium, 3: High
    DeliveryStatus status;

public:
    Delivery(int id, const Location& src, const Location& dest, int prio)
        : deliveryId(id), source(src), destination(dest), priority(prio), status(DeliveryStatus::Pending) {}

    int getId() const { return deliveryId; }
    Location getSource() const { return source; }
    Location getDestination() const { return destination; }
    int getPriority() const { return priority; }
    DeliveryStatus getStatus() const { return status; }
    
    void setStatus(DeliveryStatus newStatus) { status = newStatus; }
};
