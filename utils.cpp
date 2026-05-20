#include "constants.h"
#include <cmath>

sf::Color randomColour() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(0, 255);

    return sf::Color(distr(gen), distr(gen), distr(gen));
}

std::pair<int, int> cellCoord(const sf::Vector2f& position, float cellSize) {
    return {
        static_cast<int>(std::floor(position.x / cellSize)),
        static_cast<int>(std::floor(position.y / cellSize))
    };
}

float randomCoord() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(-200,200);

    return dist(gen);
}

sf::Vector2f calcDelta(const Particle& particle1, const Particle& particle2){
    sf::Vector2f delta = particle1.position - particle2.position;
    return delta;
}

float calcDistSqr(sf::Vector2f delta) {
    float dist2 = delta.x * delta.x + delta.y * delta.y;
    return dist2;
}



sf::Color velocityToColour(sf::Vector2f velocity) {
    const double maxVelocitySquared = 131072.0;
    const double velocityMagnitude = calcDistSqr(velocity);
    const double velocityRatio = std::clamp(velocityMagnitude / maxVelocitySquared, 0.0, 1.0);

    if (velocityRatio < 0.1) {
        return sf::Color(0, 0, 255);
    }

    const sf::Uint8 red = static_cast<sf::Uint8>(255.0 * velocityRatio);
    return sf::Color(red, 0, 0);
}


    