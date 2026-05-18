#include "constants.h"
#include <unordered_map>
#include <cstdint>
#include <cmath>

using neighbourVector = std::vector<std::vector<int>>;
neighbourVector buildNeighbourList(const std::vector<Particle>& particles) {
    const int n = static_cast<int>(particles.size());
    neighbourVector list(n);

    if (n == 0) {
        return list;
    }

    const float cellSize = static_cast<float>(SKIN_RADIUS);

    auto cellKey = [](int cx, int cy) -> std::int64_t {
        return (static_cast<std::int64_t>(cx) << 32) ^
               static_cast<std::uint32_t>(cy);
    };

    std::unordered_map<std::int64_t, std::vector<int>> grid;
    grid.reserve(static_cast<std::size_t>(n) * 2);

    for (int i = 0; i < n; ++i) {
        const auto [cx, cy] = cellCoord(particles[i].position, cellSize);
        grid[cellKey(cx, cy)].push_back(i);
    }

    for (int i = 0; i < n; ++i) {
        const auto [cx, cy] = cellCoord(particles[i].position, cellSize);

        for (int ox = -1; ox <= 1; ++ox) {
            for (int oy = -1; oy <= 1; ++oy) {
                const auto it = grid.find(cellKey(cx + ox, cy + oy));
                if (it == grid.end()) {
                    continue;
                }

                for (const int j : it->second) {
                    if (j <= i) {
                        continue;
                    }

                    const float dx = particles[j].position.x - particles[i].position.x;
                    const float dy = particles[j].position.y - particles[i].position.y;
                    const float dist2 = dx * dx + dy * dy;

                    if (dist2 < SKIN_RADIUS2) {
                        list[i].push_back(j);
                        list[j].push_back(i);
                    }
                }
            }
        }
    }
    return list;
}

void neighbourOverlap(std::vector<Particle>& particles, const neighbourVector& neighbours) {
    const int n = static_cast<int>(particles.size());
    if (static_cast<int>(neighbours.size()) != n) {
        return;
    }

    const float minDistance = static_cast<float>(PARTICLE_RADIUS * 2.0);
    const float minDistance2 = minDistance * minDistance;

    for (int i = 0; i < n; ++i) {
        for (const int j : neighbours[i]) {
            if (j <= i || j < 0 || j >= n) {
                continue;
            }

            sf::Vector2f delta = particles[j].position - particles[i].position;
            float dist2 = delta.x * delta.x + delta.y * delta.y;

            if (dist2 >= minDistance2) {
                continue;
            }

            float dist = std::sqrt(dist2);
            sf::Vector2f normal;

            if (dist > static_cast<float>(EPSILON)) {
                normal = delta / dist;
            } else {
                normal = {1.0f, 0.0f};
                dist = 0.0f;
            }

            const float overlap = minDistance - dist;
            const sf::Vector2f correction = normal * (overlap * 0.5f);

            particles[i].position -= correction;
            particles[j].position += correction;
            particles[i].shape.setPosition(particles[i].position);
            particles[j].shape.setPosition(particles[j].position);
        }
    }
}