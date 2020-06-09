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
    uint32_t Scancode;
    int32_t Key;
} k_InputEventKeyboard;

typedef struct {
    int32_t X;
    int32_t Y;
    int32_t Xrel;
    int32_t Yrel;
} k_InputEventMouseMovement;

typedef struct {
    k_MouseButton Button;
    uint8_t Clicks;
    int32_t X;
    int32_t Y;
} k_InputEventMouseButton;

typedef struct {
    int32_t X;
    int32_t Y;
    uint32_t Direction;
} k_InputEventMouseWheelMotion;

typedef struct {
    k_InputEventType Type;
    uint32_t Timestamp;
    union {
        k_InputEventKeyboard KeyPressed;
        k_InputEventKeyboard KeyReleased;
        k_InputEventMouseMovement MouseMovement;
        k_InputEventMouseButton MouseButtonPressed;
        k_InputEventMouseButton MouseButtonReleased;
        k_InputEventMouseWheelMotion MouseWheelMotion;
    };
} k_InputEvent;

bool k_InputEventTranslate(k_InputEvent *restrict event,
                           const SDL_Event *restrict source);

#endif  // _K_SYSTEM_INPUT_EVENT_H_
