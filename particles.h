#pragma once
#include <SFML/Graphics.hpp>

struct Particle {
    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::CircleShape shape;
    sf::Vector2f force;


    Particle(float x, float y, float radius, sf::Color color);
    void draw(sf::RenderWindow& window);
    void update(float dt);
    void checkBounds(float width, float height);
    void checkOverlap();
};