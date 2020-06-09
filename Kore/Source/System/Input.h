#ifndef _K_SYSTEM_H_
#define _K_SYSTEM_H_

#include <stdbool.h>

typedef enum {
    k_InputKeyUp,
    k_InputKeyDown,
    k_InputKeyLeft,
    k_InputKeyRight,
} k_InputKey;

bool k_InputIsPressed(k_InputKey k);

#endif  // _K_SYSTEM_H_
