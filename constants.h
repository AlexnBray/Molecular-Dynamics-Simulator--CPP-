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

const unsigned int WINDOW_WIDTH = 800;
const unsigned int WINDOW_HEIGHT = 600;
const float SPAWN_COOLDOWN_SEC = 0.05f;
const unsigned int HUD_FONT_SIZE = 20;

//grid_particle constants
const int COLLISION_SOLVER_ITERS = 3;
const float COLLISION_RESTITUTION = 0.05f;
const float COLLISION_POSITIONAL_PERCENT = 0.8f;
const float COLLISION_PENETRATION_SLOP = 0.01f;
const float COLLISION_FRICTION = 0.15f;