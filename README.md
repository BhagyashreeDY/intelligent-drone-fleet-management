# Intelligent Drone Fleet Management System

## Overview

A constraint-aware drone delivery simulation system built using Modern C++ and Object-Oriented Programming principles.
The system focuses on intelligent task allocation using optimization techniques and real-world operational constraints.

---

## Problem Statement

Drone delivery systems face several practical challenges:

* Limited battery capacity
* Restricted no-fly zones
* Weather-dependent operations
* Inefficient static assignment strategies

Many basic implementations rely on selecting the nearest available drone and ignore these constraints, resulting in unrealistic and inefficient systems.

---

## Solution Approach

This project models the decision-making layer of a drone delivery system by introducing:

* Constraint-based validation (battery, weather, restricted zones)
* Optimization-driven drone selection using weighted scoring
* Adaptive constraint handling with retry mechanisms
* Transparent decision logic through score breakdown and logs
* Performance tracking across simulation cycles

---

## Project Highlights

Most drone delivery simulations use simple heuristics such as nearest-drone assignment and do not account for real-world constraints.

This system improves upon those approaches by:

* Introducing a constraint-aware decision system
* Using an optimization-based scoring mechanism for better selection
* Supporting adaptive constraint relaxation to improve delivery success
* Providing explainable decision outputs through structured logs

The project focuses on modeling the decision layer of real-world systems, which is a key component in practical implementations.
While hardware-level complexities are not included, the system is designed to be extensible for future integration.

---

## Key Features

* Drone fleet management
* Priority-based delivery scheduling
* Constraint evaluation (battery, weather, no-fly zones)
* Weighted scoring for drone selection
* Adaptive constraint handling
* Detailed decision logs and rejection reasoning
* System performance metrics (efficiency tracking)
* Configuration-driven setup (`config.txt`)
* Multi-cycle simulation

---

## System Design

* Object-Oriented Design (Encapsulation, Inheritance, Polymorphism)
* Strategy Pattern for constraint handling
* Modular architecture separating logic and control flow

---

## Optimization Model

The system selects drones using a weighted scoring approach:

Score = (distance_weight × distance)
- (battery_weight × battery)
- (priority_weight × priority)
+ (usage_weight × utilization)

Lower score indicates a better candidate.

Weights are configurable through the configuration file.

---

## Project Structure

```
intelligent-drone-fleet-management/
│
├── main.cpp
├── Drone.h
├── Delivery.h
├── Location.h
├── AssignmentEngine.h
├── ConstraintManager.h
├── FleetManager.h
├── Logger.h
│
├── config.txt
├── DESIGN.md
└── README.md
```

---

## How to Run

```bash
g++ main.cpp -o drone_system
./drone_system
```

---

## Sample Output

```
[SYSTEM CHECK] Validating drone safety constraints...

[INTEL] Score Breakdown for Drone 2:
  - Distance Component: 12.5
  - Battery Component : -80.0
  - Priority Component: -7.5
  - Usage Penalty     : +1.5
  - Final Score       : -73.5

Assigned to Drone 2
Estimated Delivery Time: 8.3 units

[SYSTEM SUMMARY]
Total Deliveries Processed: 6
Successful: 4
Failed: 2
Efficiency: 66.6%
```

---

## Future Enhancements

* Integration with real-time weather data
* Advanced route optimization
* Obstacle-aware path planning
* Distributed fleet coordination

---

## Creator

Bhagyashree Yadagiri
