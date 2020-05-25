#include "renderer.h"
#include "../../memory/memory.h"

#include <GL/glew.h>
#include <GL/gl.h>

static const size_t _64Kb = 64 * 1024;

struct k_Renderer {
    GLuint vertexBuffer;
    GLuint colorBuffer;
    GLuint transform;
    GLuint mvp;
};

// k_Renderer* k_RendererCreate(GLuint program) {
k_Renderer* k_RendererCreate(GLuint program) {
    k_Renderer* r = malloc(sizeof(k_Renderer));
    if (!r) {
        return NULL;
    }

    glGenBuffers(1, &r->vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, r->vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, _64Kb, NULL, GL_DYNAMIC_DRAW);

    glGenBuffers(1, &r->colorBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, r->colorBuffer);
    glBufferData(GL_ARRAY_BUFFER, _64Kb, NULL, GL_DYNAMIC_DRAW);

    r->transform = glGetUniformLocation(program, "Transform");
    r->mvp = glGetUniformLocation(program, "MVP");
    return r;
}

void k_RendererDestroy(k_Renderer* r) {
    if (!r) {
        return;
    }

    glDeleteBuffers(1, &r->vertexBuffer);
    glDeleteBuffers(1, &r->colorBuffer);
    k_Delete(r);
}

void k_RendererDrawTriangles(k_Renderer* r,
                             const k_Mat4* restrict transform,
                             const k_Mat4* restrict mvp,
                             const float* restrict data,
                             size_t size) {
    glUniformMatrix4fv(r->transform,
                       1,
                       GL_FALSE,
                       (const GLfloat*)&transform->m[0][0]);

    glUniformMatrix4fv(r->mvp,
                       1,
                       GL_FALSE,
                       (const GLfloat*)&mvp->m[0][0]);

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

void k_RendererColorTriangles(k_Renderer* r,
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
