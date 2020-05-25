#ifndef _K_WORLD_SCENARIO_H_
#define _K_WORLD_SCENARIO_H_

#include "../graphics/graphics.h"
#include "../math/math.h"

typedef struct k_Scenario k_Scenario;

k_Scenario* k_ScenarioCreate();
void k_ScenarioDestroy(k_Scenario** restrict);

void k_ScenarioDraw(k_Renderer* restrict renderer,
                    k_Scenario* restrict scenario,
                    k_Mat4* restrict mvp);

#endif  // _K_WORLD_SCENARIO_H_
