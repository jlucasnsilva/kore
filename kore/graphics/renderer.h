#ifndef _K_GRAPHICS_RENDERER_H_
#define _K_GRAPHICS_RENDERER_H_

#include "../math/math.h"
#include "shader.h"

#include <stdlib.h>

#ifdef LinuxBuild
#include <GL/glew.h>
#include <GL/gl.h>

typedef struct {
    k_ShaderProgram shaderProgram;
    GLuint vertexBuffer;
    GLuint colorBuffer;
    GLuint uvBuffer;
    GLuint transform;
} k_Renderer;
#endif  // LinuxBuild

k_Renderer* k_RendererCreate();

void k_RendererDestroy(k_Renderer* restrict r);

void k_RendererDrawTriangles(k_Renderer* restrict r,
                             const k_Mat4* restrict transform,
                             const float* restrict data,
                             size_t size);

void k_RendererColorTriangles(k_Renderer* restrict r,
                              const float* restrict data,
                              size_t size);

void k_RendererMapUV(k_Renderer* restrict r,
                     const float* restrict data,
                     size_t size);

void k_RendererSetShaderProgram(k_Renderer* restrict r,
                                k_ShaderProgram program);

#endif  // _K_GRAPHICS_RENDERER_H_
