# Custom 2D Physics Engine

A custom 2D physics simulation built from scratch in C++ using SDL3 and Dear ImGui.

## Core Features

- **Vector Math (`Vec2`)**: Custom implementation of 2D vector operations, normalization, dot products, and compound assignment operators.
- **Continuous Collision Detection (CCD)**: Time-of-impact calculation via quadratic equation solving ($A, B, C$ coefficients) to prevent object tunnelling at high velocities.
- **Collision Resolution**: Impulse-based elastic response utilising inverse mass and restitution.
- **N-Body Simulation**: Supports dynamic interaction across an arbitrary number of circular bodies.
- **Environment**: Real-time linear drag damping and boundary wall collision handling.
- **Diagnostics**: Live monitoring of system kinetic energy ($\sum \frac{1}{2}mv^2$) via a Dear ImGui debug panel.
- **Interactivity**: Runtime object spawning and mouse-applied velocity impulses.

## Tech Stack

- C++ (C++17/20)
- SDL3
- Dear ImGui
- CMake

## Project Architecture

```text
Custom-2D-Physics-Engine/
├── CMakeLists.txt
├── src/
│   ├── main.cpp        # Application entry point, event loop & ImGui integration
│   ├── World.h         # Simulation state, N-body collision dispatch & energy tally
│   ├── Physics.h/.cpp  # Core physical algorithms (CCD, impulses, drag, walls)
│   ├── Circle.h        # Rigid body entity structure with mass & custom color
│   ├── Vec2.h          # 2D mathematical vector structure & operators
│   └── Renderer.h      # Software-based circle rasterization helper
```
