#ifndef TILE_H
#define TILE_H

#include <stdint.h>

struct Tile {
    float food;
    float foodC;
    float population;
    uint8_t force;
    uint8_t land; // land type
    uint8_t build; // building type
    uint8_t unit; // unit id
};

extern struct Tile tiles[256][256];

extern "C" {
    void initTiles();
}

    void iterateFood();

#endif // TILE_H
