#include "matrix.h"
#include "vector.h"
#include "angle.h"

#include <math.h>

void k_Mat4SetVec4(k_Mat4 *restrict result, k_Vec4 a, k_Vec4 b, k_Vec4 c) {
    result->v[0] = a;
    result->v[1] = b;
    result->v[2] = c;
    result->v[3] = k_bVec4(.x = 0.0f, .y = 0.0f, .z = 0.0f, .w = 1.0f);
}

Vec4 k_Mat4Vec4(const k_Mat4 *restrict m, k_Vec4 v) {
    Vec4 result;
    for (int i = 0; i < 4; i++) {
        result.v[i] = k_Vec4Dot(m->v[i], v);
    }
    return result;
}

void k_Mat4Rotation(k_Mat4 *restrict result, k_Vec3 rotation) {
    float a = k_DegreeToRad(rotation.x);  // yaw
    float b = k_DegreeToRad(rotation.y);  // pitch
    float c = k_DegreeToRad(rotation.z);  // roll

    result->m[0][0] = cosf(a) * cosf(b);
    result->m[0][1] = cosf(a) * sinf(b) * sinf(c) - sinf(a) * cosf(c);
    result->m[0][2] = cosf(a) * sinf(b) * cosf(c) + sinf(a) * sinf(c);
    result->m[1][0] = sinf(a) * cosf(b);
    result->m[1][1] = sinf(a) * sinf(b) * sinf(c) + cosf(a) * cosf(b);
    result->m[1][2] = sinf(a) * sinf(b) * cosf(c) - cosf(a) * sinf(c);
    result->m[2][0] = -sinf(b);
    result->m[2][1] = cosf(b) * sinf(c);
    result->m[2][2] = cosf(b) * cosf(c);
}
