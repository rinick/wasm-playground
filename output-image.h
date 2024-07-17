#ifndef OUTPUTIMAGE_H
#define OUTPUTIMAGE_H


#include <cstddef>
#include <stdint.h>

extern uint8_t bitmap[256][256][4];
extern size_t kx;
extern size_t ky;
void * updateBitmap();

#endif // OUTPUTIMAGE_H
