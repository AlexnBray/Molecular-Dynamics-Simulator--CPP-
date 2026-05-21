#include "particles.h"
#include "constants.h"

Particle::Particle(float x, float y, float radius, sf::Color color) {
    shape.setRadius(radius);
    shape.setFillColor(color);
    shape.setPosition({x, y});
    position = {x, y};
    velocity = {0.f, 0.f};
    force = {0.f, 0.f};
}

void Particle::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

void Particle::update(float dt){
    const sf::Vector2f gravityForce = {0.0f, static_cast<float>(PARTICLE_MASS * GRAVITY)};
    const sf::Vector2f totalForce = force + gravityForce;
    const sf::Vector2f acceleration = totalForce / PARTICLE_MASS;

    velocity += acceleration * dt;
    /* -----VELOCITY -----
    𝑣(𝑡+Δ𝑡2)=𝑣(𝑡)+12𝑎(𝑡)   */
   
    /* -----POSITION -----
    𝑥(𝑡+Δ𝑡)=𝑥(𝑡)+𝑣(𝑡+Δ𝑡2)   */


    /* -----POSITION -----
    v(𝑡+Δ𝑡)=𝑣(𝑡+Δ𝑡2)+1/2* a(𝑡+Δ𝑡2) * Δt */

    position += dt * velocity;
    shape.setFillColor(velocityToColour(velocity));
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
