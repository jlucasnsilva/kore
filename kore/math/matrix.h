#ifndef _K_MATH_MATRIX_H_
#define _K_MATH_MATRIX_H_

#include "vector.h"

typedef union {
    Vec4 v[4];
    float m[4][4];
} Mat4;

#define bMat4I() ((Mat4){.m = {{1.0f, 0.0f, 0.0f, 0.0f}, \
                               {0.0f, 1.0f, 0.0f, 0.0f}, \
                               {0.0f, 0.0f, 1.0f, 0.0f}, \
                               {0.0f, 0.0f, 0.0f, 1.0f}}})

#define bMat4Translation(tvec) ((Mat4){.m = {{1.0f, 0.0f, 0.0f, tvec.x}, \
                                             {0.0f, 1.0f, 0.0f, tvec.y}, \
                                             {0.0f, 0.0f, 1.0f, tvec.z}, \
                                             {0.0f, 0.0f, 0.0f, 1.0f}}})

#define bMat4UTranslation(tscalar)                   \
    ((Matscalar4){.m = {{1.0f, 0.0f, 0.0f, tscalar}, \
                        {0.0f, 1.0f, 0.0f, tscalar}, \
                        {0.0f, 0.0f, 1.0f, tscalar}, \
                        {0.0f, 0.0f, 0.0f, 1.0f}}})

#define bMat4Scaling(svec) ((Mat4){.m = {{svec.x, 0.0f, 0.0f, 0.0f}, \
                                         {0.0f, svec.y, 0.0f, 0.0f}, \
                                         {0.0f, 0.0f, svec.z, 0.0f}, \
                                         {0.0f, 0.0f, 0.0f, 1.0f}}})

#define bMat4UScaling(sscalar) ((Mat4){.m = {{sscalar, 0.0f, 0.0f, 0.0f}, \
                                             {0.0f, sscalar, 0.0f, 0.0f}, \
                                             {0.0f, 0.0f, sscalar, 0.0f}, \
                                             {0.0f, 0.0f, 0.0f, 1.0f}}})

void Mat4SetVec4(Mat4 *restrict result, Vec4 a, Vec4 b, Vec4 c);
Vec4 Mat4Vec4(const Mat4 *restrict m, Vec4 v);
void Mat4Rotation(Mat4 *restrict result, Vec3 rotation);

#endif  // _K_MATH_MATRIX_H_
