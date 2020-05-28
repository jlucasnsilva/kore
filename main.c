#include "kore/kore.h"
#include "hexapod/hexapod.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

static void init(k_Executable* restrict self);
static void quit(k_Executable* restrict self);
static void step(k_Executable* restrict self, float dt);
static void handler(k_Executable* self, k_InputEvent* restrict event, float dt);

static void loadShaderProgram(k_Renderer* restrict renderer);

typedef struct {
    k_Texture tex;
    k_Executable exec;
    k_Renderer* renderer;
    hx_Scenario* scenario;
    k_PerpectiveCamera* cam;
    float* uv;
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
    k_Run(&game.exec);
    k_Quit();
    return 0;
}

static void init(k_Executable* restrict self) {
    Game* g = k_Ptr(self);
    g->scenario = hx_ScenarioCreate();
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
    g->renderer = k_RendererCreate();
    loadShaderProgram(g->renderer);
    if (!g->renderer) {
        k_LogErrorf("Not enough memory to create a renderer\n");
        exit(EXIT_FAILURE);
    }

    g->tex = k_LoadTexture("game/assets/hexagon.png");
    if (g->tex.Width < 0 || g->tex.Height < 0) {
        k_LogErrorf("Failed to load the texture\n");
        exit(EXIT_FAILURE);
    }

    size_t uvBytes = sizeof(k_ShapeHexagon);
    size_t uvSize = uvBytes / sizeof(float);
    g->uv = malloc(uvBytes);
    if (!g->uv) {
        k_LogErrorf("Failed to load the UV mappings\n");
        exit(EXIT_FAILURE);
    }

    k_ShapeHexagonUV(g->uv, uvSize);
}

static void step(k_Executable* restrict self, float dt) {
    Game* g = k_Ptr(self);
    k_Renderer* r = g->renderer;
    k_PerpectiveCamera* cam = g->cam;

    k_Mat4 model = k_bMat4I();
    k_Mat4 mvp;

    k_Mat4Mul3(&mvp, &model, &cam->view, &cam->projection);
    hx_ScenarioDraw(r, g->scenario, &mvp, g->uv, sizeof(k_ShapeHexagonUV));
}

static void loadShaderProgram(k_Renderer* restrict renderer) {
    bool ok = k_LoadShaders(renderer,
                            k_bShaderLoader(.Filepath = "vertex.glsl",
                                            .Type = k_ShaderTypeVertex),
                            k_bShaderLoader(.Filepath = "fragment.glsl",
                                            .Type = k_ShaderTypeFragment));
    if (!ok) {
        exit(EXIT_FAILURE);
    }
}

static void quit(k_Executable* restrict self) {
    Game* g = k_Ptr(self);
    hx_ScenarioDestroy(&g->scenario);
    k_RendererDestroy(g->renderer);
}

static void handler(k_Executable* self,
                    k_InputEvent* restrict event,
                    float dt) {
    Game* g = k_Ptr(self);
    float speed = 0.3f;
    k_Vec3 d;

    switch (event->Type) {
        case k_InputEventTypeKeyPressed:
            if (event->KeyPressed.Scancode == SDL_SCANCODE_W) {
                g->cam->position.Z -= speed;
                g->cam->target.Z -= speed;
            } else if (event->KeyPressed.Scancode == SDL_SCANCODE_S) {
                g->cam->position.Z += speed;
                g->cam->target.Z += speed;
            }

            if (event->KeyPressed.Scancode == SDL_SCANCODE_A) {
                g->cam->position.X -= speed;
                g->cam->target.X -= speed;
            } else if (event->KeyPressed.Scancode == SDL_SCANCODE_D) {
                g->cam->position.X += speed;
                g->cam->target.X += speed;
            }

            if (event->KeyPressed.Scancode == SDL_SCANCODE_UP) {
                d = k_bVec3(.Y = -0.1f);
                g->cam->position = k_Vec3Add(g->cam->position, d);
            } else if (event->KeyPressed.Scancode == SDL_SCANCODE_DOWN) {
                d = k_bVec3(.Y = 0.1f);
                g->cam->position = k_Vec3Add(g->cam->position, d);
            }

            printf("camera.position = <%.2f, %.2f, %.2f>\n",
                   g->cam->position.X,
                   g->cam->position.Y,
                   g->cam->position.Z);
            printf("  camera.target = <%.2f, %.2f, %.2f>\n",
                   g->cam->target.X,
                   g->cam->target.Y,
                   g->cam->target.Z);
            k_PerpectiveCameraUpdate(g->cam);
            break;
        case k_InputEventTypeMouseWheelMotion:
            d = k_bVec3(.Y = -1 * event->MouseWheelMotion.Y,
                        .Z = -1 * event->MouseWheelMotion.Y);
            g->cam->position = k_Vec3Add(g->cam->position, d);
            k_PerpectiveCameraUpdate(g->cam);
            printf("camera.position = <%.2f, %.2f, %.2f>\n",
                   g->cam->position.X,
                   g->cam->position.Y,
                   g->cam->position.Z);
            printf("  camera.target = <%.2f, %.2f, %.2f>\n",
                   g->cam->target.X,
                   g->cam->target.Y,
                   g->cam->target.Z);
            break;
        default:
            break;
    }
}
