#ifndef _K_LOADER_H_
#define _K_LOADER_H_

#include "types/types.h"

#include <GL/glew.h>
#include <GL/gl.h>
#include <SDL2/SDL.h>

#include <stdbool.h>

typedef struct {
    char VertexShaderPath[512];
    char FragmentShaderPath[512];
} k_ShaderProgramLoader;

k_Maybe(GLuint) k_LoadShaderProgram(k_ShaderProgramLoader *restrict);

#endif  // _K_LOADER_H_
