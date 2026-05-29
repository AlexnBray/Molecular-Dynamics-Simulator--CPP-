#include "constants.h"
#include <algorithm>
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

float clickTime(std::chrono::steady_clock::time_point last){
    auto now = std::chrono::steady_clock::now();
    float elapsed = std::chrono::duration<float>(now - last).count();
    return elapsed;
}

float randomDistributionX() { // 1200
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(50.0, 1150.0);

    return dist(gen);
}

float randomDistributionY() { // 800
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(20.0, 600.0);

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

sf::Color gradientCalc(const sf::Color& current_colour, const sf::Color& end_colour, double ratio){
    ratio = std::clamp(ratio, 0.0, 1.0);
    const sf::Uint8 red = current_colour.r + (end_colour.r - current_colour.r) * ratio;
    const sf::Uint8 green = current_colour.g + (end_colour.g - current_colour.g) * ratio;
    const sf::Uint8 blue = current_colour.b + (end_colour.b - current_colour.b) * ratio;

    return sf::Color(red, green, blue);
}



sf::Color velocityToColour(sf::Vector2f velocity) {
    const double maxVelocitySquared = 1500.0;
    const double velocityMagnitude = calcDistSqr(velocity);
    const double velocityRatio = std::clamp(velocityMagnitude / maxVelocitySquared, 0.0, 1.0);

    const sf::Color coldBlue(0, 0, 255);
    const sf::Color lightRed(255, 220, 220);
    const sf::Color hotRed(255, 0, 0);

    if (velocityRatio < 0.5) 
        return gradientCalc(coldBlue, lightRed, velocityRatio / 0.5);

    return gradientCalc(lightRed, hotRed, (velocityRatio - 0.5) / 0.5);
}


    