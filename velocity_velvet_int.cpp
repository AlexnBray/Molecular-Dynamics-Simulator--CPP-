#include "constants.h"

std::vector<sf::Vector2f> velvetIntPart(const Particle& particle, float dt){
    const sf::Vector2f acceleration = particle.force / PARTICLE_MASS;
    const sf::Vector2f newVelocity = particle.velocity + acceleration * dt;
    const sf::Vector2f newPosition = particle.position + newVelocity * dt;

    return {newVelocity, newPosition};

            /* -----VELOCITY -----
    𝑣(𝑡+Δ𝑡/2)=𝑣(𝑡)+12*𝑎(𝑡)   */
   
    /* -----POSITION -----
    𝑥(𝑡+Δ𝑡)=𝑥(𝑡)+𝑣(𝑡+Δ𝑡/2)   */


    /* ----- ACCELERATION -----
    v(𝑡+Δ𝑡)=𝑣(𝑡+Δ𝑡2)+1/2* a(𝑡+Δ𝑡2) * Δt */
}