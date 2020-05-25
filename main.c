#include "kore/kore.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

static void init(k_Executable* restrict self);
static void quit(k_Executable* restrict self);
static void step(k_Executable* restrict self, float dt);

static GLuint loadShaderProgram();

typedef struct {
    k_Executable exec;
    GLuint program;
    k_Renderer* renderer;
    k_Mat4 projection;
    k_Mat4 model;
    k_Mat4 view;
    k_Mat4 mvp;
    k_Vec3 rotation;
} Game;

static k_Cube cube;
static GLfloat* data;
static GLfloat color[3 * 36];

// ========================================================
// ========================================================
// ========================================================
// ========================================================

// GLuint vertexBufferID;
// GLuint colorBufferID;
// GLuint mvpID;
// GLuint rotID;

// ========================================================
// ========================================================
// ========================================================
// ========================================================

int main(void) {
    Game game;
    game.exec = k_bExecutable(.Step = step, .Init = init, .Quit = quit);

    k_Init();
    k_Run(&game.exec);
    k_Quit();
    return 0;
}

static void init(k_Executable* restrict self) {
    Game* g = k_Ptr(self);

    k_CubeMake(&cube, k_bVec3(), 2.0f);
    k_CubeColor(color);
    data = k_Ptr(&cube);

    g->rotation = k_bVec3();
    g->model = k_bMat4I();
    k_Mat4LookAt(&g->view, k_bVec3(.x = -5.0f, .y = 5.0f, .z = -5.0f), k_bVec3(), k_bVec3(.y = 1));
    k_Mat4Perspective(&g->projection, 45.0f, 16.0f / 9.0f, 0.1f, 100.0f);
    k_Mat4MVP(&g->mvp, &g->model, &g->view, &g->projection);

    g->program = loadShaderProgram();
    g->renderer = k_RendererCreate(g->program);
    if (!g->renderer) {
        k_LogErrorf("Not enough memory to create a renderer\n");
        exit(EXIT_FAILURE);
    }

    /*
    glGenBuffers(1, &vertexBufferID);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
    glBufferData(GL_ARRAY_BUFFER, 3 * 36 * sizeof(float), data, GL_STATIC_DRAW);

    glGenBuffers(1, &colorBufferID);
    glBindBuffer(GL_ARRAY_BUFFER, colorBufferID);
    glBufferData(GL_ARRAY_BUFFER, 3 * 36 * sizeof(float), color, GL_STATIC_DRAW);

    mvpID = glGetUniformLocation(g->program, "MVP");
    rotID = glGetUniformLocation(g->program, "Transform");
    */
}

static void step(k_Executable* restrict self, float dt) {
    Game* g = k_Ptr(self);
    k_Renderer* r = g->renderer;

    k_Mat4 rot;

    g->rotation = k_Vec3Add(g->rotation, k_bVec3(.x = 3.6 * dt,
                                                 .y = 3.6 * dt,
                                                 .z = -3.6 * dt));
    k_Mat4Rotation(&rot, g->rotation);

    glUseProgram(g->program);
    k_RendererDrawTriangles(r, &rot, &g->mvp, data, sizeof(cube));
    k_RendererColorTriangles(r, color, sizeof(color));

    /*
    glUniformMatrix4fv(mvpID, 1, GL_FALSE, (const GLfloat*)&g->mvp.m[0][0]);
    glUniformMatrix4fv(rotID, 1, GL_FALSE, (const GLfloat*)&rot.m[0][0]);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
    glVertexAttribPointer(
        0,         // attribute 0. No particular reason for 0, but must match the layout in the shader.
        3,         // size
        GL_FLOAT,  // type
        GL_FALSE,  // normalized?
        0,         // stride
        (void*)0   // array buffer offset
    );
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glDisableVertexAttribArray(0);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, colorBufferID);
    glVertexAttribPointer(
        1,         // attribute. No particular reason for 1, but must match the layout in the shader.
        3,         // size
        GL_FLOAT,  // type
        GL_FALSE,  // normalized?
        0,         // stride
        (void*)0   // array buffer offset
    );
    glDisableVertexAttribArray(1);
    */
}

static GLuint loadShaderProgram() {
    k_ShaderProgramLoader loader;
    k_Maybe(GLuint) mprogram;

    strncpy(loader.VertexShaderPath, "vertex.glsl", 512);
    strncpy(loader.FragmentShaderPath, "fragment.glsl", 512);

    mprogram = k_LoadShaderProgram(&loader);
    if (!mprogram.ok) {
        exit(EXIT_FAILURE);
    }
    return mprogram.value;
}

static void quit(k_Executable* restrict self) {
    Game* g = k_Ptr(self);
    // k_RendererDestroy(g->renderer);
    glDeleteProgram(g->program);
}
