# Molecular Dynamics Simulator (C++/SFML)

This project is a real-time 2D molecular dynamics sandbox written in modern C++, where hundreds to thousands of particles interact through a Lennard-Jones (LJ) force model, resolve near-field overlap with impulse-style collision handling, and advance with fixed-step Verlet-style integration for stable simulation timing; the result is an interactive desktop simulation that demonstrates physics modeling, numerical integration, spatial partitioning, and rendering/HUD engineering in a compact, readable codebase.

## Demo

https://github.com/user-attachments/assets/c203037e-9d73-4677-a81e-7f5fd4495403

## Features

- Real-time particle simulation with a fixed physics timestep (`1/60 s`)
- Lennard-Jones pair-force interactions with cutoff and neighbor list acceleration
- Spatial grid hashing for near-`O(n)` neighborhood candidate generation
- Wall bounds and overlap/collision response with restitution + friction terms
- HUD with rolling FPS, physics step time, particle count, and energy trend

## Build and Run

### Prerequisites

- CMake `>=3.16`
- C++17 compiler
- SFML `>=2.5` (`graphics`, `window`, `system`)

### Linux (Ubuntu/Debian)

```bash
sudo apt update
sudo apt install -y build-essential cmake libsfml-dev
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j
./build/bin/sim
```

### macOS (Homebrew)

```bash
brew install cmake sfml
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j
./build/bin/sim
```

### Windows

Using MSYS2 UCRT64 (recommended for this setup):

```powershell
pacman -S --needed mingw-w64-ucrt-x86_64-toolchain mingw-w64-ucrt-x86_64-cmake mingw-w64-ucrt-x86_64-sfml
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release
cmake --build build
.\build\bin\sim.exe
```

Using Visual Studio generator:

```powershell
cmake -S . -B build -G "Visual Studio 17 2022" -A x64
cmake --build build --config Release
.\build\bin\Release\sim.exe
```

## Architecture

```text
main.cpp
  ├─ Event loop + fixed-step accumulator
  ├─ buildNeighbourList(...)          [grid_particle.cpp]
  ├─ calcNeighbourInteractions(...)   [grid_particle.cpp + lj_potential.cpp]
  ├─ Particle::update(...)            [particle.cpp + velocity_velvet_int.cpp]
  ├─ Particle::checkBounds(...)       [particle.cpp]
  └─ HudOverlay::update/draw(...)     [hud_overlay.cpp]
```

Simulation/UI layout:

- Simulation viewport: `1200 x 800`
- Right HUD panel: text metrics
- Bottom HUD strip: full-width energy trend graph
- Window size: `simWidth + hudWidth` by `1000` (configured in `include/constants.h`)

## Physics Model

### 1) Lennard-Jones force

Pairwise force magnitude (implemented in `lj_potential.cpp`):

\[
F(r)=\frac{24\epsilon}{r^2}\left[2\left(\frac{\sigma}{r}\right)^{12}-\left(\frac{\sigma}{r}\right)^6\right]
\]

Implementation details:

- `LJ_EPSILON = 10.0`
- `LJ_SIGMA = PARTICLE_RADIUS * 2.3`
- Cutoff radius `LJ_CUTOFF = 2.5 * LJ_SIGMA`
- Neighbor skin radius `SKIN_RADIUS = 1.2 * max(LJ_CUTOFF, 2R)`

### 2) Verlet-style integration

The runtime uses a fixed-step update and a Verlet-style velocity/position advance:

\[
\mathbf{v}_{t+\Delta t}=\mathbf{v}_t+\mathbf{a}_t\Delta t,\qquad
\mathbf{x}_{t+\Delta t}=\mathbf{x}_t+\mathbf{v}_{t+\Delta t}\Delta t
\]

Notes:

- Physics timestep is fixed at `\Delta t = 1/60 s`
- Gravity is applied as a force each step
- Collision and wall constraints are resolved after force accumulation

### 3) Scaling notes

- Units are simulation units mapped to pixels (not SI-calibrated molecular units)
- `sigma` is tied to rendered particle diameter for visually stable interactions
- Parameter choices prioritize interactive stability and clarity over strict physical fidelity

## Performance

The app is frame-limited to `60 FPS` and exposes rolling FPS and physics step time in the HUD.

Current benchmark protocol (recommended):

1. Build `Release`
2. Launch app and spawn particles in batches (left click)
3. Let each particle count settle for ~10 seconds
4. Record average FPS from HUD and physics step time

Performance snapshot (fill with your machine measurements):

| Particle count | Avg FPS | Physics ms/step | Notes |
|---|---:|---:|---|
| 500 | _TBD_ | _TBD_ | single click spawn |
| 1000 | _TBD_ | _TBD_ | two clicks |
| 2500 | _TBD_ | _TBD_ | sustained run |
| 5000 | _TBD_ | _TBD_ | stress test |

## Controls

- Left mouse click in simulation area: spawn ~500 particles
- Close window: exit

## Roadmap

- Project plan: [`PROJECT_PLAN.md`](PROJECT_PLAN.md)

## References

- Rapaport, D.C. *The Art of Molecular Dynamics Simulation* (2nd ed.)
- Frenkel & Smit, *Understanding Molecular Simulation* (2nd ed.)
- Allen & Tildesley, *Computer Simulation of Liquids*
