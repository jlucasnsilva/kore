#ifndef _K_MATH_QUATERNION_H_
#define _K_MATH_QUATERNION_H_

#include "vector.h"
#include "consts.h"

#include <math.h>
#include <stdlib.h>

typedef union {
    struct {
        float w;  // cosseno da metade do ângulo
        float x;
        float y;
        float z;
    };
    float v[4];
} k_Quaternion;

#define k_bQuaternion(...) ((k_Quaternion){{.w = 0.0f, \
                                            .x = 0.0f, \
                                            .y = 0.0f, \
                                            .z = 0.0f, \
                                            __VA_ARGS__}})

extern const k_Quaternion QuaternionZero;

static inline k_Quaternion k_QuaternionMake(float w, k_Vec3 v) {
    return k_bQuaternion(.x = v.x, .y = v.y, .z = v.z, .w = w);
}

static inline k_Vec3 k_QuaternionToVec3(k_Quaternion q) {
    return k_bVec3(.x = q.x, .y = q.y, .z = q.z);
}

static inline k_Quaternion k_QuaternionFromVec3(k_Vec3 v) {
    return k_bQuaternion(.x = v.x, .y = v.y, .z = v.z, .w = 0.0f);
}

static inline k_Quaternion k_QuaternionInverse(k_Quaternion q) {
    return k_bQuaternion(.w = q.w,
                         .x = -q.x,
                         .y = -q.y,
                         .z = -q.z);
}

// Grassman product
static inline k_Quaternion k_QuaternionMul(k_Quaternion p, k_Quaternion q) {
    k_Vec3 pv = k_QuaternionToVec3(p);
    k_Vec3 qv = k_QuaternionToVec3(q);
    float w = p.w * q.w - k_Vec3Dot(pv, qv);
    k_Vec3 aux = k_Vec3Add(k_Vec3Scale(qv, p.w), k_Vec3Scale(pv, q.w));
    k_Vec3 v = k_Vec3Add(aux, k_Vec3Cross(pv, qv));

    return k_QuaternionMake(w, v);
}

static inline k_Quaternion k_QuaternionRotation(k_Vec3 v, float angle) {
    float a = angle / 360.0f * PI * 2.0f;  // to radians
    float sina2 = sinf(a / 2);

    return k_bQuaternion(.w = cosf(a / 2),
                         .x = v.x * sina2,
                         .y = v.y * sina2,
                         .z = v.z * sina2);
}

static inline k_Vec3 k_QuaternionRotate(k_Quaternion rotation, k_Vec3 v) {
    k_Quaternion q = rotation;
    k_Quaternion iq = k_QuaternionInverse(q);
    k_Quaternion vq = k_QuaternionFromVec3(v);

    k_Quaternion aux = k_QuaternionMul(q, vq);
    k_Quaternion res = k_QuaternionMul(aux, iq);
    return k_QuaternionToVec3(res);
}

static inline float k_QuaternionLenSquared(k_Quaternion q) {
    float len = 0.0f;
    for (int i = 0; i < 4; i++) {
        len += q.v[i] * q.v[i];
    }
    return len;
}

static inline float k_QuaternionLen(k_Quaternion q) {
    return sqrtf(k_QuaternionLenSquared(q));
}

static inline k_Quaternion k_QuaternionScale(k_Quaternion q, float x) {
    k_Quaternion res;
    for (int i = 0; i < 4; i++) {
        res.v[i] = x * q.v[i];
    }
    return res;
}

static inline k_Quaternion QuaternionNormalize(k_Quaternion q) {
    float len = k_QuaternionLen(q);
    return k_QuaternionScale(q, len);
}

// Concatenate quaternions:
//   concat(p, q, r, V) = r * q * p * V * ip * iq * ir

#endif  // _K_MATH_QUATERNION_H_
