#ifndef _K_SYSTEM_RUNTIME_H_
#define _K_SYSTEM_RUNTIME_H_

#include "inputevent.h"

typedef struct k_Executable k_Executable;

typedef void (*k_StepFunc)(k_Executable* self, float dt);
typedef void (*k_ExecutableFunc)(k_Executable* self);
typedef void (*k_InputEventHandlerFunc)(k_Executable* self,
                                        k_InputEvent* restrict event,
                                        float dt);

struct k_Executable {
    k_ExecutableFunc Init;
    k_StepFunc Step;
    k_ExecutableFunc Quit;
    k_InputEventHandlerFunc HandleInputEvent;
};

#define k_bExecutable(...) ((k_Executable){.Step = NULL, __VA_ARGS__})

void k_Init(void);

void k_Quit(void);

void k_Run(k_Executable* restrict);

#endif  // _K_SYSTEM_RUNTIME_H_