#include "constants.h"

int calcLennardJonesPotential(const Particle& particle1, const Particle& particle2){

    double force {};
    double lj_epsilon;
    sf::Vector2f delta = calcDelta(particle1, particle2);

    force = 24*lj_epsilon;

    return 0;
}