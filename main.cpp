#include <stdio.h>

#include "force.h"
#include "tile.h"

extern "C" {

    void * gettiles() {
        return &tiles;
    }
    void updateTile() {
        tiles[0][0].food ++;
    }

    void run() {
        iterateFood();
    }
}

int main()
{
    initTiles();
    initForces();
    printf("Hello World!\n");
    return 0;
}
