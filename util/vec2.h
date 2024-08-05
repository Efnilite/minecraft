//
// Created by efy on 3/08/24.
//

#ifndef VEC2_H
#define VEC2_H
#include <stdint.h>

typedef struct Vec2i {
    int16_t x;
    int16_t y;
} Vec2i;

Vec2i vec2i_create(int16_t x, int16_t y);

#endif //VEC2_H
