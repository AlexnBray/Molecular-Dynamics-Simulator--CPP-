#include <iostream>
#include "constants.h"
#include <SFML/Graphics.hpp>
#include "particles.h"
#include <vector>

int count {};

int main() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Particle Simulation");

    std::vector<Particle> particles;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            count++;
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            std::cout << "clicked at " << mousePos.x << ", " << mousePos.y << std::endl;
            particles.emplace_back(mousePos.x, mousePos.y, 20.f, sf::Color(61, 225, 189));
        }

        window.clear(sf::Color::White);
        for (auto& p : particles)
            p.draw(window);
        window.display();
    }

    return 0;
}