#ifndef _K_VAR_H_
#define _K_VAR_H_

#include <GL/glew.h>
#include <GL/gl.h>
#include <SDL2/SDL.h>

// Inicializado no kore.c
extern SDL_Window* k_gWindow;

// Inicializado no kore.c
extern SDL_GLContext k_gGLContext;

extern int k_gFramesPerSecond;

extern GLuint k_gVertexArray;

#endif  // _K_VAR_H_
