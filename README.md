Molecular Dynamics Simulator
A particle-based physics simulation engine built from scratch in C++, implementing the Lennard-Jones potential and Velocity Verlet integration to model the behaviour of interacting particles at a molecular level. Visualised in real-time using SFML.

Overview
This project simulates N particles interacting via the Lennard-Jones pair potential, one of the most fundamental models in computational physics and materials science. Particles evolve over time under Newtonian mechanics, producing emergent thermodynamic behaviour including temperature equilibration, pressure, and diffusion — all arising from simple pairwise force rules.
The simulator was built as a personal portfolio project to develop practical skills in C++, numerical methods, and computational physics, with direct relevance to quantitative finance and scientific computing.

Features

Lennard-Jones force calculation between all particle pairs
Velocity Verlet time integration for energy-conserving dynamics
Periodic boundary conditions to simulate bulk material behaviour
Regular grid particle initialisation to prevent force singularities
Neighbour list optimisation to reduce O(N²) force calculations
Thermostat for temperature control via velocity rescaling
Real-time 2D particle visualisation using SFML
Energy, temperature, and pressure output for analysis
Python visualisation scripts for post-simulation analysis

Physics Background
Lennard-Jones Potential
The interaction between particles is governed by the Lennard-Jones (LJ) 12-6 potential:
V(r) = 4ε [ (σ/r)^12 - (σ/r)^6 ]
where ε is the depth of the potential well (energy scale), σ is the finite distance at which the inter-particle potential is zero (length scale), and r is the distance between two particles. The repulsive r^-12 term models Pauli exclusion at short range, while the attractive r^-6 term models van der Waals dispersion forces.
A cutoff radius of r_c = 2.5σ is applied — interactions beyond this distance are truncated as their contribution becomes negligible, significantly reducing computational cost.
Velocity Verlet Integration
Particle positions and velocities are evolved using the Velocity Verlet algorithm, a symplectic integrator that conserves energy over long simulation times:
v(t + dt/2) = v(t) + (F(t) / m) * dt/2
x(t + dt)   = x(t) + v(t + dt/2) * dt
v(t + dt)   = v(t + dt/2) + (F(t + dt) / m) * dt/2
Velocity Verlet is preferred over simple Euler integration because it is time-reversible and exhibits near-perfect energy conservation — critical properties for a physically meaningful simulation.
Periodic Boundary Conditions
The simulation box uses periodic boundary conditions (PBC) to eliminate edge effects and simulate a bulk system with a finite number of particles. When a particle crosses one face of the box it re-enters from the opposite face, and the minimum image convention is used to calculate the nearest distance between particle pairs.
Thermodynamic Observables
Temperature is computed from the equipartition theorem relating kinetic energy to temperature. Pressure is computed via the virial theorem from the pairwise forces. Both are monitored over time to verify the system reaches thermodynamic equilibrium.

Build Instructions
Prerequisites

g++ with C++17 support
SFML 2.5+
CMake 3.15+
Python 3.x with matplotlib and numpy (for analysis scripts)

Windows (MSYS2/MinGW)
bashg++ src/*.cpp -o molecular_dynamics -lsfml-graphics -lsfml-window -lsfml-system -std=c++17
./molecular_dynamics.exe
CMake (all platforms)
bashmkdir build && cd build
cmake ..
make
./molecular_dynamics

Usage
Simulation parameters are set in include/constants.h:
cppconstexpr int    N_PARTICLES = 100;    // number of particles
constexpr double BOX_LENGTH  = 10.0;  // simulation box side length
constexpr double DT          = 0.001; // timestep
constexpr double TEMPERATURE = 1.0;   // target temperature (reduced units)
constexpr double CUTOFF      = 2.5;   // LJ cutoff radius
Run the simulation, then analyse output with:
bashpython scripts/visualise.py

References and Learning Resources
The physics theory and implementation approach for this project were developed from the following sources:
Primary References

Rapaport, D.C. The Art of Molecular Dynamics Simulation, 2nd ed. Cambridge University Press. — Primary implementation reference, directly informed the force calculation and integrator architecture
Frenkel, D. & Smit, B. Understanding Molecular Simulation: From Algorithms to Applications, 2nd ed. Academic Press, 2002. — Core theoretical foundation for LJ potential, PBC, and thermodynamic observables
Allen, M.P. & Tildesley, D.J. Computer Simulation of Liquids. Oxford University Press. — Reference for neighbour list implementation and pressure calculation via virial theorem

Online Resources

InSilicoSci — Molecular Dynamics Simulation Concepts (insilicosci.com/molecular-dynamics-simulation-concepts) — Conceptual introduction to MD theory
Compute Canada MD Theory Course (computecanada.github.io/molmodsim-md-theory-lesson-novice) — Periodic boundary conditions and force field theory
LearnCPP (learncpp.com) — C++ language foundation including data types, structs, classes, vectors, and memory management

C++ Implementation

This project was built alongside systematic study of C++ fundamentals via LearnCPP, covering chapters 1–16 including data types, functions, control flow, structs, classes, and the STL
