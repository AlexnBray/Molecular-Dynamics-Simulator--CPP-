#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "particles.h"

std::vector<sf::Vector2f> velvetIntPart(const Particle& particle, float dt);

