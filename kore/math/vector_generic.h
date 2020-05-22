#ifndef _K_MATH_VECTOR_GENERIC_H_
#define _K_MATH_VECTOR_GENERIC_H_

#include "consts.h"

#include <math.h>
#include <stdbool.h>

#define DEFINE_VEC_PAIR_SIMPLE_OPERATION(T, NAME, OP)         \
    static inline T T##NAME(T a, T b) {                       \
        T res;                                                \
        for (int i = 0; i < sizeof(T) / sizeof(float); i++) { \
            res.v[i] = a.v[i] OP b.v[i];                      \
        }                                                     \
        return res;                                           \
    }

#define DEFINE_VEC_PAIR_DISTANCE_SQUARED(T)                   \
    static inline float T##DistSquared(T a, T b) {            \
        float res = 0.0f;                                     \
        for (int i = 0; i < sizeof(T) / sizeof(float); i++) { \
            float x = a.v[i] - b.v[i];                        \
            res += x * x;                                     \
        }                                                     \
        return res;                                           \
    }

#define DEFINE_VEC_PAIR_DISTANCE(T)         \
    static inline float T##Dist(T a, T b) { \
        return sqrt(T##DistSquared(a, b));  \
    }

#define DEFINE_VEC_PAIR_DOT(T)                                \
    static inline float T##Dot(T a, T b) {                    \
        float res = 0.0f;                                     \
        for (int i = 0; i < sizeof(T) / sizeof(float); i++) { \
            res += a.v[i] * b.v[i];                           \
        }                                                     \
        return res;                                           \
    }

#define DEFINE_VEC_PAIR_EQ(T)                   \
    static inline bool T##Eq(T a, T b) {        \
        return T##Dist(a, b) <= FloatTolerance; \
    }

#define DEFINE_VEC_LEN_SQUARED(T)                             \
    static inline float T##LenSquared(T a) {                  \
        float res = 0.0f;                                     \
        for (int i = 0; i < sizeof(T) / sizeof(float); i++) { \
            res += a.v[i] * a.v[i];                           \
        }                                                     \
        return res;                                           \
    }

#define DEFINE_VEC_LEN(T)               \
    static inline float T##Len(T a) {   \
        return sqrtf(T##LenSquared(a)); \
    }

#define DEFINE_VEC_SCALE(T)                                   \
    static inline T T##Scale(T a, float s) {                  \
        T res = T##Zero;                                      \
        for (int i = 0; i < sizeof(T) / sizeof(float); i++) { \
            res.v[i] = a.v[i] * s;                            \
        }                                                     \
        return res;                                           \
    }

#define DEFINE_VEC_NORMALIZE(T)         \
    static inline T T##Normalize(T a) { \
        float len = T##Len(a);          \
        return T##Scale(a, 1.0f / len); \
    }

#endif  // _K_MATH_VECTOR_GENERIC_H_
