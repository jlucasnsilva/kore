#ifndef _K_MATH_VECTOR_H_
#define _K_MATH_VECTOR_H_

#include "vector_generic.h"

typedef union {
    struct {
        float x;
        float y;
    };
    float v[2];
} k_Vec2;

typedef union {
    struct {
        float x;
        float y;
        float z;
    };
    float v[3];
} k_Vec3;

typedef union {
    struct {
        float x;
        float y;
        float z;
        float w;
    };
    float v[4];
} k_Vec4;

#define k_Vec2Spread(v) (v).x, (v).y
#define k_bVec2(...) ((k_Vec2){{.x = 0.0f, .y = 0.0f, __VA_ARGS__}})

#define k_Vec3Spread(v) (v).x, (v).y, (v).z,
#define k_bVec3(...) ((k_Vec3){{.x = 0.0f, .y = 0.0f, .z = 0.0f, __VA_ARGS__}})

#define k_Vec4Spread(v) (v).x, (v).y, (v).z, (v).w
#define k_bVec4(...) ((k_Vec4){{.x = 0.0f, \
                                .y = 0.0f, \
                                .z = 0.0f, \
                                .w = 0.0f, \
                                __VA_ARGS__}})

const k_Vec2 k_Vec2Zero = k_bVec2();
const k_Vec3 k_Vec3Zero = k_bVec3();
const k_Vec4 k_Vec4Zero = k_bVec4();

// ========================================================
//
// Generic
//
// ========================================================

K_DEFINE_VEC_PAIR_SIMPLE_OPERATION(k_Vec2, Add, +)
K_DEFINE_VEC_PAIR_SIMPLE_OPERATION(k_Vec2, Sub, -)
K_DEFINE_VEC_PAIR_SIMPLE_OPERATION(k_Vec2, Times, *)
K_DEFINE_VEC_PAIR_SIMPLE_OPERATION(k_Vec2, Div, /)
K_DEFINE_VEC_PAIR_DISTANCE_SQUARED(k_Vec2)
K_DEFINE_VEC_PAIR_DISTANCE(k_Vec2)
K_DEFINE_VEC_PAIR_DOT(k_Vec2)
K_DEFINE_VEC_PAIR_EQ(k_Vec2)
K_DEFINE_VEC_LEN_SQUARED(k_Vec2)
K_DEFINE_VEC_LEN(k_Vec2)
K_DEFINE_VEC_SCALE(k_Vec2)
K_DEFINE_VEC_NORMALIZE(k_Vec2)

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
    return k_bVec3(.x = (a.y * b.z) - (a.z * b.y),
                   .y = (a.z * b.x) - (a.x * b.z),
                   .z = (a.x * b.y) - (a.y * b.x));
}

static inline k_Vec3 k_Vec3FromVec4(k_Vec4 v) {
    return k_bVec3(.x = v.x, .y = v.y, .z = v.z);
}

static inline k_Vec4 k_Vec4FromVec3(k_Vec4 v) {
    return k_bVec4(.x = v.x, .y = v.y, .z = v.z, .w = 1.0f);
}

#endif  // _K_MATH_VECTOR_H_