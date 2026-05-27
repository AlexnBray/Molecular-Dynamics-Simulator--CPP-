#pragma once
#include <SFML/Graphics.hpp>
#include <deque>

class HudOverlay {
public:
    explicit HudOverlay(const sf::Font& font);
    void update(int particleCount, double gravity, float fps, float physicsMs, double kineticEnergy, double ljEnergy);
    void draw(sf::RenderWindow& window) const;

private:
    sf::RectangleShape textPanel_;
    sf::RectangleShape graphPanel_;
    sf::Text graphTitleText_;
    sf::Text rangeText_;
    sf::Text particlesText_;
    sf::Text gravityText_;
    sf::Text fpsText_;
    sf::Text physicsText_;
    sf::Text kineticText_;
    sf::Text ljText_;
    std::deque<float> energyHistory_;
    std::size_t graphMaxSamples_;
};
