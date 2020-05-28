#include "scenario.h"
#include "../../kore/kore.h"

#include <stdlib.h>
#include <math.h>

static const int COLOR_LEN = sizeof(k_ShapeHexagonBlock) / sizeof(float);

static float yellow[COLOR_LEN];
static float yellowLight[COLOR_LEN];
static float green[COLOR_LEN];
static float greenLight[COLOR_LEN];
static float colors[COLOR_LEN];
static k_ShapeHexagonBlock scenarioTile;

hx_Scenario* hx_ScenarioCreate() {
    k_ShapeHexagonBlockMake(&scenarioTile);
    k_ShapeHexagonBlockColor(yellowLight);
    k_ShapeHexagonBlockColor(yellow);
    k_ShapeHexagonBlockColor(greenLight);
    k_ShapeHexagonBlockColor(green);
    for (int i = 0; i < (6 * 3 * 3); i += 3) {
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

    k_ShapeHexagonBlockColor(colors);
    hx_Scenario* scn = k_New(hx_Scenario, 1);
    if (!scn) {
        return NULL;
    }
    for (int i = 0; i < k_bScenarioSize; i++) {
        scn->scaling[i] = k_bVec3(.X = 1.0f, .Y = 0.5f, .Z = 1.0f);
    }
    return scn;
}

void hx_ScenarioDestroy(hx_Scenario** restrict scn) {
    if (scn && *scn) {
        k_Delete(*scn);
    }
}

void hx_ScenarioDraw(k_Renderer* restrict r,
                     hx_Scenario* restrict scn,
                     k_Mat4* restrict mvp,
                     float* uv,
                     size_t uvSize) {
    const float dz = 1.732f;
    const float dx = 1.50f;
    k_Mat4 translation;
    k_Mat4 transform;
    k_Mat4 scaling;
    k_Mat4 ts;
    // float dx = 16.0f;
    // float dz = 8.0f;

    for (int i = 0; i < k_bScenarioHeight; i++) {
        for (int j = 0; j < k_bScenarioWidth; j++) {
            int idx = i * k_bScenarioWidth + j;
            float dh = j % 2 != 0 ? 0.5f * dz : 0.0f;
            k_Vec3 t = k_bVec3(.X = (float)j * dx,
                               .Z = (float)i * dz + dh);

            k_Mat4Scaling(&scaling, scn->scaling[idx]);
            k_Mat4Translation(&translation, t);
            k_Mat4Mul(&ts, &scaling, &translation);
            k_Mat4Mul(&transform, &ts, mvp);

            k_RendererDrawTriangles(r,
                                    &transform,
                                    (void*)&scenarioTile,
                                    sizeof(k_ShapeHexagonBlock));
            k_RendererMapUV(r, uv, uvSize);

            // k_RendererColorTriangles(r,
            //                          colors,
            //                          sizeof(colors));

            // k_RendererColorTriangles(r,
            //                          j % 2 == 0 ? yellow : yellowLight,
            //                          sizeof(greenLight));
        }
    }
}
