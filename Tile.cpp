#include "tile.h"
#include <cstddef>
#include <cstdlib>
#include <limits>
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
            row[x].food = 128.0f;
        }
    }
}

size_t kx = 6;
size_t ky = 106;

void iterateFood() {

        // init values;
        for (size_t y = 1; y < 255; ++y) {
            auto* row = tiles[y];
            for (size_t x = 1; x < 255; ++x) {
                //if (x & y & 1) {
                    row[x].foodC = static_cast <float> (rand()) *0.2f / static_cast <float> (RAND_MAX);
               // } else {
                    row[x].foodC = 0.05f;
                //}
            }
        }


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
                t->foodC -= t->food * 0.75;
                diffSum = (t->food * 0.75) / diffSum; // pre divide;
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

    tiles[ky][kx].food = 0;

    ky = ky + (rand() & 1) - (rand() & 1);
    kx = kx + (rand() & 1) - (rand() & 1);

    if (ky < 5) ky = 5;
    if (ky > 200) ky = 200;
    if (kx < 5) kx = 5;
    if (kx > 200) kx = 200;

    tiles[153][153].food = 0;
    tiles[153][154].food = 0;
    tiles[153][152].food = 0;
    tiles[152][153].food = 0;
    tiles[152][152].food = 0;
    tiles[152][154].food = 0;
    tiles[154][153].food = 0;
    tiles[154][152].food = 0;
    tiles[154][154].food = 0;
}
