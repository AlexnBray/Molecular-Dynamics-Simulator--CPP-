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
        if (velocity.x > 0.f) {
            velocity.x = -velocity.x * WALL_RESTITUTION;
        }
    }
    if (position.x < 0.f) {
        position.x = 0.f;
        if (velocity.x < 0.f) {
            velocity.x = -velocity.x * WALL_RESTITUTION;
        }
    }
    if (position.y + r * 2 > height) {
        position.y = height - r * 2;
        if (velocity.y > 0.f) {
            velocity.y = -velocity.y * WALL_RESTITUTION;
        }
    }
    if (position.y < 0.f) {
        position.y = 0.f;
        if (velocity.y < 0.f) {
            velocity.y = -velocity.y * WALL_RESTITUTION;
        }
    }
    shape.setPosition(position);
}

void Particle::checkOverlap(){
    
}
