#ifndef _K_MATH_VECTOR_H_
#define _K_MATH_VECTOR_H_

#include "vector_generic.h"

typedef union {
    struct {
        float X;
        float Y;
        float Z;
    };
    float V[3];
} k_Vec3;

typedef union {
    struct {
        float X;
        float Y;
        float Z;
        float W;
    };
    float V[4];
} k_Vec4;

#define k_Vec3Spread(v) (v).X, (v).Y, (v).Z,
#define k_bVec3(...) ((k_Vec3){{.X = 0.0f, .Y = 0.0f, .Z = 0.0f, __VA_ARGS__}})

#define k_Vec4Spread(v) (v).X, (v).Y, (v).Z, (v).w
#define k_bVec4(...) ((k_Vec4){{.X = 0.0f, \
                                .Y = 0.0f, \
                                .Z = 0.0f, \
                                .W = 0.0f, \
                                __VA_ARGS__}})

extern const k_Vec3 k_Vec3Zero;
extern const k_Vec4 k_Vec4Zero;

// ========================================================
//
// Generic
//
// ========================================================

K_DEFINE_VEC_PAIR_SIMPLE_OPERATION(k_Vec3, Add, +)
K_DEFINE_VEC_PAIR_SIMPLE_OPERATION(k_Vec3, Sub, -)
K_DEFINE_VEC_PAIR_SIMPLE_OPERATION(k_Vec3, Times, *)
K_DEFINE_VEC_PAIR_SIMPLE_OPERATION(k_Vec3, Div, /)
K_DEFINE_VEC_PAIR_DISTANCE_SQUARED(k_Vec3)
K_DEFINE_VEC_PAIR_DISTANCE(k_Vec3)
K_DEFINE_VEC_PAIR_DOT(k_Vec3)
K_DEFINE_VEC_PAIR_EQ(k_Vec3)
K_DEFINE_VEC_LEN_SQUARED(k_Vec3)
K_DEFINE_VEC_LEN(k_Vec3)
K_DEFINE_VEC_SCALE(k_Vec3)
K_DEFINE_VEC_NORMALIZE(k_Vec3)

K_DEFINE_VEC_PAIR_SIMPLE_OPERATION(k_Vec4, Add, +)
K_DEFINE_VEC_PAIR_SIMPLE_OPERATION(k_Vec4, Sub, -)
K_DEFINE_VEC_PAIR_SIMPLE_OPERATION(k_Vec4, Times, *)
K_DEFINE_VEC_PAIR_SIMPLE_OPERATION(k_Vec4, Div, /)
K_DEFINE_VEC_PAIR_DISTANCE_SQUARED(k_Vec4)
K_DEFINE_VEC_PAIR_DISTANCE(k_Vec4)
K_DEFINE_VEC_PAIR_DOT(k_Vec4)
K_DEFINE_VEC_PAIR_EQ(k_Vec4)
K_DEFINE_VEC_LEN_SQUARED(k_Vec4)
K_DEFINE_VEC_LEN(k_Vec4)
K_DEFINE_VEC_SCALE(k_Vec4)
K_DEFINE_VEC_NORMALIZE(k_Vec4)

// ========================================================
//
// Other
//
// ========================================================

static inline k_Vec3 k_Vec3Cross(k_Vec3 a, k_Vec3 b) {
    return k_bVec3(.X = (a.Y * b.Z) - (a.Z * b.Y),
                   .Y = (a.Z * b.X) - (a.X * b.Z),
                   .Z = (a.X * b.Y) - (a.Y * b.X));
}

static inline k_Vec3 k_Vec3FromVec4(k_Vec4 v) {
    return k_bVec3(.X = v.X, .Y = v.Y, .Z = v.Z);
}

static inline k_Vec4 k_Vec4FromVec3(k_Vec4 v) {
    return k_bVec4(.X = v.X, .Y = v.Y, .Z = v.Z, .W = 1.0f);
}

#endif  // _K_MATH_VECTOR_H_