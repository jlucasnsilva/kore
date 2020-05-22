#ifndef _K_MATH_VECTOR_H_
#define _K_MATH_VECTOR_H_

#include "vector_generic.h"

typedef union {
    struct {
        float x;
        float y;
    };
    float v[2];
} Vec2;

typedef union {
    struct {
        float x;
        float y;
        float z;
    };
    float v[3];
} Vec3;

typedef union {
    struct {
        float x;
        float y;
        float z;
        float w;
    };
    float v[4];
} Vec4;

#define Vec2Spread(v) (v).x, (v).y
#define bVec2(...) ((Vec2){{.x = 0.0f, .y = 0.0f, __VA_ARGS__}})

#define Vec3Spread(v) (v).x, (v).y, (v).z,
#define bVec3(...) ((Vec3){{.x = 0.0f, .y = 0.0f, .z = 0.0f, __VA_ARGS__}})

#define Vec4Spread(v) (v).x, (v).y, (v).z, (v).w
#define bVec4(...) ((Vec4){{.x = 0.0f, \
                            .y = 0.0f, \
                            .z = 0.0f, \
                            .w = 0.0f, \
                            __VA_ARGS__}})

const Vec2 Vec2Zero = bVec2();
const Vec3 Vec3Zero = bVec3();
const Vec4 Vec4Zero = bVec4();

// ========================================================
//
// Generic
//
// ========================================================

DEFINE_VEC_PAIR_SIMPLE_OPERATION(Vec2, Add, +)
DEFINE_VEC_PAIR_SIMPLE_OPERATION(Vec2, Sub, -)
DEFINE_VEC_PAIR_SIMPLE_OPERATION(Vec2, Times, *)
DEFINE_VEC_PAIR_SIMPLE_OPERATION(Vec2, Div, /)
DEFINE_VEC_PAIR_DISTANCE_SQUARED(Vec2)
DEFINE_VEC_PAIR_DISTANCE(Vec2)
DEFINE_VEC_PAIR_DOT(Vec2)
DEFINE_VEC_PAIR_EQ(Vec2)
DEFINE_VEC_LEN_SQUARED(Vec2)
DEFINE_VEC_LEN(Vec2)
DEFINE_VEC_SCALE(Vec2)
DEFINE_VEC_NORMALIZE(Vec2)

DEFINE_VEC_PAIR_SIMPLE_OPERATION(Vec3, Add, +)
DEFINE_VEC_PAIR_SIMPLE_OPERATION(Vec3, Sub, -)
DEFINE_VEC_PAIR_SIMPLE_OPERATION(Vec3, Times, *)
DEFINE_VEC_PAIR_SIMPLE_OPERATION(Vec3, Div, /)
DEFINE_VEC_PAIR_DISTANCE_SQUARED(Vec3)
DEFINE_VEC_PAIR_DISTANCE(Vec3)
DEFINE_VEC_PAIR_DOT(Vec3)
DEFINE_VEC_PAIR_EQ(Vec3)
DEFINE_VEC_LEN_SQUARED(Vec3)
DEFINE_VEC_LEN(Vec3)
DEFINE_VEC_SCALE(Vec3)
DEFINE_VEC_NORMALIZE(Vec3)

DEFINE_VEC_PAIR_SIMPLE_OPERATION(Vec4, Add, +)
DEFINE_VEC_PAIR_SIMPLE_OPERATION(Vec4, Sub, -)
DEFINE_VEC_PAIR_SIMPLE_OPERATION(Vec4, Times, *)
DEFINE_VEC_PAIR_SIMPLE_OPERATION(Vec4, Div, /)
DEFINE_VEC_PAIR_DISTANCE_SQUARED(Vec4)
DEFINE_VEC_PAIR_DISTANCE(Vec4)
DEFINE_VEC_PAIR_DOT(Vec4)
DEFINE_VEC_PAIR_EQ(Vec4)
DEFINE_VEC_LEN_SQUARED(Vec4)
DEFINE_VEC_LEN(Vec4)
DEFINE_VEC_SCALE(Vec4)
DEFINE_VEC_NORMALIZE(Vec4)

// ========================================================
//
// Other
//
// ========================================================

static inline Vec3 Vec3Cross(Vec3 a, Vec3 b) {
    return bVec3(.x = (a.y * b.z) - (a.z * b.y),
                 .y = (a.z * b.x) - (a.x * b.z),
                 .z = (a.x * b.y) - (a.y * b.x));
}

static inline Vec3 Vec3FromVec4(Vec4 v) {
    return bVec3(.x = v.x, .y = v.y, .z = v.z);
}

static inline Vec4 Vec4FromVec3(Vec4 v) {
    return bVec4(.x = v.x, .y = v.y, .z = v.z, .w = 1.0f);
}

#endif  // _K_MATH_VECTOR_H_
