#include "constants.h"

int count {};
sf::Font MyFont;

double computeLJPotentialEnergy(const std::vector<Particle>& particles, const neighbourVector& neighbours) {
    double totalPotential = 0.0;
    const int n = static_cast<int>(particles.size());
    if (static_cast<int>(neighbours.size()) != n) {
        return totalPotential;
    }

    for (int i = 0; i < n; ++i) {
        for (const int j : neighbours[i]) {
            if (j <= i || j < 0 || j >= n) {
                continue;
            }

            const sf::Vector2f delta = particles[j].position - particles[i].position;
            const double dist2 = static_cast<double>(delta.x * delta.x + delta.y * delta.y);
            if (dist2 <= FLOAT_TOLERANCE || dist2 >= LJ_CUTOFF2) {
                continue;
            }

            const double sr2 = (LJ_SIGMA * LJ_SIGMA) / dist2;
            const double sr6 = sr2 * sr2 * sr2;
            const double sr12 = sr6 * sr6;
            totalPotential += 4.0 * LJ_EPSILON * (sr12 - sr6);
        }
    }

    return totalPotential;
}

int main() {
    sf::RenderWindow window(sf::VideoMode({static_cast<unsigned int>(windowWidth), static_cast<unsigned int>(windowHeight)}), "Particle Simulation");
    std::vector<Particle> particles;
    window.setFramerateLimit(60);

    sf::RectangleShape simBox({simWidth, simHeight});
    simBox.setPosition({0.0f, 0.0f});
    simBox.setFillColor(sf::Color::Black);
    simBox.setOutlineColor(sf::Color(70, 70, 70));
    simBox.setOutlineThickness(1.0f);

    MyFont.loadFromFile("fonts/AovelSansRounded-rdDL.ttf");
    HudOverlay hud(MyFont);
    
    bool isPaused = false;

    constexpr float fixedDt = 1.0f / 60.0f;
    float accumulator = 0.0f;
    float fpsRolling = 60.0f;
    float physicsStepMs = 0.0f;
    double totalKineticEnergy = 0.0;
    double totalLJPotentialEnergy = 0.0;
    neighbourVector latestNeighbours;

    sf::Clock clock;
    auto lastSpawn = std::chrono::steady_clock::now();

    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }


        const float frameSeconds = clock.restart().asSeconds();
        if (frameSeconds > 0.0f) {
            const float fpsInstant = 1.0f / frameSeconds;
            fpsRolling = fpsRolling * 0.9f + fpsInstant * 0.1f;
        }

        accumulator += frameSeconds;

        if (accumulator > 0.25f) accumulator = 0.25f;

        const auto physicsStart = std::chrono::steady_clock::now();
        while (accumulator >= fixedDt) {
            neighbourVector neighbours = buildNeighbourList(particles);
            latestNeighbours = neighbours;

            for (int i = 0; i < 3; ++i) {
                calcNeighbourInteractions(particles, neighbours);
            }

            for (auto& p : particles)
                p.update(fixedDt);

            for (auto& p : particles)
                p.checkBounds(simWidth, simHeight);

            accumulator -= fixedDt;
        }
        const auto physicsEnd = std::chrono::steady_clock::now();
        physicsStepMs = std::chrono::duration<float, std::milli>(physicsEnd - physicsStart).count();

        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && clickTime(lastSpawn) >= SPAWN_COOLDOWN_SEC) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            if (mousePos.x >= 0 && mousePos.x < simWidth && mousePos.y >= 0 && mousePos.y < simHeight) {
            count += 500;
            lastSpawn = std::chrono::steady_clock::now();
            std::cout << "clicked at " << mousePos.x << ", " << mousePos.y << std::endl;

            for (int i = 0; i < 501; i++) {
                sf::Vector2f randomDist = {randomDistributionX(), randomDistributionY()};
                sf::Vector2f worldcoords = window.mapPixelToCoords(static_cast<sf::Vector2i>(randomDist));
                if (worldcoords.x >= 0.0f && worldcoords.x < simWidth && worldcoords.y >= 0.0f && worldcoords.y < simHeight) {
                    particles.emplace_back(worldcoords.x, worldcoords.y, PARTICLE_RADIUS, randomColour());
                }
            }
            }
        }

        totalKineticEnergy = 0.0;
        for (const auto& p : particles) {
            totalKineticEnergy += p.kineticEnergy;
        }
        totalLJPotentialEnergy = computeLJPotentialEnergy(particles, latestNeighbours);

        window.clear(sf::Color::Black);
        window.draw(simBox);
        hud.update(count, GRAVITY, fpsRolling, physicsStepMs, totalKineticEnergy, totalLJPotentialEnergy);

        for (auto& p : particles)
            p.draw(window);

        hud.draw(window);
        window.display();
    }

    return 0;

}
