#include "constants.h"

std::vector<sf::Vector2f> velvetIntPart(Particle particle, float dt){
    
    double veloc_x, veloc_y;
    double position_x {}, position_y;
    double accleration_x {}, position_y;
    
    veloc_x = particle.velocity.x + 12 * particle.force.x/ PARTICLE_MASS;
    veloc_x = particle.velocity.y + 12 * particle.force.y/ PARTICLE_MASS;
    sf::Vector2f velocity_vect= {veloc_x, veloc_y};

    position_x = particle.position.x + veloc_x;
    position_y = particle.position.y + veloc_y;
    sf::Vector2f position_vect = {position_x, position_y};

    

        /* -----VELOCITY -----
    𝑣(𝑡+Δ𝑡/2)=𝑣(𝑡)+12𝑎(𝑡)   */
   
    /* -----POSITION -----
    𝑥(𝑡+Δ𝑡)=𝑥(𝑡)+𝑣(𝑡+Δ𝑡/2)   */


    /* ----- ACCELERATION -----
    v(𝑡+Δ𝑡)=𝑣(𝑡+Δ𝑡2)+1/2* a(𝑡+Δ𝑡2) * Δt */


}