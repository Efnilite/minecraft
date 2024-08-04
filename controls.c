//
// Created by efy on 2/08/24.
//

#include "controls.h"

#include <SDL_keyboard.h>
#include <SDL_mouse.h>

void controls_use_ingame_set(const bool enabled) {
    if (SDL_SetRelativeMouseMode(enabled ? SDL_TRUE : SDL_FALSE) != 0) {
        fprintf(stderr, "Failed to set relative mouse mode: %s\n", SDL_GetError());
    }
}

bool keyboard_is_pressing(const int key) {
    const Uint8 *keyboard = SDL_GetKeyboardState(nullptr);

    return keyboard[key];
}