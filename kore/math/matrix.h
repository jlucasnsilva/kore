#ifndef _K_MATH_MATRIX_H_
#define _K_MATH_MATRIX_H_

#include "vector.h"

typedef union {
    k_Vec4 v[4];
    float m[4][4];
} k_Mat4;

#define k_bMat4I() ((k_Mat4){.m = {{1.0f, 0.0f, 0.0f, 0.0f}, \
                                   {0.0f, 1.0f, 0.0f, 0.0f}, \
                                   {0.0f, 0.0f, 1.0f, 0.0f}, \
                                   {0.0f, 0.0f, 0.0f, 1.0f}}})

#define k_bMat4Translation(tvec) ((k_Mat4){.m = {{1.0f, 0.0f, 0.0f, tvec.x}, \
                                                 {0.0f, 1.0f, 0.0f, tvec.y}, \
                                                 {0.0f, 0.0f, 1.0f, tvec.z}, \
                                                 {0.0f, 0.0f, 0.0f, 1.0f}}})

#define k_bMat4UTranslation(tscalar)                 \
    ((Matscalar4){.m = {{1.0f, 0.0f, 0.0f, tscalar}, \
                        {0.0f, 1.0f, 0.0f, tscalar}, \
                        {0.0f, 0.0f, 1.0f, tscalar}, \
                        {0.0f, 0.0f, 0.0f, 1.0f}}})

#define k_bMat4Scaling(svec) ((k_Mat4){.m = {{svec.x, 0.0f, 0.0f, 0.0f}, \
                                             {0.0f, svec.y, 0.0f, 0.0f}, \
                                             {0.0f, 0.0f, svec.z, 0.0f}, \
                                             {0.0f, 0.0f, 0.0f, 1.0f}}})

#define k_bMat4UScaling(sscalar) ((k_Mat4){.m = {{sscalar, 0.0f, 0.0f, 0.0f}, \
                                                 {0.0f, sscalar, 0.0f, 0.0f}, \
                                                 {0.0f, 0.0f, sscalar, 0.0f}, \
                                                 {0.0f, 0.0f, 0.0f, 1.0f}}})

void k_Mat4SetVec4(k_Mat4 *restrict result, k_Vec4 a, k_Vec4 b, k_Vec4 c);
k_Vec4 k_Mat4Vec4(const k_Mat4 *restrict m, k_Vec4 v);
void k_Mat4Rotation(k_Mat4 *restrict result, k_Vec3 rotation);

#endif  // _K_MATH_MATRIX_H_
