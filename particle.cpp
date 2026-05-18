#include "particles.h"
#include <SFML/Graphics.hpp>

Particle::Particle(float x, float y, float radius, sf::Color color) {
    shape.setRadius(radius);
    shape.setFillColor(color);
    shape.setPosition({x, y});
    position = {x, y};
    velocity = {0.f, 0.f};
}

void Particle::draw(sf::RenderWindow& window) {
    window.draw(shape);
}