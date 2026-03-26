# Drone Delivery System - Modern C++ Implementation

This project simulates an autonomous drone fleet managing package deliveries under real-world constraints like battery limits, no-fly zones, and weather conditions.

## Technical Design Decisions

### 1. Extensible Constraint System
The project implements a `ConstraintManager` using an interface-based design (`DeliveryConstraint`).
*   **Rationale:** Adding new operational rules (e.g., wind speed, drone weight limits) is as simple as adding a new class without modifying the existing assignment engine.
*   **Impact:** Promotes the Open-Closed Principle from SOLID.

### 2. Polymorphic Drone Fleet
Drones use inheritance to specialize behavior:
*   **LightDrones:** Optimized for short, fast trips with low power usage.
*   **HeavyDrones:** Built for long-haul or heavy payload stability with higher consumption rates.
*   **Implementation:** Polymorphism allows the `AssignmentEngine` to treat all drones uniformly while respecting their unique physical properties.

### 3. Smart Resource Management
*   **Battery Lifecycle:** Drones maintain state throughout the simulation. If a battery drops below 20%, the system automatically flags the drone for a recharge cycle, simulating real-world warehouse logistics.
*   **Modern C++ Memory Management:** The system utilizes `std::unique_ptr` and `std::move` to ensure safe memory ownership and eliminate leaks during fleet scaling.

### 4. Dynamic Input Control
*   **Configuration Layer:** The system is entirely config-driven via `config.txt`. This allows testing different fleet compositions and delivery queues without recompiling the source code.

### 5. Multi-Cycle Simulation
Unlike single-pass scripts, this implementation supports a time-sliced simulation. It demonstrates how the system adapts to changing weather (e.g., rejecting low-priority deliveries during a storm) and how the fleet's total battery health degrades over time.
