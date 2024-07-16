#include <stdio.h>

#include "force.h"
#include "output-image.h"
#include "tile.h"

extern "C" {

    void * gettiles() {
        return &tiles;
    }
    void updateTile() {
        tiles[0][0].food ++;
    }

    void * run() {
        iterateFood();
        return updateBitmap();
    }
}

int main()
{
    initTiles();
    initForces();
    printf("Hello World!\n");
    return 0;
}
