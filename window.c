//
// Created by efy on 1/08/24.
//

#include "window.h"

#include <SDL_error.h>
#include <SDL_video.h>
#include <SDL_render.h>
#include <SDL.h>
#include <stdio.h>

SDL_Window *window = nullptr;
SDL_Renderer *renderer = nullptr;

void window_create() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "Failed to init SDL: %s\n", SDL_GetError());
    }

    window = SDL_CreateWindow("Minecraft in C",
                              SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              1920 / 2, 1080 / 2, SDL_WINDOW_SHOWN);

    if (window == nullptr) {
        fprintf(stderr, "Failed to create window: %s\n", SDL_GetError());
    }

    renderer = SDL_CreateRenderer(window, -1, 0);

    if (renderer == nullptr) {
        fprintf(stderr, "Failed to create renderer: %s\n", SDL_GetError());
    }
}

void window_close() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
}

void window_clear() {
    if (SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0) != 0) {
        fprintf(stderr, "Prerender draw color failed: %s", SDL_GetError());
        return;
    }

    if (SDL_RenderClear(renderer) != 0) {
        fprintf(stderr, "Prerender clear failed: %s", SDL_GetError());
        return;
    }
}

void window_draw() {
    SDL_RenderPresent(renderer);
}