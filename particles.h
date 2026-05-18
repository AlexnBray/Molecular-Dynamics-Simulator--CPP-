#pragma once
#include <SFML/Graphics.hpp>

struct Particle {
    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::CircleShape shape;

    Particle(float x, float y, float radius, sf::Color color);
    void draw(sf::RenderWindow& window);
    void update(float dt);
};