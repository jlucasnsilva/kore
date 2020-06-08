#ifndef _K_WORLD_SCENARIO_H_
#define _K_WORLD_SCENARIO_H_

#include "../../kore/graphics/graphics.h"
#include "../../kore/math/math.h"

#include <stdlib.h>

// #define k_bScenarioHeight 10
// #define k_bScenarioWidth 12
#define k_bScenarioHeight 1
#define k_bScenarioWidth 1
#define k_bScenarioSize (k_bScenarioHeight * k_bScenarioWidth)

typedef struct {
    k_Vec3 scaling[k_bScenarioSize];
} hx_Scenario;

hx_Scenario* hx_ScenarioCreate();
void hx_ScenarioDestroy(hx_Scenario** restrict);

void hx_ScenarioDraw(k_Renderer* restrict renderer,
                     hx_Scenario* restrict scenario,
                     k_Mat4* restrict mvp,
                     float* uv,
                     size_t uvSize);

#endif  // _K_WORLD_SCENARIO_H_
