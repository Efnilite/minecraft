//
// Created by efy on 1/08/24.
//

#ifndef VEC3_H
#define VEC3_H
#include <stdint.h>

typedef struct Vec3i {
    int16_t x;
    int16_t y;
    int16_t z;
} Vec3i;

Vec3i vec3i_create(int16_t x, int16_t y, int16_t z);

Vec3i vec3i_add(const Vec3i *vec3, const Vec3i *other);

Vec3i vec3i_subtract(const Vec3i *vec3, const Vec3i *other);

double vec3i_length(const Vec3i *vec3);

double vec3i_distance_to(const Vec3i *vec3, const Vec3i *other);

typedef struct Vec3d {
    double x;
    double y;
    double z;
} Vec3d;

Vec3d vec3d_create(double x, double y, double z);

Vec3d vec3d_add(const Vec3d *vec3, const Vec3d *other);

Vec3d vec3d_subtract(const Vec3d *vec3, const Vec3d *other);

Vec3d vec3d_multiply(const Vec3d *vec3, double scalar);

Vec3d vec3d_normalize(const Vec3d *vec3);

Vec3d vec3d_rotate_xz(const Vec3d *vec3, double angle);

double vec3d_length(const Vec3d *vec3);

double vec3d_distance_to(const Vec3d *vec3, const Vec3d *other);

#endif //VEC3_H
