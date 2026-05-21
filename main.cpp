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

    MyFont.loadFromFile("fonts/AovelSansRounded-rdDL.ttf");
    sf::Text Text("particles", MyFont, 20);
    Text.setFillColor(sf::Color::White);
    Text.setPosition({10.f, 10.f});

    sf::Text gravityText("gravity", MyFont, 20);
    gravityText.setFillColor(sf::Color::White);
    gravityText.setPosition({10.f, 30.f});


    sf::Clock clock;
    auto lastSpawn = std::chrono::steady_clock::now();
    

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        neighbourVector neighbours = buildNeighbourList(particles);

        for (int i = 0; i < 3; ++i) {
            calcNeighbourInteractions(particles, neighbours);
        }

        float dt = clock.restart().asSeconds();
        for (auto& p : particles) //auto& references the p without copying it (also allowing for the
            p.update(dt);   //      compiler to decide what data type it is)
            //particle spawn logic
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && clickTime(lastSpawn) >= SPAWN_COOLDOWN_SEC) {
            count += 500; //check how many particles are spawned
            lastSpawn = std::chrono::steady_clock::now();;
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            std::cout << "clicked at " << mousePos.x << ", " << mousePos.y << std::endl;
            for (int i=0; i<501; i++)
                particles.emplace_back(mousePos.x + randomCoord(), mousePos.y + randomCoord(), PARTICLE_RADIUS, randomColour());
        }

        window.clear(sf::Color::Black);
        Text.setString("Particles: " + std::to_string(count));
        gravityText.setString("Gravity: " + std::to_string(GRAVITY) + "px/s^2");
        for (auto& p : particles){
            p.draw(window);
            p.checkBounds(1200, 800);
        }
        window.draw(Text);
        window.draw(gravityText);
        window.display();


    }

    return 0;
}
