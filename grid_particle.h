#pragma once
#include <SFML/Graphics.hpp>
#include "constants.h"


using neighbourVector = std::vector<std::vector<int>>;

neighbourVector buildNeighbourList(const std::vector<Particle>& particles);
void neighbourOverlap(std::vector<Particle>& particles, const neighbourVector& neighbours);

