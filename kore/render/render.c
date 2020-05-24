#include "render.h"
#include "../memory/memory.h"

#include <GL/glew.h>
#include <GL/gl.h>

struct k_Renderer {
    GLuint vertexBuffer;
    GLuint colorBuffer;
    GLuint mvp;
};

// k_Renderer* k_RendererCreate(GLuint program) {
k_Renderer* k_RendererCreate(GLuint program, float* data, float* colors, size_t size) {
    k_Renderer* r = malloc(sizeof(k_Renderer));
    if (!r) {
        return NULL;
    }

    glGenBuffers(1, &r->vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, r->vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);

    glGenBuffers(1, &r->colorBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, r->colorBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(data), colors, GL_STATIC_DRAW);

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
                             const k_Mat4* restrict mvp,
                             const float* restrict data,
                             size_t size) {
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    glUniformMatrix4fv(r->mvp, 1, GL_FALSE, (const GLfloat*)&mvp->m[0][0]);

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

    glDrawArrays(GL_TRIANGLES, 0, size / (2 * sizeof(float)));
    glDisableVertexAttribArray(0);
}

void k_RendererColorTriangles(k_Renderer* r, const float* restrict data, size_t size) {
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
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
}
