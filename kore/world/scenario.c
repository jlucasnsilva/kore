#include "scenario.h"
#include "../math/math.h"
#include "../memory/memory.h"
#include "../graphics/graphics.h"

#include <stdlib.h>

static const int SCN_HEIGHT = 16;
static const int SCN_WIDTH = 16;
static const int SCN_SIZE = SCN_HEIGHT * SCN_WIDTH;
static const int COLOR_LEN = sizeof(k_HexagonBlock) / sizeof(float);

static float yellow[COLOR_LEN];
static float yellowLight[COLOR_LEN];
static float green[COLOR_LEN];
static float greenLight[COLOR_LEN];
static float colors[COLOR_LEN];
static k_HexagonBlock scenarioTile;

struct k_Scenario {
    k_Vec3 scaling[SCN_SIZE];
};

k_Scenario* k_ScenarioCreate() {
    k_HexagonBlockMake(&scenarioTile);
    for (int i = 0; i < COLOR_LEN; i += 3) {
        yellowLight[i + 0] = 34.0f / 255.0f;
        yellowLight[i + 1] = 255.0f / 255.0f;
        yellowLight[i + 2] = 128.0f / 255.0f;

        yellow[i + 0] = 34.0f / 255.0f;
        yellow[i + 1] = 255.0f / 255.0f;
        yellow[i + 2] = 106.0f / 255.0f;

        greenLight[i + 0] = 68.0f / 255.0f;
        greenLight[i + 1] = 145.0f / 255.0f;
        greenLight[i + 2] = 102.0f / 255.0f;

        green[i + 0] = 68.0f / 255.0f;
        green[i + 1] = 145.0f / 255.0f;
        green[i + 2] = 76.0f / 255.0f;
    }

    k_HexagonBlockColor(colors);
    k_Scenario* scn = k_New(k_Scenario, 1);
    if (!scn) {
        return NULL;
    }
    for (int i = 0; i < SCN_SIZE; i++) {
        scn->scaling[i] = k_bVec3(.x = 1.0f, .y = 1.0f, .z = 1.0f);
    }
    return scn;
}

void k_ScenarioDestroy(k_Scenario** restrict scn) {
    if (scn && *scn) {
        k_Delete(*scn);
    }
}

void k_ScenarioDraw(k_Renderer* restrict r,
                    k_Scenario* restrict scn,
                    k_Mat4* restrict mvp) {
    k_Mat4 translation;
    k_Mat4 transform;
    k_Mat4 scaling;
    k_Mat4 ts;
    // float dx = 16.0f;
    // float dz = 8.0f;

    for (int i = 0; i < SCN_HEIGHT; i++) {
        for (int j = 0; j < SCN_WIDTH; j++) {
            int idx = i * SCN_WIDTH + j;
            float dh = j % 2 == 0 ? 0.5f : 0.0f;
            k_Vec3 t = k_bVec3(.x = (float)j * 3,
                               .z = (float)i * 3 + dh);

            k_Mat4Scaling(&scaling, scn->scaling[idx]);
            k_Mat4Translation(&translation, t);
            k_Mat4Mul(&ts, &scaling, &translation);
            k_Mat4Mul(&transform, &ts, mvp);

            k_RendererDrawTriangles(r,
                                    &transform,
                                    (void*)&scenarioTile,
                                    sizeof(k_HexagonBlock));
            k_RendererColorTriangles(r,
                                     colors,
                                     sizeof(colors));
            // k_RendererColorTriangles(r,
            //                          j % 2 == 0 ? yellowLight : greenLight,
            //                          sizeof(greenLight));
        }
    }
}
