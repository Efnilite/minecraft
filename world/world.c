//
// Created by efy on 2/08/24.
//

#include "world.h"

#include <assert.h>
#include <math.h>
#include <stdio.h>

#include "chunk.h"
#include "../util/vec2.h"

#define RENDER_DISTANCE 8
#define RENDER_CHUNKS (RENDER_DISTANCE * RENDER_DISTANCE)

typedef struct World {
    int seed;
    Chunk *chunks[RENDER_CHUNKS];
} World;

World world;

void world_create() {
    constexpr uint8_t half = RENDER_DISTANCE / 2;

    uint8_t i = 0;
    for (int8_t dx = -half; dx < half; ++dx) {
        for (int8_t dz = -half; dz < half; ++dz) {
            world.chunks[i] = chunk_load(dx, dz);
            i++;
        }
    }
}

void world_close() {
    for (int8_t i = 0; i < RENDER_CHUNKS; ++i) {
        if (world.chunks[i] == nullptr) {
            fprintf(stderr, "Failed to get world at %i\n", i);
            continue;
        }
        chunk_close(world.chunks[i]);
    }
}

void world_chunks_load(const Vec2i currentChunk) {
    const int8_t chunkX = (int8_t) floor(currentChunk.x) / CHUNK_SIZE;
    const int8_t chunkZ = (int8_t) floor(currentChunk.y) / CHUNK_SIZE;
    constexpr uint8_t half = RENDER_DISTANCE / 2;

    Vec2i newArea[RENDER_CHUNKS];

    {
        uint8_t i = 0;
        for (int8_t dx = chunkX - half; dx < chunkX + half; ++dx) {
            for (int8_t dz = chunkZ - half; dz < chunkZ + half; ++dz) {
                newArea[i] = vec2i_create(dx, dz);
                i++;
            }
        }
    }

    uint8_t toUnloadSize = 0;
    uint8_t toUnload[RENDER_CHUNKS];
    for (int i = 0; i < RENDER_CHUNKS; ++i) {
        toUnload[i] = -1;
    }

    for (uint8_t i = 0; i < RENDER_CHUNKS; ++i) {
        Chunk *chunk = world.chunks[i];

        assert(chunk != nullptr);

        bool unload = true;
        for (uint8_t j = 0; j < RENDER_CHUNKS; ++j) {
            const Vec2i vec = newArea[j];

            if (vec.x == chunk->x && vec.y == chunk->z) {
                unload = false;
                break;
            }
        }

        if (unload) {
            printf("Unloading chunk dynamically at %i,%i\n", chunk->x, chunk->z);
            chunk_close(chunk);

            toUnload[toUnloadSize] = i;
            toUnloadSize++;
        }
    }

    int toUnloadIndex = 0;
    for (uint8_t i = 0; i < RENDER_CHUNKS; ++i) {
        const Vec2i vec = newArea[i];

        bool load = true;
        for (uint8_t j = 0; j < RENDER_CHUNKS; ++j) {
            const Chunk *chunk = world.chunks[j];

            assert(chunk != nullptr);

            if (chunk->x == vec.x && chunk->z == vec.y) {
                load = false;
                break;
            }
        }

        if (load) {
            printf("Loading chunk dynamically at %i,%i\n", vec.x, vec.y);

            const uint8_t idx = toUnload[toUnloadIndex];

            if (idx == -1) {
                continue;
            }

            world.chunks[idx] = chunk_load(vec.x, vec.y);
            toUnloadIndex++;
        }
    }
}

void world_update(const Vec2i currentChunk) {
    world_chunks_load(currentChunk);
}
