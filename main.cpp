#include <iostream>
#include "constants.h"
#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Particle Simulation");

    sf::CircleShape particle;
    sf::Color colour(61,225,189);
    particle.setRadius(50.f); // radius
    particle.setFillColor(colour);
    particle.setPosition({400.f, 300.f}); //coords

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);
        window.draw(particle);
        window.display();
    }

    return 0;
}