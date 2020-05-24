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
} Game;

/*
static GLfloat data[] = {-1.0f, -1.0f, 0.0f,
                         1.0f, -1.0f, 0.0f,
                         0.0f, 1.0f, 0.0f};

static GLfloat color[] = {0.583f, 0.771f, 0.014f,
                          0.609f, 0.115f, 0.436f,
                          0.327f, 0.483f, 0.844f};
*/

static GLfloat data[] = {-1.0f, -1.0f, -1.0f,
                         -1.0f, -1.0f, 1.0f,
                         -1.0f, 1.0f, 1.0f,
                         1.0f, 1.0f, -1.0f,
                         -1.0f, -1.0f, -1.0f,
                         -1.0f, 1.0f, -1.0f,
                         1.0f, -1.0f, 1.0f,
                         -1.0f, -1.0f, -1.0f,
                         1.0f, -1.0f, -1.0f,
                         1.0f, 1.0f, -1.0f,
                         1.0f, -1.0f, -1.0f,
                         -1.0f, -1.0f, -1.0f,
                         -1.0f, -1.0f, -1.0f,
                         -1.0f, 1.0f, 1.0f,
                         -1.0f, 1.0f, -1.0f,
                         1.0f, -1.0f, 1.0f,
                         -1.0f, -1.0f, 1.0f,
                         -1.0f, -1.0f, -1.0f,
                         -1.0f, 1.0f, 1.0f,
                         -1.0f, -1.0f, 1.0f,
                         1.0f, -1.0f, 1.0f,
                         1.0f, 1.0f, 1.0f,
                         1.0f, -1.0f, -1.0f,
                         1.0f, 1.0f, -1.0f,
                         1.0f, -1.0f, -1.0f,
                         1.0f, 1.0f, 1.0f,
                         1.0f, -1.0f, 1.0f,
                         1.0f, 1.0f, 1.0f,
                         1.0f, 1.0f, -1.0f,
                         -1.0f, 1.0f, -1.0f,
                         1.0f, 1.0f, 1.0f,
                         -1.0f, 1.0f, -1.0f,
                         -1.0f, 1.0f, 1.0f,
                         1.0f, 1.0f, 1.0f,
                         -1.0f, 1.0f, 1.0f,
                         1.0f, -1.0f, 1.0f};

static GLfloat color[] = {0.583f, 0.771f, 0.014f,
                          0.609f, 0.115f, 0.436f,
                          0.327f, 0.483f, 0.844f,
                          0.822f, 0.569f, 0.201f,
                          0.435f, 0.602f, 0.223f,
                          0.310f, 0.747f, 0.185f,
                          0.597f, 0.770f, 0.761f,
                          0.559f, 0.436f, 0.730f,
                          0.359f, 0.583f, 0.152f,
                          0.483f, 0.596f, 0.789f,
                          0.559f, 0.861f, 0.639f,
                          0.195f, 0.548f, 0.859f,
                          0.014f, 0.184f, 0.576f,
                          0.771f, 0.328f, 0.970f,
                          0.406f, 0.615f, 0.116f,
                          0.676f, 0.977f, 0.133f,
                          0.971f, 0.572f, 0.833f,
                          0.140f, 0.616f, 0.489f,
                          0.997f, 0.513f, 0.064f,
                          0.945f, 0.719f, 0.592f,
                          0.543f, 0.021f, 0.978f,
                          0.279f, 0.317f, 0.505f,
                          0.167f, 0.620f, 0.077f,
                          0.347f, 0.857f, 0.137f,
                          0.055f, 0.953f, 0.042f,
                          0.714f, 0.505f, 0.345f,
                          0.783f, 0.290f, 0.734f,
                          0.722f, 0.645f, 0.174f,
                          0.302f, 0.455f, 0.848f,
                          0.225f, 0.587f, 0.040f,
                          0.517f, 0.713f, 0.338f,
                          0.053f, 0.959f, 0.120f,
                          0.393f, 0.621f, 0.362f,
                          0.673f, 0.211f, 0.457f,
                          0.820f, 0.883f, 0.371f,
                          0.982f, 0.099f, 0.879f};

// ========================================================
// ========================================================
// ========================================================
// ========================================================

GLuint vertexBufferID;
GLuint colorBufferID;
GLuint mvpID;

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

    g->model = k_bMat4I();
    k_Mat4LookAt(&g->view, k_bVec3(.x = 15.0f, .y = 3.0f, .z = 3.0f), k_bVec3(), k_bVec3(.y = 1));
    k_Mat4Perspective(&g->projection, 45.0f, 16.0f / 9.0f, 0.1f, 100.0f);
    k_Mat4MVP(&g->mvp, &g->model, &g->view, &g->projection);

    g->program = loadShaderProgram();

    glGenBuffers(1, &vertexBufferID);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);

    glGenBuffers(1, &colorBufferID);
    glBindBuffer(GL_ARRAY_BUFFER, colorBufferID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW);

    mvpID = glGetUniformLocation(g->program, "MVP");

    // g->renderer = k_RendererCreate(g->program);
    // if (!g->renderer) {
    //     k_LogErrorf("Not enough memory to create a renderer\n");
    //     exit(EXIT_FAILURE);
    // }
}

static void step(k_Executable* restrict self, float dt) {
    Game* g = k_Ptr(self);
    // k_Renderer* r = g->renderer;

    glUseProgram(g->program);
    glUniformMatrix4fv(mvpID, 1, GL_FALSE, (const GLfloat*)&g->mvp.m[0][0]);

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

    // k_RendererDrawTriangles(r, &g->mvp, data, sizeof(data));
    // k_RendererColorTriangles(r, color, sizeof(color));
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
