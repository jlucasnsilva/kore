#ifndef _K_SYSTEM_INPUT_EVENT_H_
#define _K_SYSTEM_INPUT_EVENT_H_

#include <SDL2/SDL.h>

#include <stdint.h>
#include <stdbool.h>

typedef enum {
    k_InputEventTypeKeyPressed = SDL_KEYDOWN,
    k_InputEventTypeKeyReleased = SDL_KEYUP,

    k_InputEventTypeMouseMovement = SDL_MOUSEMOTION,
    k_InputEventTypeMouseButtonPressed = SDL_MOUSEBUTTONDOWN,
    k_InputEventTypeMouseButtonReleased = SDL_MOUSEBUTTONUP,
    k_InputEventTypeMouseWheelMotion = SDL_MOUSEWHEEL,
} k_InputEventType;

typedef enum {
    k_MouseButtonLeft = SDL_BUTTON_LEFT,
    k_MouseButtonMiddle = SDL_BUTTON_MIDDLE,
    k_MouseButtonRight = SDL_BUTTON_RIGHT,
} k_MouseButton;

typedef struct {
    uint32_t scancode;
    int32_t key;
} k_InputEventKeyboard;

typedef struct {
    int32_t x;
    int32_t y;
    int32_t xrel;
    int32_t yrel;
} k_InputEventMouseMovement;

typedef struct {
    k_MouseButton button;
    uint8_t clicks;
    int32_t x;
    int32_t y;
} k_InputEventMouseButton;

typedef struct {
    int32_t x;
    int32_t y;
    uint32_t direction;
} k_InputEventMouseWheelMotion;

typedef struct {
    k_InputEventType type;
    uint32_t timestamp;
    union {
        k_InputEventKeyboard keyPressed;
        k_InputEventKeyboard keyReleased;
        k_InputEventMouseMovement mouseMovement;
        k_InputEventMouseButton mouseButtonPressed;
        k_InputEventMouseButton mouseButtonReleased;
        k_InputEventMouseWheelMotion mouseWheelMotion;
    };
} k_InputEvent;

bool k_InputEventTranslate(k_InputEvent *restrict event,
                           const SDL_Event *restrict source);

#endif  // _K_SYSTEM_INPUT_EVENT_H_
