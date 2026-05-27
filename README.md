# Molecular Dynamics Simulator
A particle-based physics simulation engine built from scratch in C++, implementing the Lennard-Jones potential and Velocity Verlet integration to model the behaviour of interacting particles at a molecular level. Visualised in real-time using SFML.

---
https://github.com/user-attachments/assets/c203037e-9d73-4677-a81e-7f5fd4495403

## Overview
This project simulates N particles interacting via the Lennard-Jones pair potential, one of the most fundamental models in computational physics and materials science. Particles evolve over time under Newtonian mechanics, producing emergent thermodynamic behaviour including temperature equilibration, pressure, and diffusion — all arising from simple pairwise force rules.

The simulator was built as a personal portfolio project to develop practical skills in C++, numerical methods, and computational physics, with direct relevance to scientific computing and memory management.

---

## References and Learning Resources
The physics theory and implementation approach for this project were developed from the following sources:

### Primary References
- Rapaport, D.C. *The Art of Molecular Dynamics Simulation*, 2nd ed. Cambridge University Press. — Primary implementation reference, directly informed the force calculation and integrator architecture
- Frenkel, D. & Smit, B. *Understanding Molecular Simulation: From Algorithms to Applications*, 2nd ed. Academic Press, 2002. — Core theoretical foundation for LJ potential, PBC, and thermodynamic observables
- Allen, M.P. & Tildesley, D.J. *Computer Simulation of Liquids*. Oxford University Press. — Reference for neighbour list implementation and pressure calculation via virial theorem

### Online Resources
- InSilicoSci — Molecular Dynamics Simulation Concepts (`insilicosci.com/molecular-dynamics-simulation-concepts`) — Conceptual introduction to MD theory
- Compute Canada MD Theory Course (`computecanada.github.io/molmodsim-md-theory-lesson-novice`) — Periodic boundary conditions and force field theory
- LearnCPP (`learncpp.com`) — C++ language foundation including data types, structs, classes, vectors, and memory management

### C++ Implementation
This project was built alongside systematic study of C++ fundamentals via LearnCPP, covering chapters 1–16 including data types, functions, control flow, structs, classes, and the STL.
