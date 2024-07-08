#ifndef HERO_H
#define HERO_H

#include <stdint.h>

struct Tile;

struct Hero {
    float army;
    float injured;
    float food;
    float loyal;
    struct Tile* tile;
    uint8_t force;

    uint8_t wy; // 武勇
    uint8_t fy; // 防御
    uint8_t zm; // 智谋
    uint8_t jj; // 军纪
    uint8_t js; // 军师
    uint8_t nz; // 内政
    uint8_t zb; // 征兵
};

#endif // HERO_H
