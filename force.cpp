#include "force.h"

#include <cmath>

struct Relation forces[16] = {0};
struct Relation relations[16][16] = {0};

void initForces() {
    for (size_t i = 1; i < 16; ++i) {
        relations[i][i].frendly = INFINITY;
        relations[i][i].allied = INFINITY;
    }
}
