#include "matrix.h"

#include <math.h>

void k_Mat4Add(k_Mat4 *restrict result, const k_Mat4 *restrict a) {
    for (int i = 0; i < 4; i++) {
        result->v[i] = k_Vec4Add(a->v[i], result->v[i]);
    }
}

void k_Mat4Mul(k_Mat4 *restrict result,
               const k_Mat4 *restrict a,
               const k_Mat4 *restrict b) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            k_Vec4 col = k_bVec4(.x = b->m[0][j],
                                 .y = b->m[1][j],
                                 .z = b->m[2][j],
                                 .w = b->m[3][j]);
            result->m[i][j] = k_Vec4Dot(a->v[i], col);
        }
    }
}

void k_Mat4Mul3(k_Mat4 *restrict result,
                const k_Mat4 *restrict m,
                const k_Mat4 *restrict v,
                const k_Mat4 *restrict p) {
    k_Mat4 aux = k_bMat4();
    k_Mat4Mul(&aux, v, p);
    k_Mat4Mul(result, m, &aux);
}

void k_Mat4MulScalar(k_Mat4 *restrict result, k_Mat4 *restrict m, float s) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            result->m[i][j] = m->m[i][j] * s;
        }
    }
}

void k_Mat4XRotation(k_Mat4 *restrict result, float yaw) {
    float angle = k_DegreeToRad(yaw);
    float cosa = cosf(angle);
    float sina = sinf(angle);
    *result = k_bMat4I();

    result->m[0][0] = 1.0f;
    result->m[1][1] = cosa;
    result->m[1][2] = -sina;
    result->m[2][1] = sina;
    result->m[2][2] = cosa;

    result->m[3][3] = 1.0f;
}

void k_Mat4YRotation(k_Mat4 *restrict result, float pitch) {
    float angle = k_DegreeToRad(pitch);
    float cosa = cosf(angle);
    float sina = sinf(angle);
    *result = k_bMat4I();

    result->m[1][1] = 1.0f;
    result->m[0][0] = cosa;
    result->m[0][2] = sina;
    result->m[2][0] = -sina;
    result->m[2][2] = cosa;

    result->m[3][3] = 1.0f;
}

void k_Mat4ZRotation(k_Mat4 *restrict result, float roll) {
    float angle = k_DegreeToRad(roll);
    float cosa = cosf(angle);
    float sina = sinf(angle);
    *result = k_bMat4I();

    result->m[2][2] = 1.0f;
    result->m[0][0] = cosa;
    result->m[0][1] = -sina;
    result->m[1][0] = sina;
    result->m[1][1] = cosa;

    result->m[3][3] = 1.0f;
}

void k_Mat4Rotation(k_Mat4 *restrict result, k_Vec3 rotation) {
    k_Mat4 aux1;
    k_Mat4 aux2;
    k_Mat4 aux3;

    k_Mat4XRotation(&aux2, rotation.x);
    k_Mat4YRotation(&aux3, rotation.y);
    k_Mat4Mul(&aux1, &aux2, &aux3);

    k_Mat4ZRotation(&aux2, rotation.z);
    k_Mat4Mul(result, &aux1, &aux2);
}

void k_Mat4Translation(k_Mat4 *restrict result, k_Vec3 delta) {
    *result = k_bMat4I();
    result->m[3][0] = delta.x;
    result->m[3][1] = delta.y;
    result->m[3][2] = delta.z;
}

void k_Mat4Scaling(k_Mat4 *restrict result, k_Vec3 delta) {
    *result = k_bMat4I();
    result->m[0][0] = delta.x;
    result->m[1][1] = delta.y;
    result->m[2][2] = delta.z;
}

void k_Mat4LookAt(k_Mat4 *restrict result,
                  k_Vec3 cameraPosition,
                  k_Vec3 target,
                  k_Vec3 up) {
    k_Vec3 f = k_Vec3Normalize(k_Vec3Sub(target, cameraPosition));
    k_Vec3 nup = k_Vec3Normalize(up);
    k_Vec3 side = k_Vec3Normalize(k_Vec3Cross(f, nup));
    k_Vec3 u = k_Vec3Cross(side, f);
    *result = k_bMat4I();

    result->m[0][0] = side.x;
    result->m[1][0] = side.y;
    result->m[2][0] = side.z;
    result->m[0][1] = u.x;
    result->m[1][1] = u.y;
    result->m[2][1] = u.z;
    result->m[0][2] = -f.x;
    result->m[1][2] = -f.y;
    result->m[2][2] = -f.z;
    result->m[3][0] = -k_Vec3Dot(side, cameraPosition);
    result->m[3][1] = -k_Vec3Dot(u, cameraPosition);
    result->m[3][2] = k_Vec3Dot(f, cameraPosition);
}

void k_Mat4Perspective(k_Mat4 *restrict result,
                       float angleOfView,
                       float aspectRatio,
                       float near,
                       float far) {
    float rad = k_DegreeToRad(angleOfView);
    float f = tanf(rad / 2.0f);

    *result = k_bMat4();
    result->m[0][0] = 1.0f / (aspectRatio * f);
    result->m[1][1] = 1.0f / f;
    result->m[2][2] = -(far + near) / (far - near);
    result->m[2][3] = -1.0f;
    result->m[3][2] = -(2.0f * far * near) / (far - near);
}

#ifdef DebugBuild
#include <stdio.h>
void k_Mat4Print(const k_Mat4 *restrict m) {
    puts("\n");
    for (int i = 0; i < 4; i++) {
        printf("| %-5.2f %-5.2f %5.2f %5.2f |\n", m->m[i][0], m->m[i][1], m->m[i][2], m->m[i][3]);
    }
    puts("\n");
}
#endif
