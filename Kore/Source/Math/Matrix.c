#include "Matrix.h"

#include <math.h>

void k_Mat4Add(k_Mat4 *restrict result, const k_Mat4 *restrict a) {
    for (int i = 0; i < 4; i++) {
        result->V[i] = k_Vec4Add(a->V[i], result->V[i]);
    }
}

void k_Mat4Mul(k_Mat4 *restrict result,
               const k_Mat4 *restrict a,
               const k_Mat4 *restrict b) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            k_Vec4 col = k_bVec4(.X = b->M[0][j],
                                 .Y = b->M[1][j],
                                 .Z = b->M[2][j],
                                 .W = b->M[3][j]);
            result->M[i][j] = k_Vec4Dot(a->V[i], col);
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
            result->M[i][j] = m->M[i][j] * s;
        }
    }
}

void k_Mat4XRotation(k_Mat4 *restrict result, float yaw) {
    float angle = k_DegreeToRad(yaw);
    float cosa = cosf(angle);
    float sina = sinf(angle);
    *result = k_bMat4I();

    result->M[0][0] = 1.0f;
    result->M[1][1] = cosa;
    result->M[1][2] = sina;
    result->M[2][1] = -sina;
    result->M[2][2] = cosa;

    result->M[3][3] = 1.0f;
}

void k_Mat4YRotation(k_Mat4 *restrict result, float pitch) {
    float angle = k_DegreeToRad(pitch);
    float cosa = cosf(angle);
    float sina = sinf(angle);
    *result = k_bMat4I();

    result->M[1][1] = 1.0f;
    result->M[0][0] = cosa;
    result->M[0][2] = -sina;
    result->M[2][0] = sina;
    result->M[2][2] = cosa;

    result->M[3][3] = 1.0f;
}

void k_Mat4ZRotation(k_Mat4 *restrict result, float roll) {
    float angle = k_DegreeToRad(roll);
    float cosa = cosf(angle);
    float sina = sinf(angle);
    *result = k_bMat4I();

    result->M[2][2] = 1.0f;
    result->M[0][0] = cosa;
    result->M[0][1] = sina;
    result->M[1][0] = -sina;
    result->M[1][1] = cosa;

    result->M[3][3] = 1.0f;
}

void k_Mat4Rotation(k_Mat4 *restrict result, k_Vec3 rotation) {
    k_Mat4 aux1;
    k_Mat4 aux2;
    k_Mat4 aux3;

    k_Mat4XRotation(&aux2, rotation.X);
    k_Mat4YRotation(&aux3, rotation.Y);
    k_Mat4Mul(&aux1, &aux2, &aux3);

    k_Mat4ZRotation(&aux2, rotation.Z);
    k_Mat4Mul(result, &aux1, &aux2);
}

void k_Mat4Translation(k_Mat4 *restrict result, k_Vec3 delta) {
    *result = k_bMat4I();
    result->M[3][0] = delta.X;
    result->M[3][1] = delta.Y;
    result->M[3][2] = delta.Z;
}

void k_Mat4Scaling(k_Mat4 *restrict result, k_Vec3 delta) {
    *result = k_bMat4I();
    result->M[0][0] = delta.X;
    result->M[1][1] = delta.Y;
    result->M[2][2] = delta.Z;
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

    result->M[0][0] = side.X;
    result->M[1][0] = side.Y;
    result->M[2][0] = side.Z;
    result->M[0][1] = u.X;
    result->M[1][1] = u.Y;
    result->M[2][1] = u.Z;
    result->M[0][2] = -f.X;
    result->M[1][2] = -f.Y;
    result->M[2][2] = -f.Z;
    result->M[3][0] = -k_Vec3Dot(side, cameraPosition);
    result->M[3][1] = -k_Vec3Dot(u, cameraPosition);
    result->M[3][2] = k_Vec3Dot(f, cameraPosition);
}

void k_Mat4Perspective(k_Mat4 *restrict result,
                       float angleOfView,
                       float aspectRatio,
                       float near,
                       float far) {
    float rad = k_DegreeToRad(angleOfView);
    float f = tanf(rad / 2.0f);

    *result = k_bMat4();
    result->M[0][0] = 1.0f / (aspectRatio * f);
    result->M[1][1] = 1.0f / f;
    result->M[2][2] = -(far + near) / (far - near);
    result->M[2][3] = -1.0f;
    result->M[3][2] = -(2.0f * far * near) / (far - near);
}

#ifdef DebugBuild
#include <stdio.h>
void k_Mat4Print(const k_Mat4 *restrict m) {
    puts("\n");
    for (int i = 0; i < 4; i++) {
        printf("| %-5.2f %-5.2f %5.2f %5.2f |\n", m->M[i][0], m->M[i][1], m->M[i][2], m->M[i][3]);
    }
    puts("\n");
}
#endif
