#include "loader.h"
#include "../util/util.h"
#include "../memory/memory.h"
#include "../log/log.h"

#include <SDL2/SDL.h>

#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// ========================================================
//
// Declaration
//
// ========================================================

static char *loadShader(const char *restrict);

static bool compileShader(GLuint, const char *restrict);

static k_Maybe(GLuint) compileProgram(GLuint, GLuint);

// ========================================================
//
// Public implementation
//
// ========================================================

k_Maybe(GLuint) k_LoadShaderProgram(k_ShaderProgramLoader *restrict info) {
    k_Maybe(GLuint) ret;
    char *vertexShaderCode = NULL;
    char *fragmentShaderCode = NULL;

    ret.ok = false;

    vertexShaderCode = loadShader(info->VertexShaderPath);
    if (!vertexShaderCode) {
        goto clean_up;
    }

    fragmentShaderCode = loadShader(info->FragmentShaderPath);
    if (!fragmentShaderCode) {
        goto clean_up;
    }

    k_Logf("compiling vertex shader: %s\n", info->VertexShaderPath);
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    if (!compileShader(vertexShader, vertexShaderCode)) {
        k_LogErrorf("compilation failed\n");
        goto clean_up;
    }

    k_Logf("compiling fragment shader: %s\n", info->FragmentShaderPath);
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    if (!compileShader(fragmentShader, fragmentShaderCode)) {
        k_LogErrorf("compilation failed\n");
        glDeleteShader(vertexShader);
        goto clean_up;
    }

    k_Maybe(GLuint) maybeProgram = compileProgram(vertexShader,
                                                  fragmentShader);
    glDeleteShader(fragmentShader);
    glDeleteShader(vertexShader);
    ret.value = maybeProgram.value;
    ret.ok = true;

clean_up:
    k_Delete(fragmentShaderCode);
    k_Delete(vertexShaderCode);
    return ret;
}

// ========================================================
//
// Private implementation
//
// ========================================================

static char *loadShader(const char *restrict filepath) {
    size_t capacity = 2048;
    char *content = (char *)malloc(capacity);
    if (!content) {
        return NULL;
    }
    memset(content, '\0', 2048);

    SDL_RWops *in = SDL_RWFromFile(filepath, "r");
    if (!in) {
        k_Delete(content);
        return NULL;
    }

    SDL_RWread(in, content, capacity, 1);
    if (strlen(content) < 1) {
        k_Delete(content);
        return NULL;
    }
    SDL_RWclose(in);
    return content;
}

static bool compileShader(GLuint shader, const char *code) {
    GLint res = GL_FALSE;
    int logLength = 0;
    char log[512];

    glShaderSource(shader, 1, &code, NULL);
    glCompileShader(shader);

    // Check Vertex Shader
    glGetShaderiv(shader, GL_COMPILE_STATUS, &res);
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
    if (logLength > 0) {
        glGetShaderInfoLog(shader, logLength, NULL, log);
        k_LogErrorf("[shader] %s", log);
        return false;
    }
    return true;
}

static k_Maybe(GLuint) compileProgram(GLuint vertexShader,
                                      GLuint fragmentShader) {
    GLuint program = glCreateProgram();
    GLint res = GL_FALSE;
    int logLength = 0;
    k_Maybe(GLuint) ret;
    char log[512];

    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    glGetProgramiv(program, GL_LINK_STATUS, &res);
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
    ret.ok = logLength > 0;
    if (ret.ok) {
        glGetProgramInfoLog(program, logLength, NULL, log);
        k_LogErrorf("[program] %s\n", log);
    }

    glDetachShader(program, vertexShader);
    glDetachShader(program, fragmentShader);

    ret.value = program;
    return ret;
}