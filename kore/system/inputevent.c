#include "inputevent.h"

bool k_InputEventTranslate(k_InputEvent *restrict event,
                           const SDL_Event *restrict source) {
    switch (source->type) {
        case SDL_KEYDOWN:
        case SDL_KEYUP:
            event->Type = source->type == SDL_KEYDOWN
                              ? k_InputEventTypeKeyPressed
                              : k_InputEventTypeKeyReleased;
            event->Timestamp = source->key.timestamp;
            event->Timestamp = source->key.timestamp;
            event->KeyPressed.Key = source->key.keysym.sym;
            event->KeyPressed.Scancode = source->key.keysym.scancode;
            return true;
        case SDL_MOUSEMOTION:
            event->Type = k_InputEventTypeMouseMovement;
            event->Timestamp = source->motion.timestamp;
            event->MouseMovement.X = source->motion.x;
            event->MouseMovement.Y = source->motion.y;
            event->MouseMovement.Xrel = source->motion.xrel;
            event->MouseMovement.Yrel = source->motion.yrel;
            return true;
        case SDL_MOUSEBUTTONDOWN:
        case SDL_MOUSEBUTTONUP:
            event->Type = source->type == SDL_MOUSEBUTTONDOWN
                              ? k_InputEventTypeMouseButtonPressed
                              : k_InputEventTypeMouseButtonReleased;
            event->MouseButtonPressed.Button = source->button.button;
            event->MouseButtonPressed.Clicks = source->button.clicks;
            event->MouseButtonPressed.X = source->button.x;
            event->MouseButtonPressed.Y = source->button.y;
            return true;
        case SDL_MOUSEWHEEL:
            event->Type = k_InputEventTypeMouseWheelMotion;
            event->MouseWheelMotion.Direction = source->wheel.direction;
            event->MouseWheelMotion.X = source->wheel.x;
            event->MouseWheelMotion.Y = source->wheel.y;
            return true;
    }
    return false;
}
