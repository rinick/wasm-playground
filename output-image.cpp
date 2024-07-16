#include "output-image.h"
#include "tile.h"
#include <cmath>
#include <cstddef>

uint8_t bitmap[256][256][4] = {0};

void * updateBitmap() {
    for (size_t y = 1; y < 255; ++y) {
        auto* trow = tiles[y];
        auto* brow = bitmap[y];
        for (size_t x = 1; x < 255; ++x) {
            float m = trow[x].food - trow[x].foodC* 0.5f;
            brow[x][3] = 255;
            if (m > 255.0) {
                brow[x][0] = 255;
            } else if (m < 0.0) {
                brow[x][0] = 0;
            } else {
                brow[x][0] = round(m);
            }
        }
    }
    return &bitmap;
}
