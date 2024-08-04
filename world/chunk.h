//
// Created by efy on 3/08/24.
//

#ifndef CHUNK_H
#define CHUNK_H
#include <stdint.h>

#include "block.h"

#define CHUNK_SIZE 16
#define CHUNK_HEIGHT 32

typedef struct Chunk {
    int8_t x;
    int8_t z;
    Block blocks[CHUNK_SIZE * CHUNK_SIZE * CHUNK_HEIGHT];
} Chunk;

/**
 * Load a {@link Chunk} from a file, or if unloaded, creates it.
 * Freed with {@link chunk_close}.
 *
 * @param x The x-coordinate.
 * @param z The z-coordinate.
 * @return The {@link Chunk} at the given coordinates.
 */
Chunk *chunk_load(int8_t x, int8_t z);

void chunk_close(Chunk *chunk);

#endif //CHUNK_H
