#pragma once
#include <SFML/Graphics.hpp>
#include <utility>

sf::Color randomColour();
std::pair<int, int> cellCoord(const sf::Vector2f& position, float cellSize);
float randomCoord();
float calcDistSqr(sf::Vector2f delta);
sf::Vector2f calcDelta(const Particle& particle1, const Particle& particle2);
sf::Color velocityToColour(sf::Vector2f velocity);
sf::Color gradientCalc(const sf::Color& current_colour, const sf::Color& end_colour, double ratio);
