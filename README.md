# Intelligent Drone Fleet Management System

## Overview

A constraint aware drone delivery simulation system built using Modern C++ and Object Oriented Programming principles.
The system focuses on intelligent task allocation using optimization techniques and real world operational constraints.

<<<<<<< HEAD
---
=======
*   **Optimization-Driven Assignment:** Matches deliveries against multiple constraints using weighted decision scoring for highest efficiency.
*   **Adaptive Constraint Relaxation:** Two-pass logic reconsidering rejected deliveries when soft constraints (weather) can be safely bypassed.
*   **Polymorphic Fleet:** Supports multiple drone types (`LightDrone`, `HeavyDrone`) with unique energy consumption profiles.
*   **Dynamic Simulation:** Features a multi-cycle loop demonstrating adaptation to shifting environmental conditions.
*   **Config-Driven Architecture:** Decoupled from hardcoded data; fleet settings and optimization weights are loaded from external configuration.

## 📦 Project Structure

```text
├── src/                    # Source code and header files
├── config/                 # External system configuration
├── docs/                   # Architectural documentation
├── README.md               # Project overview
└── .gitignore              # Git ignore rules
```
>>>>>>> 6af3b99 (Refactored project structure into src, config, and docs directories)

## Problem Statement

<<<<<<< HEAD
Drone delivery systems face several practical challenges:

* Limited battery capacity
* Restricted no fly zones
* Weather dependent operations
* Inefficient static assignment strategies

Many basic implementations rely on selecting the nearest available drone and ignore these constraints, resulting in unrealistic and inefficient systems.

---

## Solution Approach

This project models the decision-making layer of a drone delivery system by introducing:

* Constraint based validation (battery, weather, restricted zones)
* Optimization driven drone selection using weighted scoring
* Adaptive constraint handling with retry mechanisms
* Transparent decision logic through score breakdown and logs
* Performance tracking across simulation cycles

---

## Project Highlights

Most drone delivery simulations use simple heuristics such as nearest drone assignment and do not account for real world constraints.

This system improves upon those approaches by:

* Introducing a constraint aware decision system
* Using an optimization based scoring mechanism for better selection
* Supporting adaptive constraint relaxation to improve delivery success
* Providing explainable decision outputs through structured logs

The project focuses on modeling the decision layer of real-world systems, which is a key component in practical implementations.
While hardware level complexities are not included, the system is designed to be extensible for future integration.

---

## Key Features

* Drone fleet management
* Priority based delivery scheduling
* Constraint evaluation (battery, weather, no fly zones)
* Weighted scoring for drone selection
* Adaptive constraint handling
* Detailed decision logs and rejection reasoning
* System performance metrics (efficiency tracking)
* Configuration driven setup (`config.txt`)
* Multi cycle simulation

---

## System Design

* Object Oriented Design (Encapsulation, Inheritance, Polymorphism)
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
=======
*   **Language:** C++ (using C++14/17 features)
*   **Core Concepts:** Inheritance, Polymorphism, Strategy Pattern, SOLID Principles, Smart Pointers.
*   **Build Tool:** GCC/g++

## ⚙️ Compilation & Execution

To compile the system from the project root:

```bash
g++ src/main.cpp -I src -o drone_system
```

To run the simulation:

```bash
>>>>>>> 6af3b99 (Refactored project structure into src, config, and docs directories)
./drone_system
```

---

<<<<<<< HEAD
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

* Integration with real time weather data
* Advanced route optimization
* Obstacle aware path planning
* Distributed fleet coordination

---

## Creator

Bhagyashree Yadagiri
=======
For a detailed breakdown of the architectural decisions and patterns used in this project, please refer to [docs/DESIGN.md](./docs/DESIGN.md).
>>>>>>> 6af3b99 (Refactored project structure into src, config, and docs directories)
