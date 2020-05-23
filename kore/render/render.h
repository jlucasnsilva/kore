#ifndef _K_RENDER_H_
#define _K_RENDER_H_

#include "../math/math.h"

#include <GL/glew.h>
#include <GL/gl.h>

#include <stdlib.h>

typedef struct k_Renderer k_Renderer;

k_Renderer* k_RendererCreate(GLuint program);
void k_RendererDestroy(k_Renderer* r);

void k_RendererDrawTriangles(k_Renderer* r,
                             const k_Mat4* restrict mvp,
                             const float* restrict data,
                             size_t size);

void k_RendererColorTriangles(k_Renderer* r, const float* restrict data, size_t size);

#endif  // _K_RENDER_H_
