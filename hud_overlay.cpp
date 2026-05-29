#include "constants.h"
#include "hud_overlay.h"
#include <algorithm>
#include <cmath>

HudOverlay::HudOverlay(const sf::Font& font)
    : graphTitleText_("Energy trend", font, 18),
      rangeText_("Range: n/a", font, 15),
      particlesText_("particles", font, 18),
      gravityText_("gravity", font, 18),
      fpsText_("fps", font, 18),
      physicsText_("physics", font, 18),
      kineticText_("kinetic", font, 18),
      ljText_("lj", font, 18),
      graphMaxSamples_(320) {
    textPanel_.setSize({hudWidth - 16.0f, simHeight - 16.0f});
    textPanel_.setPosition({simWidth + 8.0f, 8.0f});
    textPanel_.setFillColor(sf::Color(19, 25, 34));
    textPanel_.setOutlineColor(sf::Color(58, 78, 98));
    textPanel_.setOutlineThickness(1.0f);

    graphPanel_.setSize({windowWidth - 16.0f, bottomHudHeight - 16.0f});
    graphPanel_.setPosition({8.0f, simHeight + 8.0f});
    graphPanel_.setFillColor(sf::Color(14, 21, 31));
    graphPanel_.setOutlineColor(sf::Color(61, 82, 107));
    graphPanel_.setOutlineThickness(1.0f);

    const sf::Color textColor(240, 244, 255);
    graphTitleText_.setFillColor(textColor);
    rangeText_.setFillColor(sf::Color(170, 195, 225));
    particlesText_.setFillColor(textColor);
    gravityText_.setFillColor(textColor);
    fpsText_.setFillColor(textColor);
    physicsText_.setFillColor(textColor);
    kineticText_.setFillColor(textColor);
    ljText_.setFillColor(textColor);

    graphTitleText_.setPosition({graphPanel_.getPosition().x + 14.0f, graphPanel_.getPosition().y + 8.0f});
    rangeText_.setPosition({graphPanel_.getPosition().x + graphPanel_.getSize().x - 250.0f, graphPanel_.getPosition().y + 10.0f});

    const float left = textPanel_.getPosition().x + 12.0f;
    const float top = textPanel_.getPosition().y + 14.0f;
    const float row = 30.0f;
    particlesText_.setPosition({left, top});
    gravityText_.setPosition({left, top + row});
    fpsText_.setPosition({left, top + row * 2.0f});
    physicsText_.setPosition({left, top + row * 3.0f});
    kineticText_.setPosition({left, top + row * 4.0f});
    ljText_.setPosition({left, top + row * 5.0f});
}

//import clear button here

void HudOverlay::update(int particleCount, double gravity, float fps, float physicsMs, double kineticEnergy, double ljEnergy) {
    particlesText_.setString("Particles: " + std::to_string(particleCount));
    gravityText_.setString("Gravity: " + std::to_string(std::round(gravity * 100.0) / 100.0) + "px/s^2");
    fpsText_.setString("FPS: " + std::to_string(static_cast<int>(std::round(fps))));
    physicsText_.setString("Physics: " + std::to_string(std::round(physicsMs * 100.0f) / 100.0f) + "ms");
    kineticText_.setString("Kinetic E: " + std::to_string(std::round(kineticEnergy * 100.0) / 100.0));
    ljText_.setString("LJ E: " + std::to_string(std::round(ljEnergy * 100.0) / 100.0));

    const float totalEnergy = static_cast<float>(kineticEnergy + ljEnergy);
    energyHistory_.push_back(totalEnergy);
    while (energyHistory_.size() > graphMaxSamples_) {
        energyHistory_.pop_front();
    }

    if (energyHistory_.empty()) {
        rangeText_.setString("Range: n/a");
        return;
    }

    const auto minmax = std::minmax_element(energyHistory_.begin(), energyHistory_.end());
    const float roundedMin = std::round((*minmax.first) * 10.0f) / 10.0f;
    const float roundedMax = std::round((*minmax.second) * 10.0f) / 10.0f;
    rangeText_.setString("Range: " + std::to_string(roundedMin) + " - " + std::to_string(roundedMax));
}

void HudOverlay::draw(sf::RenderWindow& window) const {
    window.draw(textPanel_);
    window.draw(graphPanel_);
    window.draw(graphTitleText_);
    window.draw(rangeText_);
    window.draw(particlesText_);
    window.draw(gravityText_);
    window.draw(fpsText_);
    window.draw(physicsText_);
    window.draw(kineticText_);
    window.draw(ljText_);

    const float left = graphPanel_.getPosition().x + 14.0f;
    const float top = graphPanel_.getPosition().y + 42.0f;
    const float width = graphPanel_.getSize().x - 28.0f;
    const float height = graphPanel_.getSize().y - 52.0f;

    sf::VertexArray guideLines(sf::Lines, 8);
    for (int i = 0; i < 4; ++i) {
        const float y = top + (height / 3.0f) * static_cast<float>(i);
        guideLines[i * 2].position = {left, y};
        guideLines[i * 2 + 1].position = {left + width, y};
        guideLines[i * 2].color = sf::Color(35, 50, 68);
        guideLines[i * 2 + 1].color = sf::Color(35, 50, 68);
    }
    window.draw(guideLines);

    if (energyHistory_.size() < 2) {
        return;
    }

    const auto minmax = std::minmax_element(energyHistory_.begin(), energyHistory_.end());
    const float minEnergy = *minmax.first;
    const float maxEnergy = *minmax.second;
    const float range = std::max(maxEnergy - minEnergy, 1e-6f);

    sf::VertexArray line(sf::LineStrip, energyHistory_.size());
    for (std::size_t i = 0; i < energyHistory_.size(); ++i) {
        const float t = static_cast<float>(i) / static_cast<float>(energyHistory_.size() - 1);
        const float x = left + t * width;
        const float normalized = (energyHistory_[i] - minEnergy) / range;
        const float y = top + (1.0f - normalized) * height;
        line[i].position = {x, y};
        line[i].color = sf::Color(94, 214, 255);
    }

    window.draw(line);
}
