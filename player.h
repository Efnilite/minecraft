//
// Created by efy on 1/08/24.
//

#ifndef PLAYER_H
#define PLAYER_H
#include "util/vec2.h"

/**
 * Updates player.
 */
void player_update();

void player_update_mouse(double dx, double dy);

Vec2i player_get_chunk();

#endif //PLAYER_H
