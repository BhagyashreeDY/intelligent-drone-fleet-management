#pragma once
#include <cmath>

class Location {
private:
    double x;
    double y;

public:
    Location(double x = 0, double y = 0) : x(x), y(y) {}
    
    double getX() const { return x; }
    double getY() const { return y; }
    
    // Euclidean distance calculation between two points
    double calculateDistance(const Location& other) const {
        return std::sqrt(std::pow(x - other.x, 2) + std::pow(y - other.y, 2));
    }
    
    // Check if two locations are identical
    bool operator==(const Location& other) const {
        return x == other.x && y == other.y;
    }
};
