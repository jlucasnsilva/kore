#ifndef _K_RUNTIME_H_
#define _K_RUNTIME_H_

typedef struct k_Executable k_Executable;

typedef void (*k_StepFunc)(k_Executable* self, float dt);
typedef void (*k_ExecutableFunc)(k_Executable* self);

struct k_Executable {
    k_ExecutableFunc Init;
    k_StepFunc Step;
};

#define k_bExecutable(...) ((k_Executable){.Step = NULL, __VA_ARGS__})

void k_Init(void);

void k_Quit(void);

void k_Run(k_Executable* restrict);

#endif  // _K_RUNTIME_H_