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
} Quaternion;

#define bQuaternion(...) ((Quaternion){{.w = 0.0f, \
                                        .x = 0.0f, \
                                        .y = 0.0f, \
                                        .z = 0.0f, \
                                        __VA_ARGS__}})

const Quaternion QuaternionZero = bQuaternion();

static inline Quaternion QuaternionMake(float w, Vec3 v) {
    return bQuaternion(.x = v.x, .y = v.y, .z = v.z, .w = w);
}

static inline Vec3 QuaternionToVec3(Quaternion q) {
    return bVec3(.x = q.x, .y = q.y, .z = q.z);
}

static inline Quaternion QuaternionFromVec3(Vec3 v) {
    return bQuaternion(.x = v.x, .y = v.y, .z = v.z, .w = 0.0f);
}

static inline Quaternion QuaternionInverse(Quaternion q) {
    return bQuaternion(.w = q.w,
                       .x = -q.x,
                       .y = -q.y,
                       .z = -q.z);
}

// Grassman product
static inline Quaternion QuaternionMul(Quaternion p, Quaternion q) {
    Vec3 pv = QuaternionToVec3(p);
    Vec3 qv = QuaternionToVec3(q);
    float w = p.w * q.w - Vec3Dot(pv, qv);
    Vec3 aux = Vec3Add(Vec3Scale(qv, p.w), Vec3Scale(pv, q.w));
    Vec3 v = Vec3Add(aux, Vec3Cross(pv, qv));

    return QuaternionMake(w, v);
}

static inline Quaternion QuaternionRotation(Vec3 v, float angle) {
    float a = angle / 360.0f * PI * 2.0f;  // to radians
    float sina2 = sinf(a / 2);

    return bQuaternion(.w = cosf(a / 2),
                       .x = v.x * sina2,
                       .y = v.y * sina2,
                       .z = v.z * sina2);
}

static inline Vec3 QuaternionRotate(Quaternion rotation, Vec3 v) {
    Quaternion q = rotation;
    Quaternion iq = QuaternionInverse(q);
    Quaternion vq = QuaternionFromVec3(v);

    Quaternion aux = QuaternionMul(q, vq);
    Quaternion res = QuaternionMul(aux, iq);
    return QuaternionToVec3(res);
}

static inline float QuaternionLenSquared(Quaternion q) {
    float len = 0.0f;
    for (int i = 0; i < 4; i++) {
        len += q.v[i] * q.v[i];
    }
    return len;
}

static inline float QuaternionLen(Quaternion q) {
    return sqrtf(QuaternionLenSquared(q));
}

static inline Quaternion QuaternionScale(Quaternion q, float x) {
    Quaternion res;
    for (int i = 0; i < 4; i++) {
        res.v[i] = x * q.v[i];
    }
    return res;
}

static inline Quaternion QuaternionNormalize(Quaternion q) {
    float len = QuaternionLen(q);
    return QuaternionScale(q, len);
}

// Concatenate quaternions:
//   concat(p, q, r, V) = r * q * p * V * ip * iq * ir

#endif  // _K_MATH_QUATERNION_H_
