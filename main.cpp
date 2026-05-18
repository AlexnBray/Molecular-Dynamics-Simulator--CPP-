#include <iostream>
#include "constants.h"
#include <SFML/Graphics.hpp>
#include "particles.h"
#include <vector>
#include <chrono>
#include <thread>

int count {};
sf::Font MyFont;

float clickTime(std::chrono::steady_clock::time_point last){
    auto now = std::chrono::steady_clock::now();
    float elapsed = std::chrono::duration<float>(now - last).count();
    return elapsed;
}

int main() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Particle Simulation");
    std::vector<Particle> particles;

    MyFont.loadFromFile("fonts/AovelSansRounded-rdDL.ttf");
    sf::Text Text("particles", MyFont, 20);
    Text.setFillColor(sf::Color::Black);
    Text.setPosition({10.f, 10.f});

    auto lastSpawn = std::chrono::steady_clock::now();
    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        float dt = clock.restart().asSeconds();
        for (auto& p : particles)
            p.update(dt);   

        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && clickTime(lastSpawn) >= 0.05f) {
            count++;
            lastSpawn = std::chrono::steady_clock::now();;
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            std::cout << "clicked at " << mousePos.x << ", " << mousePos.y << std::endl;
            particles.emplace_back(mousePos.x, mousePos.y, 20.f, sf::Color(61, 225, 189));
        }

        window.clear(sf::Color::White);
        Text.setString("Particles: " + std::to_string(count));
        for (auto& p : particles)
            p.draw(window);
        window.draw(Text);
        window.display();
    }

    return 0;
}