#include "constants.h"

using neighbourVector = std::vector<std::vector<int>>;
neighbourVector buildNeighbourList(const std::vector<Particle>& particles) {
    int n = particles.size();
    neighbourVector list(n);

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            float dx = particles[j].position.x - particles[i].position.x;
            float dy = particles[j].position.y - particles[i].position.y;
            float dist2 = dx*dx + dy*dy;

            if (dist2 < SKIN_RADIUS2) {
                list[i].push_back(j);
                list[j].push_back(i);
            }
        }
    }
    return list;
}