#include "tile.h"
#include <cstddef>
#include "force.h"

const float MAX_GIVEN = 1024.0f;
struct Tile tiles[256][256] = {0};

const int neighbors[] = {-257, -256, -255, -1, 1, 255, 256, 257};

void initTiles() {
    for (size_t y = 1; y < 255; ++y) {
        auto* row = tiles[y];
        for (size_t x = 1; x < 255; ++x) {
            row[x].force = 1;
            row[x].foodC = 5;
        }
    }
}

void iterateFood() {

    // init values;
    for (size_t y = 1; y < 255; ++y) {
        auto* row = tiles[y];
        for (size_t x = 1; x < 255; ++x) {
            if (x & y & 1) {
                row[x].foodC = 10.0f;
            } else {
                row[x].foodC = 1.0f;
            }
        }
    }
    tiles[6][6].food = 0;
    tiles[254][254].food = 0;

    // check neighbors
    for (size_t y = 1; y < 255; ++y) {
        auto* row = tiles[y];
        for (size_t x = 1; x < 255; ++x) {
            Tile * t = &row[x];
            auto mf = t->force;
            if (mf == 0) {
                continue;
            }
            float diffSum = 0;
            float diff[8] = {0};
            // find neighbors to transfer food
            for (size_t i = 0; i < 8; ++i) {
                Tile * n = t + neighbors[i];
                auto nf = n->force;
                if (nf == 0) {
                    continue;
                }
                if ( mf == nf || (relations[mf][nf].allied > 0 && relations[mf][nf].given < MAX_GIVEN)) {
                    if (n->food < t->food) {
                        auto d = t->food - n->food;
                        diff[i] = d;
                        diffSum += d;
                    }
                }
            }
            // apply the transfer
            if (diffSum) {
                t->foodC -= t->food;
                diffSum = t->food / diffSum; // pre divide;
                for (size_t i = 0; i < 8; ++i) {
                    if (diff[i]) {
                        Tile * n = t + neighbors[i];
                        auto nf = n->force;
                        float add = diff[i] * diffSum;
                        n->foodC += add;
                        if (mf != nf) {
                            // cound given
                            relations[mf][nf].givenC += add;
                        }
                    }
                }
            }
        }
    }

    // apply the change
    for (size_t y = 1; y < 255; ++y) {
        auto* row = tiles[y];
        for (size_t x = 1; x < 255; ++x) {
            Tile & t = row[x];
            t.food += t.foodC;
        }
    }
}
