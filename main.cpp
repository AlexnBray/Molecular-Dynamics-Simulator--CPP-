#include "constants.h"

int count {};
sf::Font MyFont;

float clickTime(std::chrono::steady_clock::time_point last){
    auto now = std::chrono::steady_clock::now();
    float elapsed = std::chrono::duration<float>(now - last).count();
    return elapsed;
}

int main() {
    sf::RenderWindow window(sf::VideoMode({1200, 800}), "Particle Simulation");
    std::vector<Particle> particles;
    window.setFramerateLimit(60);

    MyFont.loadFromFile("fonts/AovelSansRounded-rdDL.ttf");
    sf::Text Text("particles", MyFont, 20);
    Text.setFillColor(sf::Color::White);
    Text.setPosition({10.f, 10.f});

    sf::Text gravityText("gravity", MyFont, 20);
    gravityText.setFillColor(sf::Color::White);
    gravityText.setPosition({10.f, 30.f});


    constexpr float fixedDt = 1.0f / 60.0f;
    float accumulator = 0.0f;

    sf::Clock clock;
    auto lastSpawn = std::chrono::steady_clock::now();

    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }


        accumulator += clock.restart().asSeconds();

        if (accumulator > 0.25f) accumulator = 0.25f;

        while (accumulator >= fixedDt) {
            neighbourVector neighbours = buildNeighbourList(particles);

            for (int i = 0; i < 3; ++i) {
                calcNeighbourInteractions(particles, neighbours);
            }

            for (auto& p : particles)
                p.update(fixedDt);

            for (auto& p : particles)
                p.checkBounds(1200, 800);

            accumulator -= fixedDt;
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && clickTime(lastSpawn) >= SPAWN_COOLDOWN_SEC) {
            count += 500;
            lastSpawn = std::chrono::steady_clock::now();
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            std::cout << "clicked at " << mousePos.x << ", " << mousePos.y << std::endl;

            for (int i = 0; i < 501; i++) {
                sf::Vector2f randomDist = {randomDistributionX(), randomDistributionY()};
                sf::Vector2f worldcoords = window.mapPixelToCoords(static_cast<sf::Vector2i>(randomDist));
                particles.emplace_back(worldcoords.x, worldcoords.y, PARTICLE_RADIUS, randomColour());
            }
        }

        window.clear(sf::Color::Black);
        Text.setString("Particles: " + std::to_string(count));
        gravityText.setString("Gravity: " + std::to_string(std::round(GRAVITY * 100.0) / 100.0) + "px/s^2");

        for (auto& p : particles)
            p.draw(window);

        window.draw(Text);
        window.draw(gravityText);
        window.display();
    }

    return 0;
}
