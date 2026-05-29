#include "constants.h"
#include <cmath>
#include <iostream>
#include <string>

namespace {

bool approx(double a, double b, double eps = 1e-5) {
    return std::abs(a - b) <= eps;
}

int failures = 0;

void check(bool condition, const std::string& message) {
    if (!condition) {
        ++failures;
        std::cerr << "[FAIL] " << message << '\n';
    }
}

void testDistanceHelpers() {
    const sf::Vector2f vec = {3.0f, 4.0f};
    check(approx(calcDistSqr(vec), 25.0), "calcDistSqr({3,4}) should be 25");

    Particle p1(10.0f, 5.0f, static_cast<float>(PARTICLE_RADIUS), sf::Color::White);
    Particle p2(4.0f, -1.0f, static_cast<float>(PARTICLE_RADIUS), sf::Color::White);
    const sf::Vector2f delta = calcDelta(p1, p2);
    check(approx(delta.x, 6.0), "calcDelta x component should be 6");
    check(approx(delta.y, 6.0), "calcDelta y component should be 6");
}

void testLennardJonesForceSigns() {
    const double sigma2 = LJ_SIGMA * LJ_SIGMA;
    const double fAtSigma = calcLennardJonesForce(static_cast<float>(sigma2));
    check(fAtSigma > 0.0, "LJ force at sigma should be repulsive (>0)");

    const double rEq = std::pow(2.0, 1.0 / 6.0) * LJ_SIGMA;
    const double fAtEq = calcLennardJonesForce(static_cast<float>(rEq * rEq));
    check(std::abs(fAtEq) < 1e-4, "LJ force at equilibrium distance should be ~0");

    const double rFar = 2.0 * LJ_SIGMA;
    const double fFar = calcLennardJonesForce(static_cast<float>(rFar * rFar));
    check(fFar < 0.0, "LJ force at 2*sigma should be attractive (<0)");
}

void testVerletPrimitiveOneParticleDrop() {
    Particle p(0.0f, 0.0f, static_cast<float>(PARTICLE_RADIUS), sf::Color::White);
    constexpr float dt = 0.1f;
    constexpr int steps = 10;

    for (int i = 0; i < steps; ++i) {
        p.force = {0.0f, static_cast<float>(PARTICLE_MASS * GRAVITY)};
        const auto state = velvetIntPart(p, dt);
        p.velocity = state[0];
        p.position = state[1];
    }

    const double expectedVy = steps * GRAVITY * dt;
    const double expectedY = GRAVITY * dt * dt * (steps * (steps + 1) / 2.0);

    check(approx(p.velocity.y, expectedVy, 1e-4), "Verlet primitive velocity should match expected drop velocity");
    check(approx(p.position.y, expectedY, 1e-4), "Verlet primitive position should match expected drop position");
}

void testWallReflectionEnergyScaling() {
    Particle p(95.0f, 10.0f, static_cast<float>(PARTICLE_RADIUS), sf::Color::White);
    p.velocity = {10.0f, 0.0f};
    const double kineticBefore = 0.5 * PARTICLE_MASS * calcDistSqr(p.velocity);

    p.checkBounds(100.0f, 100.0f);

    const double expectedVx = -10.0 * WALL_RESTITUTION;
    check(approx(p.velocity.x, expectedVx, 1e-5), "Wall bounce should flip/scaled x velocity");
    check(approx(p.position.x, 100.0 - 2.0 * PARTICLE_RADIUS, 1e-5), "Wall bounce should clamp x position");

    const double kineticAfter = 0.5 * PARTICLE_MASS * calcDistSqr(p.velocity);
    const double expectedRatio = WALL_RESTITUTION * WALL_RESTITUTION;
    check(approx(kineticAfter / kineticBefore, expectedRatio, 1e-5),
          "Wall bounce kinetic energy ratio should be restitution^2");
}

}

int main() {
    testDistanceHelpers();
    testLennardJonesForceSigns();
    testVerletPrimitiveOneParticleDrop();
    testWallReflectionEnergyScaling();

    if (failures == 0) {
        std::cout << "[PASS] physics_primitives (" << 4 << " test groups)\n";
        return 0;
    }

    std::cerr << "[FAIL] physics_primitives failed with " << failures << " assertion(s)\n";
    return 1;
}
