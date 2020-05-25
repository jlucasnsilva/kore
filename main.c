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
    k_Scenario* scenario;
    k_Mat4 projection;
    k_Mat4 model;
    k_Mat4 view;
    k_Mat4 mvp;
} Game;

static k_HexagonBlock hexagon;
static GLfloat color[sizeof(k_HexagonBlock) / sizeof(float)];

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
    g->scenario = k_ScenarioCreate();
    if (!g->scenario) {
        k_Logf("unable to acquire memory for the scenario");
        exit(EXIT_FAILURE);
    }

    k_HexagonBlockMake(&hexagon);
    k_HexagonBlockColor(color);

    g->model = k_bMat4I();
    // k_Mat4LookAt(&g->view, k_bVec3(.z = -15.0f, .y = 15.0f), k_bVec3(), k_bVec3(.y = 1));
    k_Mat4LookAt(&g->view, k_bVec3(.y = 5.0f, .z = 5.0f), k_bVec3(), k_bVec3(.y = 1));
    k_Mat4Perspective(&g->projection, 45.0f, 16.0f / 9.0f, 0.1f, 100.0f);
    k_Mat4Mul3(&g->mvp, &g->model, &g->view, &g->projection);

    g->program = loadShaderProgram();
    g->renderer = k_RendererCreate(g->program);
    if (!g->renderer) {
        k_LogErrorf("Not enough memory to create a renderer\n");
        exit(EXIT_FAILURE);
    }
}

static void step(k_Executable* restrict self, float dt) {
    Game* g = k_Ptr(self);
    k_Renderer* r = g->renderer;

    glUseProgram(g->program);
    k_ScenarioDraw(r, g->scenario, &g->mvp);
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
    k_ScenarioDestroy(&g->scenario);
    k_RendererDestroy(g->renderer);
    glDeleteProgram(g->program);
}
