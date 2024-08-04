//
// Created by efy on 3/08/24.
//

#ifndef BLOCK_H
#define BLOCK_H
#include "../util/vec3.h"

typedef enum Material {
    AIR,
    STONE,
    DIRT,
    GRASS,

    UNKNOWN,
} Material;

typedef struct Block {
    Material material;
    Vec3i position;
} Block;

Material block_material_from_string(const char *str);

char *block_string_from_material(Material material);

#endif //BLOCK_H
