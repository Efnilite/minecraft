//
// Created by efy on 3/08/24.
//

#include "block.h"

#include <string.h>

Material block_material_from_string(const char *str) {
    if (strcmp(str, "air") == 0) return AIR;
    if (strcmp(str, "stone") == 0) return STONE;
    if (strcmp(str, "dirt") == 0) return DIRT;
    if (strcmp(str, "grass") == 0) return GRASS;

    return UNKNOWN;
}

char *block_string_from_material(const Material material) {
    if (material == AIR) return "air";
    if (material == STONE) return "stone";
    if (material == DIRT) return "dirt";
    if (material == GRASS) return "grass";

    return nullptr;
}
