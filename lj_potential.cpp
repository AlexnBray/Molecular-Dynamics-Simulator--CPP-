#include "constants.h"


double calcLennardJonesForce(float distSquared) {
    double sr2  = (LJ_SIGMA * LJ_SIGMA) / distSquared;
    double sr6  = sr2 * sr2 * sr2;
    double sr12 = sr6 * sr6;

    double force = (24.0 * LJ_EPSILON / distSquared) * (2.0 * sr12 - sr6);

    return force;
}

//F(r) = (24ε / r²) [ 2(σ/r)¹² - (σ/r)⁶ ]
//F(r) = (24ε / r²) * ( 2(σ/r)¹² - (σ/r)⁶ )