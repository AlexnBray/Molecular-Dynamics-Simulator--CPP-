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
    std::uniform_int_distribution<> dist(-40,40);

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






    