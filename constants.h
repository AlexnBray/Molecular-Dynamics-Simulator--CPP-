#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "particles.h"
#include "utils.h"
#include "grid_particle.h"
#include "lj_potential.h"
#include <vector>
#include <chrono>
#include <thread>
#include <random>

const double GRAVITY         = 9.80665;
const double FLOAT_TOLERANCE = 1e-8;
const double PARTICLE_RADIUS = 10;
const double EPSILON = 1e-8;

// LJ Potential constants
const double LJ_EPSILON      = 1.0;
const double LJ_SIGMA        = 1.0;
const double LJ_CUTOFF       = 2.5 * LJ_SIGMA;

// Neighbour list constants
const double SKIN_RADIUS     = LJ_CUTOFF * 1.2;
const double SKIN_RADIUS2    = SKIN_RADIUS * SKIN_RADIUS;
const double LJ_CUTOFF2      = LJ_CUTOFF * LJ_CUTOFF;

const double SPAWN_COOLDOWN_SEC = 0.5;

// Collision constants
const float COLLISION_RESTITUTION        = 0.65f;
const float COLLISION_POSITIONAL_PERCENT = 0.8f;
const float COLLISION_PENETRATION_SLOP   = 0.01f;
const float COLLISION_FRICTION           = 0.04f;

// Wall constants
const float WALL_RESTITUTION = 0.7f;