#pragma once
#include <SFML/Graphics.hpp>
#include <utility>

sf::Color randomColour();
std::pair<int, int> cellCoord(const sf::Vector2f& position, float cellSize);
float randomCoord();
