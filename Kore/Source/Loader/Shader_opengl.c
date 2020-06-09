#ifdef LinuxBuild

#include "Shader.h"

#include "../Types/Types.h"
#include "../Graphics/Graphics.h"

#include "../Memory/Memory.h"
#include "../Log/Log.h"
#include "../IO/IO.h"

#include <SDL2/SDL.h>

#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// ========================================================
//
// Declaration
//
// ========================================================

static bool loadShader(GLuint *restrict result,
                       const char *restrict path,
                       k_ShaderType type);

static bool compileShader(GLuint, const char *restrict);

static size_t getShaderCount(const k_ShaderLoader *restrict loaders);

static bool compileProgram(GLuint *restrict result,
                           GLuint *restrict shaders,
                           size_t count);

// ========================================================
//
// Public implementation
//
// ========================================================

// k_Maybe(GLuint) k_LoadShaderProgram(k_ShaderProgramLoader *restrict info) {
bool k_LoadShaderProgram(k_Renderer *restrict renderer,
                         const k_ShaderLoader *restrict loaders) {
    const size_t count = getShaderCount(loaders);
    size_t loadedCount = 0;
    GLuint shaders[count];
    bool ok = false;
    GLuint program;

    for (int i = 0; i < count; i++) {
        ok = loadShader(&shaders[i], loaders[i].Filepath, loaders[i].Type);
        if (!ok) {
            goto clean_up;
        }
        loadedCount++;
    }
    ok = compileProgram(&program, shaders, count);

clean_up:
    for (int i = 0; i < loadedCount; i++) {
        glDeleteShader(shaders[i]);
    }
    k_RendererSetShaderProgram(renderer, program);
    return ok;
}

// ========================================================
//
// Private implementation
//
// ========================================================

static size_t getShaderCount(const k_ShaderLoader *restrict loaders) {
    size_t count = 0;
    for (count = 0; count < loaders[count].Type != k_ShaderTypeNone; count++)
        ;
    return count;
}

static bool loadShader(GLuint *restrict result,
                       const char *restrict path,
                       k_ShaderType type) {
    char *code = k_IOReadStringFile(path).Input;
    if (!code) {
        k_Logf("unable to load %s shader: %s\n", k_ShaderNameType(type), path);
        return false;
    }

    k_Logf("compiling %s shader: %s\n", k_ShaderNameType(type), path);
    GLuint shader = glCreateShader(type == k_ShaderTypeVertex
                                       ? GL_VERTEX_SHADER
                                       : GL_FRAGMENT_SHADER);
    if (!compileShader(shader, code)) {
        k_LogErrorf("compilation failed\n");
        return false;
    }

    *result = shader;
    return true;
}

static bool compileShader(GLuint shader, const char *code) {
    GLint res = GL_FALSE;
    int logLength = 0;
    char log[512];

    glShaderSource(shader, 1, &code, NULL);
    glCompileShader(shader);

    glGetShaderiv(shader, GL_COMPILE_STATUS, &res);
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
    if (logLength > 0) {
        glGetShaderInfoLog(shader, logLength, NULL, log);
        k_LogErrorf("[shader] %s", log);
        return false;
    }
    return true;
}

static bool compileProgram(GLuint *restrict result,
                           GLuint *restrict shaders,
                           size_t count) {
    GLuint program = glCreateProgram();
    GLint res = GL_FALSE;
    bool ok = false;
    int logLength = 0;
    char log[512];

    for (int i = 0; i < count; i++) {
        glAttachShader(program, shaders[i]);
    }
    glLinkProgram(program);

    glGetProgramiv(program, GL_LINK_STATUS, &res);
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
    ok = logLength < 1;
    if (!ok) {
        glGetProgramInfoLog(program, logLength, NULL, log);
        k_LogErrorf("[program] %s\n", log);
    }

    for (int i = 0; i < count; i++) {
        glDetachShader(program, shaders[i]);
    }

    *result = program;
    return ok;
}

#endif
