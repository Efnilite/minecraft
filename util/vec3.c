//
// Created by efy on 1/08/24.
//

#include "vec3.h"

#include <assert.h>
#include <stdint.h>
#include <math.h>

Vec3i vec3i_create(const int16_t x, const int16_t y, const int16_t z) {
    return (Vec3i){x, y, z};
}

Vec3i vec3i_add(const Vec3i *vec3, const Vec3i *other) {
    assert(vec3 != nullptr);
    assert(other != nullptr);

    return vec3i_create(vec3->x + other->x, vec3->y + other->y, vec3->z + other->z);
}

Vec3i vec3i_subtract(const Vec3i *vec3, const Vec3i *other) {
    assert(vec3 != nullptr);
    assert(other != nullptr);

    return vec3i_create(vec3->x - other->x, vec3->y - other->y, vec3->z - other->z);
}

double vec3i_length(const Vec3i *vec3) {
    assert(vec3 != nullptr);

    return sqrt(vec3->x * vec3->x + vec3->y * vec3->y + vec3->z * vec3->z);
}

double vec3i_distance_to(const Vec3i *vec3, const Vec3i *other) {
    assert(vec3 != nullptr);
    assert(other != nullptr);

    const int dx = vec3->x - other->x;
    const int dy = vec3->y - other->y;
    const int dz = vec3->z - other->z;

    return sqrt(dx * dx + dy * dy + dz * dz);
}

Vec3d vec3d_create(const double x, const double y, const double z) {
    return (Vec3d){x, y, z};
}

Vec3d vec3d_add(const Vec3d *vec3, const Vec3d *other) {
    assert(vec3 != nullptr);
    assert(other != nullptr);

    return vec3d_create(vec3->x + other->x, vec3->y + other->y, vec3->z + other->z);
}

Vec3d vec3d_subtract(const Vec3d *vec3, const Vec3d *other) {
    assert(vec3 != nullptr);
    assert(other != nullptr);

    return vec3d_create(vec3->x - other->x, vec3->y - other->y, vec3->z - other->z);
}

Vec3d vec3d_multiply(const Vec3d *vec3, const double scalar) {
    assert(vec3 != nullptr);

    return vec3d_create(vec3->x * scalar, vec3->y * scalar, vec3->z * scalar);
}

double vec3d_length(const Vec3d *vec3) {
    assert(vec3 != nullptr);

    return sqrt(vec3->x * vec3->x + vec3->y * vec3->y + vec3->z * vec3->z);
}

Vec3d vec3d_normalize(const Vec3d *vec3) {
    assert(vec3 != nullptr);

    const double length = vec3d_length(vec3);

    return vec3d_create(vec3->x / length, vec3->y / length, vec3->z / length);
}

Vec3d vec3d_rotate_xz(const Vec3d *vec3, const double angle) {
    assert(vec3 != nullptr);
    assert(angle >= 0 && angle <= 360);

    const double s = sin(angle);
    const double c = cos(angle);

    const double x = vec3->x * c - vec3->z * s;
    const double z = vec3->x * s + vec3->z * c;

    return vec3d_create(x, vec3->y, z);
}

double vec3d_distance_to(const Vec3d *vec3, const Vec3d *other) {
    assert(vec3 != nullptr);
    assert(other != nullptr);

    const int dx = vec3->x - other->x;
    const int dy = vec3->y - other->y;
    const int dz = vec3->z - other->z;

    return sqrt(dx * dx + dy * dy + dz * dz);
}
