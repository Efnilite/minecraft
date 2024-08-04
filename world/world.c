//
// Created by efy on 2/08/24.
//

#include "world.h"
#include <math.h>
#include <stdio.h>

#include "chunk.h"
#include "../util/vec2.h"

#define RENDER_DISTANCE 8

typedef struct World {
    int seed;
    Chunk *chunks[RENDER_DISTANCE * RENDER_DISTANCE];
} World;

World world;

void world_chunks_load(const int8_t x, const int8_t z) {
    const int8_t chunkX = (int8_t) floor(x) / CHUNK_SIZE;
    const int8_t chunkZ = (int8_t) floor(z) / CHUNK_SIZE;
    constexpr uint8_t half = RENDER_DISTANCE / 2;

    Vec2i toLoad[RENDER_DISTANCE * RENDER_DISTANCE];

    {
        int i = 0;
        for (int8_t dx = chunkX - half; dx < chunkX + half; ++dx) {
            for (int8_t dz = chunkZ - half; dz < chunkZ + half; ++dz) {
                toLoad[i] = (Vec2i){dx, dz};
                i++;
            }
        }
    }

    for (int8_t i = 0; i < RENDER_DISTANCE * RENDER_DISTANCE; ++i) {
        const int8_t newX = toLoad[i].x;
        const int8_t newZ = toLoad[i].y;

        bool inOverlap = false;
        for (int8_t j = 0; j < RENDER_DISTANCE * RENDER_DISTANCE; ++j) {
            const Chunk *chunk = world.chunks[j];

            if (chunk == nullptr) continue;

            if (chunk->x == newX && chunk->z == newZ) {
                inOverlap = true;
                break;
            }
        }
    }
}

void world_create() {
    constexpr int half = RENDER_DISTANCE / 2;

    int i = 0;
    for (int8_t dx = -half; dx < half; ++dx) {
        for (int8_t dz = -half; dz < half; ++dz) {
            world.chunks[i] = chunk_load(dx, dz);
            i++;
        }
    }
}

void world_close() {
    for (int8_t i = 0; i < RENDER_DISTANCE * RENDER_DISTANCE; ++i) {
        if (world.chunks[i] == nullptr) {
            fprintf(stderr, "Failed to get world at %i\n", i);
            continue;
        }
        chunk_close(world.chunks[i]);
    }
}
