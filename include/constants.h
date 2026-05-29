#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "particles.h"
#include "utils.h"
#include "grid_particle.h"
#include "lj_potential.h"
#include "velocity_velvet_int.h"
#include "hud_overlay.h"
#include <cmath>
#include <vector>
#include <chrono>
#include <thread>
#include <random>

constexpr  double GRAVITY = 9.80665;
constexpr  double FLOAT_TOLERANCE = 1e-8;
constexpr  double PARTICLE_RADIUS = 5;
constexpr  double EPSILON = 1e-8;

// LJ Potential constants (scaled to pixel-sized particles)
constexpr  double LJ_EPSILON = 10.0;
constexpr  double LJ_SIGMA = PARTICLE_RADIUS * 2.3; // = diameter to mimic pixel-space math
constexpr  double LJ_CUTOFF = 2.5 * LJ_SIGMA;
constexpr  double COLLISION_CONTACT_RANGE = PARTICLE_RADIUS * 2.0;

constexpr  float PARTICLE_MASS = 1.0f;

// Neighbour list constants
constexpr double NEIGHBOUR_BASE_RANGE = (LJ_CUTOFF > COLLISION_CONTACT_RANGE) ? LJ_CUTOFF : COLLISION_CONTACT_RANGE;
constexpr  double SKIN_RADIUS = NEIGHBOUR_BASE_RANGE * 1.2;
constexpr  double SKIN_RADIUS2 = SKIN_RADIUS * SKIN_RADIUS;
constexpr  double LJ_CUTOFF2 = LJ_CUTOFF * LJ_CUTOFF;

constexpr  double SPAWN_COOLDOWN_SEC = 0.5;

// Collision constants
constexpr  float COLLISION_RESTITUTION = 0.65f;
constexpr  float COLLISION_POSITIONAL_PERCENT = 0.8f;
constexpr  float COLLISION_PENETRATION_SLOP = 0.01f;
constexpr  float COLLISION_FRICTION = 0.04f;

// Wall constants
constexpr  float WALL_RESTITUTION = 0.7f;

constexpr float simWidth        = 1200.0f;
constexpr float simHeight       = 800.0f;
constexpr float hudWidth        = 300.0f;
constexpr float bottomHudHeight = 170.0f;
constexpr float windowWidth     = simWidth + hudWidth;
constexpr float windowHeight    = 970.0f;

