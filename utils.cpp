#include "constants.h"

sf::Color randomColour() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(0, 255);

    return sf::Color(distr(gen), distr(gen), distr(gen));
}
    