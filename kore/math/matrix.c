#include "matrix.h"
#include "vector.h"
#include "angle.h"

#include <math.h>

void Mat4SetVec4(Mat4 *restrict result, Vec4 a, Vec4 b, Vec4 c) {
    result->v[0] = a;
    result->v[1] = b;
    result->v[2] = c;
    result->v[3] = bVec4(.x = 0.0f, .y = 0.0f, .z = 0.0f, .w = 1.0f);
}

Vec4 Mat4Vec4(const Mat4 *restrict m, Vec4 v) {
    Vec4 result;
    for (int i = 0; i < 4; i++) {
        result.v[i] = Vec4Dot(m->v[i], v);
    }
    return result;
}

void Mat4Rotation(Mat4 *restrict result, Vec3 rotation) {
    float a = DegreeToRad(rotation.x);  // yaw
    float b = DegreeToRad(rotation.y);  // pitch
    float c = DegreeToRad(rotation.z);  // roll

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
