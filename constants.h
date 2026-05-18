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