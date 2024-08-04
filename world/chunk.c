//
// Created by efy on 3/08/24.
//

#include "chunk.h"

#include <errno.h>

#include "block.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

/**
 * Get the filename for a chunk.
 * @param x The x-coordinate.
 * @param z The z-coordinate.
 * @return A pointer to the filename.
 */
char *chunk_get_filename(const int8_t x, const int8_t z) {
    char *filename = malloc((6 + 7) * sizeof(char)); // 6 for "world/" and 7 for "x,y"
    if (filename == nullptr) {
        fprintf(stderr, "Failed to allocate memory for filename\n");
        free(filename);
        return nullptr;
    }

    sprintf(filename, "world/%i,%i", x, z);
    return filename;
}

Chunk *chunk_load_from_file(const int8_t x, const int8_t z) {
    printf("Reading file for chuck %i,%i\n", x, z);

    char *filename = chunk_get_filename(x, z);
    if (filename == nullptr) {
        fprintf(stderr, "Failed to get filename for chunk\n");
        goto free;
    }

    FILE *file = fopen(filename, "r");
    if (file == nullptr) {
        fprintf(stderr, "Failed to open chunk file: %s\n", filename);
        goto free;
    }

    fseek(file, 0, SEEK_END);
    const long filesize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *buffer = malloc(filesize * sizeof(char));
    if (buffer == nullptr) {
        fprintf(stderr, "Failed to allocate buffer for chunk file: %s\n", filename);
        goto free;
    }

    fread(buffer, 1, filesize, file);
    buffer[filesize] = '\0';

    char *split = strtok(buffer, " ");
    if (split == nullptr) {
        fprintf(stderr, "Failed to split buffer\n");
        goto free;
    }

    Block blocks[CHUNK_SIZE * CHUNK_SIZE * CHUNK_HEIGHT]; {
        int i = 0;
        while (split != nullptr) {
            const Material material = block_material_from_string(split);
            if (material == UNKNOWN) {
                fprintf(stderr, "Unknown material: %s\n", split);
                goto free;
            }

            blocks[i] = (Block){
                material,
                {i % CHUNK_SIZE, i % CHUNK_SIZE * CHUNK_SIZE, i / CHUNK_SIZE}
            };

            split = strtok(nullptr, " ");
            i++;
        }
    }

    Chunk *chunk = malloc(sizeof(Chunk));
    if (chunk == nullptr) {
        fprintf(stderr, "Failed to allocate memory for chunk\n");
        free(chunk);
        goto free;
    }

    chunk->x = x;
    chunk->z = z;
    for (int i = 0; i < CHUNK_SIZE * CHUNK_SIZE * CHUNK_HEIGHT; ++i) {
        chunk->blocks[i] = blocks[i];
    }

free:
    fclose(file);
    free(filename);
    free(buffer);
    return chunk;
}

Chunk *chunk_create(const int8_t x, const int8_t z) {
    printf("Creating chunk %i,%i\n", x, z);

    Chunk *chunk = malloc(sizeof(Chunk));
    if (chunk == nullptr) {
        fprintf(stderr, "Failed to allocate memory for chunk\n");
        free(chunk);
        return nullptr;
    }

    chunk->x = x;
    chunk->z = z;

    int i = 0;
    while (i < CHUNK_SIZE * CHUNK_SIZE * CHUNK_HEIGHT) {
        if (i < CHUNK_SIZE * CHUNK_SIZE * 3) {
            chunk->blocks[i] = (Block){
                STONE,
                {0, 0, 0}
            };
        } else if (i < CHUNK_SIZE * CHUNK_SIZE * 4) {
            chunk->blocks[i] = (Block){
                GRASS,
                {0, 0, 0}
            };
        } else {
            chunk->blocks[i] = (Block){
                AIR,
                {0, 0, 0}
            };
        }
        i++;
    }

    return chunk;
}

Chunk *chunk_load(const int8_t x, const int8_t z) {
    printf("Loading chunk %i,%i\n", x, z);

    if (access("world", F_OK) != 0) {
        mkdir("world", S_IRWXU);
        printf("Creating world folder\n");
    }

    char *filename = chunk_get_filename(x, z);
    if (filename == nullptr) {
        fprintf(stderr, "Failed to get filename for chunk\n");
        free(filename);
        return nullptr;
    }

    Chunk *chunk;
    if (access(filename, F_OK) == 0) {
        chunk = chunk_load_from_file(x, z);
    } else {
        chunk = chunk_create(x, z);
    }

    free(filename);
    return chunk;
}

void chunk_close(Chunk *chunk) {
    printf("Closing chunk %i,%i\n", chunk->x, chunk->z);

    char *filename = chunk_get_filename(chunk->x, chunk->z);
    if (filename == nullptr) {
        fprintf(stderr, "Failed to get filename for chunk\n");
        goto free;
    }

    FILE *file = fopen(filename, "w");
    if (file == nullptr) {
        fprintf(stderr, "Failed to open chunk file %s: %s\n", filename, strerror(errno));
        goto free;
    }

    for (int i = 0; i < CHUNK_SIZE * CHUNK_SIZE * CHUNK_HEIGHT; ++i) {
        fprintf(file, "%s ", block_string_from_material(chunk->blocks[i].material));
    }

free:
    fclose(file);
    free(filename);
    free(chunk);
}
