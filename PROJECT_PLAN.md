# Project Plan — Path to Resume-Worthy

Practical, prioritized roadmap for taking this molecular dynamics sim from "works on my machine" to a portfolio piece that demonstrates real software engineering — not just physics.

Each item lists: **what** to build, **why** it matters for a reviewer, **where** in the codebase, and a rough **effort** estimate.

---

## Current State (snapshot)

Already done:

- Spatial hash neighbor list (near O(n))
- Lennard-Jones interatomic force
- True Velocity Verlet integration (drift + force recompute + kick)
- Iterative impulse-based collision solver (restitution, friction, slop)
- Velocity-mapped color gradient
- Wall restitution + bounds clamping
- ~600 LOC across 10 source files

Missing for resume-grade:

- No tests, no CI, no CMake, no deterministic stepping, no config system, no metrics, weak README, global state, magic numbers, single app state.

---

## Tier 1 — Minimum Resume Bar (do these first)

These are non-negotiable for the project to read as "engineered" instead of "scripted."


### 1.3 — Extract `Simulation` and `App` classes

- **What:** Move particle vector, neighbor build, force calc, and integration into a `Simulation` class. Move window, font, HUD, input into an `App` class. `main()` becomes ~10 lines.
- **Why:** Globals (`count`, `MyFont`) and a 70-line `main` signal "script." Encapsulated state signals "system."
- **Where:** New `simulation.h/cpp`, `app.h/cpp`. Refactor `main.cpp`.
- **Effort:** ~150 LOC across new files, ~50 LOC removed from `main.cpp`.

### 1.4 — Unit tests for physics primitives

- **What:** Add `tests/` directory using Catch2 or doctest (header-only, easy). Test:
  - `calcLennardJonesForce` at known distances (`σ`, `2σ`, equilibrium)
  - `calcDistSqr`, `calcDelta` helpers
  - Verlet step on a 1-particle drop (analytical comparison after N steps)
  - Wall reflection conserves kinetic energy when restitution = 1.0
- **Why:** No tests = no engineering. Even 5 tests changes the signal completely.
- **Where:** New `tests/test_physics.cpp`, link via CMake.
- **Effort:** ~120 LOC.

### 1.5 — GitHub Actions CI

- **What:** Add `.github/workflows/build.yml` that runs CMake build + tests on Linux (Ubuntu + SFML apt package).
- **Why:** A green CI badge on the README is the single highest-signal trust marker for a code reviewer.
- **Where:** New `.github/workflows/build.yml`.
- **Effort:** ~30 LOC YAML.

### 1.6 — Professional README

- **What:** Rewrite `README.md` with:
  - One-paragraph project description
  - Demo GIF (record with ScreenToGif or similar)
  - Build instructions for Linux/macOS/Windows
  - Architecture diagram (text or image)
  - Physics model section (Verlet equations, LJ form, scaling notes)
  - Performance numbers (particle count at 60 FPS)
  - Roadmap section linking to this file
- **Why:** Most reviewers read the README and 1–2 source files. If the README is weak, the rest doesn't get read.
- **Effort:** ~100 lines + a recorded GIF.

---

## Tier 2 — Polish (do these to stand out)

### 2.1 — Deterministic mode

- **What:** Seeded `std::mt19937` for spawn randomness, optional `--seed N` CLI flag. Combined with the fixed timestep, two runs with the same seed produce identical particle motion.
- **Why:** Reproducibility is a signal of physics/simulation maturity. Also enables regression testing of full simulation runs.
- **Where:** `utils.cpp` (RNG), `app.cpp` (CLI parsing).
- **Effort:** ~30 LOC.

### 2.2 — Runtime config file

- **What:** Load `config.toml` or `config.json` at startup with all the values currently in `constants.h` (gravity, particle radius, LJ params, window size, etc.). Move `constants.h` to compile-time *defaults*.
- **Why:** Recompiling to tune `LJ_EPSILON` is amateur. A config file demonstrates separation of code and parameters.
- **Where:** New `config.h/cpp`, library: `toml++` or `nlohmann::json`.
- **Effort:** ~100 LOC.

### 2.3 — Metrics overlay (HUD upgrade)

- **What:** Replace current 2-line HUD with:
  - FPS (rolling avg)
  - Particle count
  - Physics step time (ms)
  - Total system kinetic energy
  - Total LJ potential energy
  - Optional: line graph of energy over time
- **Why:** Demonstrates instrumentation. Energy conservation is *the* validation metric for an MD sim — showing it visibly proves your integrator works.
- **Where:** `app.cpp` (HUD), `simulation.cpp` (metrics computation).
- **Effort:** ~80 LOC.

### 2.4 — Pause / single-step / reset controls

- **What:** Keyboard bindings: `Space` pause, `N` single-step, `R` reset, `+/-` adjust spawn rate.
- **Why:** Single-step is critical for debugging physics and demoing to a reviewer. Pause+step says "this person has actually used this tool."
- **Where:** `app.cpp` input handling.
- **Effort:** ~30 LOC.

### 2.5 — Benchmark script + documented results

- **What:** Add `benchmarks/` with a script that spawns N particles and measures sustained FPS for N = 500, 1000, 2500, 5000, 10000. Output a CSV. Plot in README.
- **Why:** Concrete numbers ("sustains 60 FPS at 5000 particles on M1 Mac") are resume-bullet material. Vague performance claims aren't.
- **Effort:** ~50 LOC + run + chart.

---

## Tier 3 — Stretch (if you want to be noticed)

Pick one of these for a "wow" factor. Don't try to do all three.

### 3.1 — Multithreaded force calculation

- **What:** Split `calcNeighbourInteractions` across threads using `std::thread` or `std::for_each(std::execution::par, ...)`. Per-particle force accumulation needs care (atomic adds or per-thread buffers).
- **Why:** Real-world MD simulators are parallel. Implementing it correctly (race-free, with measurable speedup) is a senior-level skill.
- **Effort:** ~100 LOC + careful debugging.

### 3.2 — WebAssembly build

- **What:** Add an Emscripten build target. Host the sim as a live demo at `username.github.io/molecular-dynamics-sim/`.
- **Why:** A reviewer clicks a link and sees your project running in 5 seconds. This single thing dominates every other portfolio touchpoint.
- **Effort:** 3–6 hours of build-system wrangling.

### 3.3 — Physical validation: radial distribution function

- **What:** Compute g(r) — the radial distribution function — of the steady-state fluid. Compare to the known g(r) of a 2D LJ fluid at the temperature/density of your run.
- **Why:** This is the difference between "I made a particle toy" and "I made a physics simulator." Reviewers with a science background will immediately know what this means.
- **Where:** New `analysis/rdf.cpp`, output `rdf.csv`, plot in README.
- **Effort:** ~80 LOC + research time.

---

## Suggested Execution Order

If you have ~2 weekends:

1. CMake + fixed timestep + extract `Simulation` class (Sat 1)
2. Catch2 tests + GitHub Actions CI (Sun 1)
3. Config file + metrics overlay (Sat 2)
4. README rewrite + record demo GIF + benchmark run (Sun 2)

That sequence alone takes the project from "class assignment" to "small portfolio project."

Add one Tier 3 item if you want it to lead a portfolio.

---

## Definition of Done

The project is resume-worthy when **all of these are true**:

- [ ] `git clone && cmake -B build && cmake --build build && ./build/sim` works on Linux without prior knowledge
- [ ] `ctest` runs and passes 5+ tests
- [ ] CI badge in README is green
- [ ] README has: description, demo media, build instructions, architecture, physics model, performance numbers
- [ ] `main()` is under 20 lines
- [ ] Zero global mutable state
- [ ] At least one piece of Tier 3 work that can be linked to or seen in 5 seconds

---

## What This Plan Optimizes For

A reviewer spends 3–5 minutes on each candidate's portfolio piece. The order above is calibrated to that budget:

1. **First 30 seconds** — they open the README and see a GIF, a description, and a CI badge.
2. **Next 2 minutes** — they read the README, scan `main.cpp` (which is short), notice tests exist.
3. **Last 2 minutes** — they spot-check one source file, look for any clever optimization (the grid, the Verlet, the LJ scaling notes).

Every Tier 1 item targets one of those three windows. Nothing else matters until Tier 1 is done.
