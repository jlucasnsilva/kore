#include <Kore/Kore.h>

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
    k_Executable exec;
    // ---------------------
    k_Renderer* renderer;
    k_PerpectiveCamera* cam;
} Game;

static k_ShapeCube cube;
static float color[sizeof(k_ShapeCube) / sizeof(float)];

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

    g->cam = k_PerpectiveCameraCreate();
    if (!g->cam) {
        k_Logf("unable to acquire memory for the camera");
        exit(EXIT_FAILURE);
    }
    g->cam->position = k_bVec3(.X = 5.0f, .Y = 5.0f, .Z = 5.0f);
    k_PerpectiveCameraUpdate(g->cam);

    g->renderer = k_RendererCreate();
    loadShaderProgram(g->renderer);
    if (!g->renderer) {
        k_LogErrorf("Not enough memory to create a renderer\n");
        exit(EXIT_FAILURE);
    }

    k_ShapeCubeMake(&cube);
    k_ShapeCubeColor(color);
}

static void step(k_Executable* restrict self, float dt) {
    Game* g = k_Ptr(self);
    k_Renderer* r = g->renderer;
    k_PerpectiveCamera* cam = g->cam;

    k_Mat4 model = k_bMat4I();
    k_Mat4 mvp;

    k_Mat4Mul3(&mvp, &model, &cam->view, &cam->projection);
    k_RendererDrawTriangles(r, &mvp, (void*)&cube, sizeof(k_ShapeCube));
    k_RendererColorTriangles(r, color, sizeof(k_ShapeCube));
}

static void loadShaderProgram(k_Renderer* restrict renderer) {
    char* vfp = "Kore/Shader/Color/vertex.glsl";
    char* ffp = "Kore/Shader/Color/fragment.glsl";

    bool ok = k_LoadShaders(renderer,
                            k_bShaderLoader(.Filepath = vfp,
                                            .Type = k_ShaderTypeVertex),
                            k_bShaderLoader(.Filepath = ffp,
                                            .Type = k_ShaderTypeFragment));
    if (!ok) {
        exit(EXIT_FAILURE);
    }
}

static void quit(k_Executable* restrict self) {
    Game* g = k_Ptr(self);
    k_PerpectiveCameraDestroy(&g->cam);
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

            k_PerpectiveCameraUpdate(g->cam);
            break;
        case k_InputEventTypeMouseWheelMotion:
            d = k_bVec3(.Y = -1 * event->MouseWheelMotion.Y,
                        .Z = -1 * event->MouseWheelMotion.Y);
            g->cam->position = k_Vec3Add(g->cam->position, d);
            k_PerpectiveCameraUpdate(g->cam);
            break;
        default:
            break;
    }
}
