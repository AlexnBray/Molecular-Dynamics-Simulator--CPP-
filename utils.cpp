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


    