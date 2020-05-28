#ifndef _K_LOADER_SHADER_H_
#define _K_LOADER_SHADER_H_

#include "../types/types.h"
#include "../types/defmaybe.h"
#include "../graphics/graphics.h"

#include <stdlib.h>

typedef struct {
    k_ShaderType Type;
    const char* Filepath;
} k_ShaderLoader;

#define k_bShaderLoader(...) \
    ((k_ShaderLoader){.Type = k_ShaderTypeNone, .Filepath = NULL, __VA_ARGS__})

#define k_LoadShaders(renderer, ...) \
    k_LoadShaderProgram(renderer,    \
                        ((k_ShaderLoader[]){__VA_ARGS__, k_bShaderLoader()}))

bool k_LoadShaderProgram(k_Renderer* restrict renderer,
                         const k_ShaderLoader* restrict loaders);

#endif  // _K_LOADER_SHADER_H_
