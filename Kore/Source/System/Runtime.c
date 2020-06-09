#include <GL/glew.h>
#include <GL/gl.h>
#include <SDL2/SDL.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "../Memory/Memory.h"
#include "../Log/Log.h"
#include "Runtime.h"
#include "Var.h"

// ========================================================
//
// Declaration
//
// ========================================================

static void handleEvents(k_Executable *restrict self,
                         float dt,
                         bool *restrict quit);

static void initCoreLibs(void);

static void initVAO(void);

static void initGL(void);

// ========================================================
//
// Public implementation
//
// ========================================================

void k_Init(void) {
    initCoreLibs();
    initGL();
    initVAO();
    k_InitMemory(128);
    k_Logf("fully initialized\n");
}

void k_Quit(void) {
    glDeleteVertexArrays(1, &k_gVertexArray);
    SDL_GL_DeleteContext(k_gWindow);
    SDL_DestroyWindow(k_gWindow);
    SDL_Quit();

    k_gGLContext = NULL;
    k_gWindow = NULL;
}

void k_Run(k_Executable *restrict exec) {
    const float frameTime = 1000.0 / k_gFramesPerSecond;
    uint32_t currentTime = SDL_GetTicks();
    uint32_t lasTime = currentTime;
    float timeDiff = 0;

    bool quit = false;

    exec->Init(exec);
    while (!quit) {
        currentTime = SDL_GetTicks();
        timeDiff = currentTime - lasTime;
        if (timeDiff < frameTime) {
            continue;
        }

        lasTime = currentTime;
        float dt = timeDiff / 1000.0;

        handleEvents(exec, dt, &quit);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        exec->Step(exec, dt);

        SDL_GL_SwapWindow(k_gWindow);
    }
    exec->Quit(exec);
}

// ========================================================
//
// Private implementation
//
// ========================================================

static void initCoreLibs(void) {
    glewExperimental = true;
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        k_LogErrorf("[sdl] %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    k_Logf("successfully initialized SDL\n");

    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS,
                        SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                        SDL_GL_CONTEXT_PROFILE_CORE);

    int winFlags = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL;
    k_gWindow = SDL_CreateWindow("OpenGL Tutorial",
                                 SDL_WINDOWPOS_CENTERED,
                                 SDL_WINDOWPOS_CENTERED,
                                 1280,
                                 720,
                                 winFlags);
    k_Logf("successfully created a window\n");
    if (!k_gWindow) {
        k_LogErrorf("[sdl] %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    k_gGLContext = SDL_GL_CreateContext(k_gWindow);
    if (!k_gGLContext) {
        k_LogErrorf("[sdl] %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    k_Logf("successfully initialized created a OpenGL context\n");

    // This makes our buffer swap syncronized with the
    // monitor's vertical refresh
    SDL_GL_SetSwapInterval(1);

    SDL_GL_MakeCurrent(k_gWindow, k_gGLContext);
    if (glewInit() != GLEW_OK) {
        k_LogErrorf("Failed to initialize GLEW.\n");
        exit(EXIT_FAILURE);
    }
    k_Logf("successfully initialized GLEW\n");
}

static void initGL(void) {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);
}

static void initVAO(void) {
    glGenVertexArrays(1, &k_gVertexArray);
    glBindVertexArray(k_gVertexArray);
}

static void handleEvents(k_Executable *restrict self,
                         float dt,
                         bool *restrict quit) {
    k_InputEventHandlerFunc handler = self->HandleInputEvent;
    k_InputEvent realEvent;
    SDL_Event e;

    while (SDL_PollEvent(&e)) {
        switch (e.type) {
            case SDL_QUIT:
                *quit = true;
                break;
            default:
                if (k_InputEventTranslate(&realEvent, &e)) {
                    handler(self, &realEvent, dt);
                }
                break;
        }
    }
}
