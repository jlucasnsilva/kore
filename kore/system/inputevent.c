#include "inputevent.h"

bool k_InputEventTranslate(k_InputEvent *restrict event,
                           const SDL_Event *restrict source) {
    switch (source->type) {
        case SDL_KEYDOWN:
        case SDL_KEYUP:
            event->type = source->type == SDL_KEYDOWN
                              ? k_InputEventTypeKeyPressed
                              : k_InputEventTypeKeyReleased;
            event->timestamp = source->key.timestamp;
            event->timestamp = source->key.timestamp;
            event->keyPressed.key = source->key.keysym.sym;
            event->keyPressed.scancode = source->key.keysym.scancode;
            return true;
        case SDL_MOUSEMOTION:
            event->type = k_InputEventTypeMouseMovement;
            event->timestamp = source->motion.timestamp;
            event->mouseMovement.x = source->motion.x;
            event->mouseMovement.y = source->motion.y;
            event->mouseMovement.xrel = source->motion.xrel;
            event->mouseMovement.yrel = source->motion.yrel;
            return true;
        case SDL_MOUSEBUTTONDOWN:
        case SDL_MOUSEBUTTONUP:
            event->type = source->type == SDL_MOUSEBUTTONDOWN
                              ? k_InputEventTypeMouseButtonPressed
                              : k_InputEventTypeMouseButtonReleased;
            event->mouseButtonPressed.button = source->button.button;
            event->mouseButtonPressed.clicks = source->button.clicks;
            event->mouseButtonPressed.x = source->button.x;
            event->mouseButtonPressed.y = source->button.y;
            return true;
        case SDL_MOUSEWHEEL:
            event->type = k_InputEventTypeMouseWheelMotion;
            event->mouseWheelMotion.direction = source->wheel.direction;
            event->mouseWheelMotion.x = source->wheel.x;
            event->mouseWheelMotion.y = source->wheel.y;
            return true;
    }
    return false;
}
