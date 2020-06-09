#ifdef LinuxBuild

#include "Renderer.h"
#include "Shader.h"
#include "../Memory/Memory.h"

#include <GL/glew.h>
#include <GL/gl.h>

static const size_t g64Kb = 64 * 1024;

k_Renderer* k_RendererCreate() {
    k_Renderer* r = malloc(sizeof(k_Renderer));
    if (!r) {
        return NULL;
    }

    glGenBuffers(1, &r->vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, r->vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, g64Kb, NULL, GL_DYNAMIC_DRAW);

    glGenBuffers(1, &r->colorBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, r->colorBuffer);
    glBufferData(GL_ARRAY_BUFFER, g64Kb, NULL, GL_DYNAMIC_DRAW);

    glGenBuffers(1, &r->uvBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, r->uvBuffer);
    glBufferData(GL_ARRAY_BUFFER, g64Kb, NULL, GL_DYNAMIC_DRAW);
    return r;
}

void k_RendererDestroy(k_Renderer* restrict r) {
    if (!r) {
        return;
    }

    glDeleteProgram(r->shaderProgram);
    glDeleteBuffers(1, &r->vertexBuffer);
    glDeleteBuffers(1, &r->colorBuffer);
    k_Delete(r);
}

void k_RendererDrawTriangles(k_Renderer* restrict r,
                             const k_Mat4* restrict transform,
                             const float* restrict data,
                             size_t size) {
    glUseProgram(r->shaderProgram);
    glUniformMatrix4fv(r->transform,
                       1,
                       GL_FALSE,
                       (const GLfloat*)&transform->M[0][0]);

    glNamedBufferSubData(r->vertexBuffer, 0, size, data);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, r->vertexBuffer);
    glVertexAttribPointer(
        0,         // attribute 0. No particular reason for 0, but must match the layout in the shader.
        3,         // size
        GL_FLOAT,  // type
        GL_FALSE,  // normalized?
        0,         // stride
        (void*)0   // array buffer offset
    );

    size_t count = size / (3 * sizeof(float));
    glDrawArrays(GL_TRIANGLES, 0, count);
    glDisableVertexAttribArray(0);
}

void k_RendererColorTriangles(k_Renderer* restrict r,
                              const float* restrict data,
                              size_t size) {
    glNamedBufferSubData(r->colorBuffer, 0, size, data);
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, r->colorBuffer);
    glVertexAttribPointer(
        1,         // attribute. No particular reason for 1, but must match the layout in the shader.
        3,         // size
        GL_FLOAT,  // type
        GL_FALSE,  // normalized?
        0,         // stride
        (void*)0   // array buffer offset
    );
    // glDisableVertexAttribArray(1);
}

void k_RendererMapUV(k_Renderer* restrict r,
                     const float* restrict data,
                     size_t size) {
    glNamedBufferSubData(r->uvBuffer, 0, size, data);
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, r->uvBuffer);
    glVertexAttribPointer(
        1,         // attribute. No particular reason for 1, but must match the layout in the shader.
        2,         // size
        GL_FLOAT,  // type
        GL_FALSE,  // normalized?
        0,         // stride
        (void*)0   // array buffer offset
    );
    // glDisableVertexAttribArray(1);
}

void k_RendererSetShaderProgram(k_Renderer* restrict r,
                                k_ShaderProgram program) {
    r->shaderProgram = program;
    r->transform = glGetUniformLocation(program, "Transform");
}

#endif
