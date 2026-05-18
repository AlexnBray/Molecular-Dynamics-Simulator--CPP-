#include "particles.h"
#include "constants.h"

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

void Particle::update(float dt){
    velocity.y += GRAVITY;
    position += dt * velocity;
    shape.setPosition(position);
}

void Particle::checkBounds(float width, float height) {
    float r = shape.getRadius();

    if (position.x + r * 2 > width) {
        position.x = width - r * 2;
        velocity.x = 0.f;
    }
    if (position.x < 0.f) {
        position.x = 0.f;
        velocity.x = 0.f;
    }
    if (position.y + r * 2 > height) {
        position.y = height - r * 2;
        velocity.y = 0.f;
    }
    if (position.y < 0.f) {
        position.y = 0.f;
        velocity.y = 0.f;
    }
    shape.setPosition(position);
}

void Particle::checkOverlap(){

    
}