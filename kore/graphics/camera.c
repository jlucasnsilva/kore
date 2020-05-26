#include "camera.h"

#include "../memory/memory.h"

#include <stdlib.h>

k_PerpectiveCamera* k_PerpectiveCameraCreate() {
    k_PerpectiveCamera* cam = k_New(k_PerpectiveCamera, 1);
    if (!cam) {
        return NULL;
    }

    *cam = (k_PerpectiveCamera){
        .position = k_bVec3(.y = 5.0f, .z = 5.0f),
        .aspectRatio = 16.0f / 9.0f,
        .up = k_bVec3(.y = 1.0f),
        .angleOfView = 45.0f,
        .target = k_bVec3(),
        .far = 100.0f,
        .near = 0.1f,
    };
    k_PerpectiveCameraUpdate(cam);
    return cam;
}

void k_PerpectiveCameraDestroy(k_PerpectiveCamera** restrict pcam) {
    if (pcam && *pcam) {
        k_Delete(*pcam);
    }
}

void k_PerpectiveCameraUpdate(k_PerpectiveCamera* restrict cam) {
    k_Mat4LookAt(&cam->view, cam->position, cam->target, cam->up);
    k_Mat4Perspective(&cam->projection,
                      cam->angleOfView,
                      cam->aspectRatio,
                      cam->near,
                      cam->far);
}
