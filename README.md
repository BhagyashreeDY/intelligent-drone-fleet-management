# Intelligent Drone Fleet Management System

A C++ simulation of an autonomous drone delivery fleet that optimizes task assignment based on complex operational constraints. This project demonstrates advanced Object-Oriented Programming (OOP) principles, modern C++ memory management, and clean code architecture.

## 🚀 Key Features

*   **Constraint-Based Assignment:** Deliveries are matched against multiple constraints (Battery levels, No-Fly Zones, Weather) using an extensible interface-based design.
*   **Polymorphic Fleet:** Supports multiple drone types (`LightDrone`, `HeavyDrone`) with unique energy consumption profiles.
*   **Dynamic Simulation:** Features a multi-cycle simulation loop that demonstrates the fleet's adaptation to environmental changes (e.g., storm conditions).
*   **Config-Driven:** Entirely decoupled from hardcoded data. Drones, deliveries, and system settings are loaded from external `config.txt` files.
*   **Robust Logging:** Detailed telemetry for every assigned or rejected delivery, providing transparency into the system's decision-making process.

## 🛠️ Technical Stack

*   **Language:** C++ (using C++14/17 features)
*   **Concepts:** Inheritance, Polymorphism, Strategy Pattern, SOLID Principles, Smart Pointers.
*   **Build Tool:** GCC/g++

## 📦 Project Structure

*   `main.cpp`: Entry point and simulation orchestration.
*   `FleetManager.h`: High-level management of drones and delivery queues.
*   `Drone.h`: Polymorphic base class and specialized drone implementations.
*   `Delivery.h`: Data model and lifecycle management for package deliveries.
*   `AssignmentEngine.h`: Logic for matching pending requests to optimal drone candidates.
*   `ConstraintManager.h`: Extensible verification system for site-specific rules.
*   `Location.h`: Utility for 2D coordinate geometry and distance calculations.
*   `Logger.h`: Centralized reporting and telemetry.

## ⚙️ Compilation & Execution

To compile the system using `g++`:

```bash
g++ main.cpp -o drone_system
```

To run the simulation:

```bash
./drone_system
```

## 📝 Design Patterns

For a detailed breakdown of the architectural decisions and patterns used in this project, please refer to [DESIGN.md](./DESIGN.md).
