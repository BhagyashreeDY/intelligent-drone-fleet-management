#pragma once
#include <cmath>

class Location {
private:
    double x;
    double y;

public:
    Location(double x_coord = 0, double y_coord = 0) : x(x_coord), y(y_coord) {}

    double getX() const { return x; }
    double getY() const { return y; }

    // Euclidean distance between two coordinate points
    double calculateDistance(const Location& other) const {
        return std::sqrt(std::pow(x - other.x, 2) + std::pow(y - other.y, 2));
    }

    // Comparison for exact location matches
    bool operator==(const Location& other) const {
        return (x == other.x && y == other.y);
    }
};
