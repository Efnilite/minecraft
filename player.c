//
// Created by efy on 1/08/24.
//

#include "player.h"

#include <SDL_scancode.h>
#include <SDL_mouse.h>

#include "controls.h"
#include "util/vec2.h"
#include "util/vec3.h"
#include "world/chunk.h"

#define PLAYER_SPEED_METER_PER_SECONDS 1/60.0
#define PLAYER_MOUSE_SENSITIVITY 0.1

typedef struct Player {
    Vec3d position;
    float yaw;
    float pitch;
} Player;

Player player = {{0, 0, 0}, 0, 0};

void player_update() {
    // movement
    Vec3d movement = {0, 0, 0};

    if (keyboard_is_pressing(SDL_SCANCODE_W)) {
        movement.x += cos(player.yaw);
        movement.z += sin(player.yaw);
    }
    if (keyboard_is_pressing(SDL_SCANCODE_A)) {
        movement.x += sin(player.yaw);
        movement.z -= cos(player.yaw);
    }
    if (keyboard_is_pressing(SDL_SCANCODE_S)) {
        movement.x -= cos(player.yaw);
        movement.z -= sin(player.yaw);
    }
    if (keyboard_is_pressing(SDL_SCANCODE_D)) {
        movement.x -= sin(player.yaw);
        movement.z += cos(player.yaw);
    }

    if (!(movement.x == 0 && movement.z == 0)) {
        movement = vec3d_normalize(&movement);
        movement = vec3d_multiply(&movement, PLAYER_SPEED_METER_PER_SECONDS);

        player.position = vec3d_add(&player.position, &movement);
    }

    // jump
    if (keyboard_is_pressing(SDL_SCANCODE_SPACE)) {
    }
}

void player_update_mouse(const double dx, const double dy) {
    player.yaw += dx * PLAYER_MOUSE_SENSITIVITY;

    if (player.yaw > 360) {
        player.yaw -= 360;
    } else if (player.yaw < 0) {
        player.yaw += 360;
    }

    player.pitch = fmax(-180, fmin(180, player.pitch - dy * PLAYER_MOUSE_SENSITIVITY));

    printf("%f %f\n", player.yaw, player.pitch);
}

Vec2i player_get_chunk() {
    const int x = (int) floor(player.position.x) / CHUNK_SIZE;
    const int z = (int) floor(player.position.z) / CHUNK_SIZE;

    return (Vec2i) {x, z};
}
