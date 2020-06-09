#include "Input.h"

#include <SDL2/SDL.h>

#include <stdint.h>

static int toScanCode[] = {
    [k_InputKeyUp] = SDL_SCANCODE_UP,
    [k_InputKeyDown] = SDL_SCANCODE_DOWN,
    [k_InputKeyLeft] = SDL_SCANCODE_LEFT,
    [k_InputKeyRight] = SDL_SCANCODE_RIGHT,
};

bool k_InputIsPressed(k_InputKey k) {
    const uint8_t* state = SDL_GetKeyboardState(NULL);
    return (bool)state[toScanCode[k]];
}
