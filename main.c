#include <SDL_events.h>
#include <SDL_timer.h>

#include "player.h"
#include "window.h"
#include "world/world.h"

uint32_t frames = 0;
void loop() {
    while (true) {
        window_clear();

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                return;
            }

            if (event.type == SDL_MOUSEMOTION) {
                player_update_mouse(event.motion.xrel, event.motion.yrel);
            }
        }

        player_update();

        if (frames > 0 && frames % 5 * 60 == 0) {
            world_update(player_get_chunk());

            frames = 0;
        }

        window_draw();

        frames++;
        SDL_Delay(1000 / 60);
    }
}

int main() {
    window_create();
    // controls_use_ingame_set(true);
    world_create();

    loop();

    world_close();
    window_close();

    return 0;
}
