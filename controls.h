//
// Created by efy on 2/08/24.
//

#ifndef CONTROLS_H
#define CONTROLS_H

void controls_use_ingame_set(bool enabled);

/**
 * If key is being pressed.
 * @param key The key code
 * @return True if the key is being pressed, false otherwise
 */
bool keyboard_is_pressing(int key);

#endif //CONTROLS_H
