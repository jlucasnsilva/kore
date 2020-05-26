#ifndef _K_GRAPHICS_CAMERA_H_
#define _K_GRAPHICS_CAMERA_H_

#include "../math/math.h"

typedef struct {
    k_Mat4 projection;
    k_Mat4 view;
    k_Vec3 position;
    k_Vec3 target;
    k_Vec3 up;
    float angleOfView;
    float aspectRatio;
    float near;
    float far;
} k_PerpectiveCamera;

k_PerpectiveCamera* k_PerpectiveCameraCreate();
void k_PerpectiveCameraDestroy(k_PerpectiveCamera** restrict);

void k_PerpectiveCameraUpdate(k_PerpectiveCamera* restrict);

#endif  // _K_GRAPHICS_CAMERA_H_
