#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "particles.h"
#include "utils.h"
#include "grid_particle.h"
#include <vector>
#include <chrono>
#include <thread>
#include <random>

const double GRAVITY = 9.80665;
const double EPSILON = 1e-8;
const double PARTICLE_RADIUS = 10;

const double CUTOFF_RANGE = PARTICLE_RADIUS * 5;
const double SKIN_RADIUS = CUTOFF_RANGE * 1.2;
const double SKIN_RADIUS2 = SKIN_RADIUS * SKIN_RADIUS;

const double SPAWN_COOLDOWN_SEC = 0.5;

const float COLLISION_RESTITUTION = 0.65f;
const float COLLISION_POSITIONAL_PERCENT = 0.8f;
const float COLLISION_PENETRATION_SLOP = 0.01f;
const float COLLISION_FRICTION = 0.04f;

// wall bounce tuning
const float WALL_RESTITUTION = 0.7f;