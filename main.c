#include "kore/kore.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

static void init(k_Executable* restrict self);
static void quit(k_Executable* restrict self);
static void step(k_Executable* restrict self, float dt);
static void handler(k_Executable* self, k_InputEvent* restrict event, float dt);

static GLuint loadShaderProgram();

typedef struct {
    k_Executable exec;
    GLuint program;
    k_Renderer* renderer;
    k_Scenario* scenario;
    k_PerpectiveCamera* cam;
} Game;

static k_ShapeHexagonBlock hexagon;
static GLfloat color[sizeof(k_ShapeHexagonBlock) / sizeof(float)];

int main(void) {
    Game game;
    game.exec = k_bExecutable(.Step = step,
                              .Init = init,
                              .Quit = quit,
                              .HandleInputEvent = handler);

    k_Init();

    SDL_RWops* io = SDL_RWFromFile("car.sh", "r");
    printf("> size = %ld\n", SDL_RWsize(io));
    SDL_RWclose(io);

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

    g->cam = k_PerpectiveCameraCreate();
    if (!g->cam) {
        k_Logf("unable to acquire memory for the camera");
        exit(EXIT_FAILURE);
    }

    k_ShapeHexagonBlockMake(&hexagon);
    k_ShapeHexagonBlockColor(color);
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
    k_PerpectiveCamera* cam = g->cam;

    k_Mat4 model = k_bMat4I();
    k_Mat4 mvp;

    k_Mat4Mul3(&mvp, &model, &cam->view, &cam->projection);
    glUseProgram(g->program);
    k_ScenarioDraw(r, g->scenario, &mvp);
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

static void handler(k_Executable* self,
                    k_InputEvent* restrict event,
                    float dt) {
    Game* g = k_Ptr(self);
    float speed = 0.3f;
    k_Vec3 d;

    switch (event->type) {
        case k_InputEventTypeKeyPressed:
            if (event->keyPressed.scancode == SDL_SCANCODE_W) {
                g->cam->position.z -= speed;
                g->cam->target.z -= speed;
            } else if (event->keyPressed.scancode == SDL_SCANCODE_S) {
                g->cam->position.z += speed;
                g->cam->target.z += speed;
            }

            if (event->keyPressed.scancode == SDL_SCANCODE_A) {
                g->cam->position.x -= speed;
                g->cam->target.x -= speed;
            } else if (event->keyPressed.scancode == SDL_SCANCODE_D) {
                g->cam->position.x += speed;
                g->cam->target.x += speed;
            }

            if (event->keyPressed.scancode == SDL_SCANCODE_UP) {
                d = k_bVec3(.y = -0.1f);
                g->cam->position = k_Vec3Add(g->cam->position, d);
            } else if (event->keyPressed.scancode == SDL_SCANCODE_DOWN) {
                d = k_bVec3(.y = 0.1f);
                g->cam->position = k_Vec3Add(g->cam->position, d);
            }

            printf("camera.position = <%.2f, %.2f, %.2f>\n",
                   g->cam->position.x,
                   g->cam->position.y,
                   g->cam->position.z);
            printf("  camera.target = <%.2f, %.2f, %.2f>\n",
                   g->cam->target.x,
                   g->cam->target.y,
                   g->cam->target.z);
            k_PerpectiveCameraUpdate(g->cam);
            break;
        case k_InputEventTypeMouseWheelMotion:
            d = k_bVec3(.y = -1 * event->mouseWheelMotion.y,
                        .z = -1 * event->mouseWheelMotion.y);
            g->cam->position = k_Vec3Add(g->cam->position, d);
            k_PerpectiveCameraUpdate(g->cam);
            printf("camera.position = <%.2f, %.2f, %.2f>\n",
                   g->cam->position.x,
                   g->cam->position.y,
                   g->cam->position.z);
            printf("  camera.target = <%.2f, %.2f, %.2f>\n",
                   g->cam->target.x,
                   g->cam->target.y,
                   g->cam->target.z);
            break;
        default:
            break;
    }
}
