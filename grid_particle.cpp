#include "constants.h"
#include <unordered_map>
#include <cstdint>
#include <cmath>
#include <algorithm>

using neighbourVector = std::vector<std::vector<int>>;
neighbourVector buildNeighbourList(const std::vector<Particle>& particles) {
    const int n = static_cast<int>(particles.size());
    neighbourVector list(n);

    if (n == 0) {
        return list;
    }

    const float cellSize = static_cast<float>(SKIN_RADIUS); // grid bucket width

    auto cellKey = [](int cx, int cy) -> std::int64_t {
        return (static_cast<std::int64_t>(cx) << 32) ^
               static_cast<std::uint32_t>(cy);
    };

    std::unordered_map<std::int64_t, std::vector<int>> grid; // cell -> particle ids
    grid.reserve(static_cast<std::size_t>(n) * 2);

    for (int i = 0; i < n; ++i) {
        const auto [cx, cy] = cellCoord(particles[i].position, cellSize);
        grid[cellKey(cx, cy)].push_back(i); // put each particle into one cell
    }

    for (int i = 0; i < n; ++i) {
        const auto [cx, cy] = cellCoord(particles[i].position, cellSize);

        for (int ox = -1; ox <= 1; ++ox) {
            for (int oy = -1; oy <= 1; ++oy) {
                const auto it = grid.find(cellKey(cx + ox, cy + oy));
                if (it == grid.end()) {
                    continue;
                }

                for (const int j : it->second) { // only local candidates now
                    if (j <= i) {
                        continue;
                    }

                    const float dx = particles[j].position.x - particles[i].position.x;
                    const float dy = particles[j].position.y - particles[i].position.y;
                    const float dist2 = dx * dx + dy * dy;

                    if (dist2 < SKIN_RADIUS2) { // final distance check
                        list[i].push_back(j);
                        list[j].push_back(i);
                    }
                }
            }
        }
    }
    return list;
}

void calcNeighbourInteractions(std::vector<Particle>& particles, const neighbourVector& neighbours) {
    const int n = static_cast<int>(particles.size());
    if (static_cast<int>(neighbours.size()) != n) return;

    // reset forces
    for (int i = 0; i < n; ++i)
        particles[i].force = {0.f, 0.f};

    const float minDistance  = static_cast<float>(PARTICLE_RADIUS * 2.0);
    const float minDistance2 = minDistance * minDistance;

    for (int i = 0; i < n; ++i) {
        for (const int j : neighbours[i]) {
            if (j <= i || j < 0 || j >= n) continue;

            const sf::Vector2f delta = calcDelta(particles[j], particles[i]);
            const float dist2 = calcDistSqr(delta);

            // --- LJ force ---
            if (dist2 < static_cast<float>(LJ_CUTOFF2) && dist2 > static_cast<float>(FLOAT_TOLERANCE)) {
                const double fmag = calcLennardJonesForce(dist2);
                const sf::Vector2f fvec = {
                    static_cast<float>(fmag * delta.x),
                    static_cast<float>(fmag * delta.y)
                };
                particles[i].force -= fvec;
                particles[j].force += fvec;
            }

            // --- collision resolution ---
            if (dist2 < minDistance2) {
                float dist = std::sqrt(dist2);
                sf::Vector2f normal;

                if (dist > static_cast<float>(FLOAT_TOLERANCE)) {
                    normal = calcDelta(particles[j], particles[i]) / dist;
                } else {
                    normal = {1.0f, 0.0f};
                    dist   = 0.0f;
                }

                const float overlap = minDistance - dist;
                const float correctionMag = std::max(overlap - COLLISION_PENETRATION_SLOP, 0.0f)
                                           * COLLISION_POSITIONAL_PERCENT * 0.5f;
                const sf::Vector2f correction = normal * correctionMag;

                particles[i].position -= correction;
                particles[j].position += correction;

                const sf::Vector2f rv = particles[j].velocity - particles[i].velocity;
                const float velAlongNormal = rv.x * normal.x + rv.y * normal.y;

                if (velAlongNormal < 0.0f) {
                    const float impulseMag = -((1.0f + COLLISION_RESTITUTION) * velAlongNormal) * 0.5f;
                    const sf::Vector2f impulse = normal * impulseMag;
                    particles[i].velocity -= impulse;
                    particles[j].velocity += impulse;

                    sf::Vector2f tangent = rv - normal * velAlongNormal;
                    const float tangentLen2 = tangent.x * tangent.x + tangent.y * tangent.y;
                    if (tangentLen2 > static_cast<float>(FLOAT_TOLERANCE)) {
                        tangent /= std::sqrt(tangentLen2);
                        const float velAlongTangent= rv.x * tangent.x + rv.y * tangent.y;
                        float frictionImpulseMag = -(velAlongTangent) * 0.5f;
                        const float maxFriction = impulseMag * COLLISION_FRICTION;
                        frictionImpulseMag = std::clamp(frictionImpulseMag, -maxFriction, maxFriction);
                        particles[i].velocity -= tangent * frictionImpulseMag;
                        particles[j].velocity += tangent * frictionImpulseMag;
                    }
                }

                particles[i].shape.setPosition(particles[i].position);
                particles[j].shape.setPosition(particles[j].position);
            }
        }
    }
}