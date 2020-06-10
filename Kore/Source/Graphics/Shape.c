#include "Shape.h"
#include "../Types/Types.h"

void k_ShapeRectangleMake(k_ShapeRectangle *restrict target,
                          k_Vec3 topLeft,
                          k_Vec3 topRight,
                          k_Vec3 bottomLeft,
                          k_Vec3 bottomRight) {
    target->Top.Vertices[0] = topLeft;
    target->Top.Vertices[1] = bottomLeft;
    target->Top.Vertices[2] = topRight;

    target->Bottom.Vertices[0] = topRight;
    target->Bottom.Vertices[1] = bottomLeft;
    target->Bottom.Vertices[2] = bottomRight;
}

void k_ShapeRectangleUV(float *restrict uv) {
    // 0---2      /3
    // |  /     /  |
    // 1/      4---5

    // first triangle
    uv[0] = 0.0f;  // vertex 0
    uv[1] = 1.0f;
    uv[2] = 0.0f;  // vertex 1
    uv[3] = 0.0f;
    uv[4] = 1.0f;  // vertex 2
    uv[5] = 1.0f;

    // second triangle
    uv[6] = 1.0f;  // vertex 3
    uv[7] = 1.0f;
    uv[8] = 0.0f;  // vertex 4
    uv[9] = 0.0f;
    uv[10] = 1.0f;  // vertex 5
    uv[11] = 0.0f;
}

void k_ShapeCubeMake(k_ShapeCube *restrict target) {
    float half = 0.5f;
    k_Vec3 less = k_bVec3(.X = -half, .Y = -half, .Z = -half);
    k_Vec3 plus = k_bVec3(.X = half, .Y = half, .Z = half);

    k_ShapeRectangleMake(&target->Top,
                         k_bVec3(.Y = plus.Y, .Z = less.Z, .X = less.X),
                         k_bVec3(.Y = plus.Y, .Z = less.Z, .X = plus.X),
                         k_bVec3(.Y = plus.Y, .Z = plus.Z, .X = less.X),
                         k_bVec3(.Y = plus.Y, .Z = plus.Z, .X = plus.X));
    k_ShapeRectangleMake(&target->Left,
                         k_bVec3(.X = less.X, .Y = plus.Y, .Z = less.Z),
                         k_bVec3(.X = less.X, .Y = plus.Y, .Z = plus.Z),
                         k_bVec3(.X = less.X, .Y = less.Y, .Z = less.Z),
                         k_bVec3(.X = less.X, .Y = less.Y, .Z = plus.Z));
    k_ShapeRectangleMake(&target->Back,
                         k_bVec3(.Z = less.Z, .Y = plus.Y, .X = less.X),
                         k_bVec3(.Z = less.Z, .Y = plus.Y, .X = plus.X),
                         k_bVec3(.Z = less.Z, .Y = less.Y, .X = less.X),
                         k_bVec3(.Z = less.Z, .Y = less.Y, .X = plus.X));
    k_ShapeRectangleMake(&target->Right,
                         k_bVec3(.X = plus.X, .Y = plus.Y, .Z = plus.Z),
                         k_bVec3(.X = plus.X, .Y = plus.Y, .Z = less.Z),
                         k_bVec3(.X = plus.X, .Y = less.Y, .Z = plus.Z),
                         k_bVec3(.X = plus.X, .Y = less.Y, .Z = less.Z));
    k_ShapeRectangleMake(&target->Front,
                         k_bVec3(.Z = plus.Z, .Y = plus.Y, .X = less.X),
                         k_bVec3(.Z = plus.Z, .Y = plus.Y, .X = plus.X),
                         k_bVec3(.Z = plus.Z, .Y = less.Y, .X = less.X),
                         k_bVec3(.Z = plus.Z, .Y = less.Y, .X = plus.X));
    k_ShapeRectangleMake(&target->Bottom,
                         k_bVec3(.Y = less.Y, .Z = plus.Z, .X = less.X),
                         k_bVec3(.Y = less.Y, .Z = plus.Z, .X = plus.X),
                         k_bVec3(.Y = less.Y, .Z = less.Z, .X = less.X),
                         k_bVec3(.Y = less.Y, .Z = less.Z, .X = plus.X));
}

void k_ShapeCubeUV(float *restrict uv) {
    k_ShapeRectangleUV(&uv[0]);   // Top
    k_ShapeRectangleUV(&uv[12]);  // Left
    k_ShapeRectangleUV(&uv[24]);  // Back
    k_ShapeRectangleUV(&uv[36]);  // Right
    k_ShapeRectangleUV(&uv[48]);  // Front
    k_ShapeRectangleUV(&uv[60]);  // Bottom
}

void k_ShapeHexagonMake(k_ShapeHexagon *restrict target) {
    float edge = 1.0f;
    float halfDiagonal = edge;
    float halfEdge = edge / 2.0f;
    float height = (sqrtf(3.0f) / 2) * edge;

    //      0
    //   1     5
    //   2     4
    //      3
    target->Triangles[0].Vertices[0] = k_bVec3(.Z = -height, .X = halfEdge);
    target->Triangles[0].Vertices[1] = k_bVec3(.Z = -height, .X = -halfEdge);
    target->Triangles[0].Vertices[2] = k_bVec3();

    target->Triangles[1].Vertices[0] = k_bVec3(.Z = -height, .X = -halfEdge);
    target->Triangles[1].Vertices[1] = k_bVec3(.X = -halfDiagonal);
    target->Triangles[1].Vertices[2] = k_bVec3();

    target->Triangles[2].Vertices[0] = k_bVec3(.X = -halfDiagonal);
    target->Triangles[2].Vertices[1] = k_bVec3(.X = -halfEdge, .Z = height);
    target->Triangles[2].Vertices[2] = k_bVec3();

    target->Triangles[3].Vertices[0] = k_bVec3(.Z = height, .X = -halfEdge);
    target->Triangles[3].Vertices[1] = k_bVec3(.Z = height, .X = halfEdge);
    target->Triangles[3].Vertices[2] = k_bVec3();

    target->Triangles[4].Vertices[0] = k_bVec3(.X = halfEdge, .Z = height);
    target->Triangles[4].Vertices[1] = k_bVec3(.X = halfDiagonal);
    target->Triangles[4].Vertices[2] = k_bVec3();

    target->Triangles[5].Vertices[0] = k_bVec3(.Z = -height, .X = halfEdge);
    target->Triangles[5].Vertices[1] = k_bVec3(.X = halfDiagonal);
    target->Triangles[5].Vertices[2] = k_bVec3();
}

void k_ShapeHexagonUV(float *restrict uv, size_t count) {
    k_ShapeHexagon hexagon;

    k_ShapeHexagonMake(&hexagon);

    const size_t hexagonSize = sizeof(hexagon) / sizeof(float);
    const size_t vertexCount = hexagonSize / 3;
    const size_t uvCount = 2 * vertexCount;
    const float *hexArray = k_Ptr(&hexagon);
    const float minZ = hexagon.Triangles[0].Vertices[0].Z;
    const float maxZ = hexagon.Triangles[3].Vertices[0].Z;
    const float minX = hexagon.Triangles[1].Vertices[1].X;
    const float maxX = hexagon.Triangles[4].Vertices[1].X;
    const float w = maxX - minX;
    const float h = maxZ - minZ;

    // TODO assert uv length is even

    //        0
    //      -----
    //   1 /     \ 5
    //   2 \     / 4
    //      -----
    //        3
    int i = 0;
    int j = 0;
    for (i = 0, j = 0;
         i < uvCount && i < count && j < hexagonSize;
         i += 2, j += 3) {
        uv[i + 0] = (hexArray[j + 0] + w / 2) / w;      // +0 = x component
        uv[i + 1] = 1 - (hexArray[j + 2] + h / 2) / h;  // +2 = z component
        printf("  %2d | [%2d:%-2d] (%f, %f, %f) -> (%f, %f)\n",
               (i + 1) / 2,
               i,
               i + 1,
               hexArray[j + 0],
               hexArray[j + 1],
               hexArray[j + 2],
               uv[i + 0],
               uv[i + 1]);
    }
}

void k_ShapeHexagonBlockMake(k_ShapeHexagonBlock *restrict target) {
    k_ShapeHexagon *Top = &target->Top;
    k_ShapeHexagon *Bottom = &target->Bottom;

    k_ShapeHexagonMake(&target->Top);
    k_ShapeHexagonMake(&target->Bottom);
    for (int i = 0; i < 6; i++) {
        Top->Triangles[i].Vertices[0].Y = 0.5f;
        Top->Triangles[i].Vertices[1].Y = 0.5f;
        Top->Triangles[i].Vertices[2].Y = 0.5f;

        Bottom->Triangles[i].Vertices[0].Y = -0.5f;
        Bottom->Triangles[i].Vertices[1].Y = -0.5f;
        Bottom->Triangles[i].Vertices[2].Y = -0.5f;
    }

    for (int i = 0; i < 6; i++) {
        k_ShapeRectangleMake(&target->Sides[i],
                             Top->Triangles[i].Vertices[0],
                             Top->Triangles[i].Vertices[1],
                             Bottom->Triangles[i].Vertices[0],
                             Bottom->Triangles[i].Vertices[1]);
    }
}

#ifdef DebugBuild
#include <stdio.h>

void k_ShapeCubeColor(float *restrict colors) {
    float cs[] = {
        0.8,
        0.2,
        0.2,
        ///////
        0.2,
        0.8,
        0.2,
        ///////
        0.2,
        0.2,
        0.8,
        ///////
        0.2,
        0.2,
        0.2,
        ///////
        0.6,
        0.6,
        0.6,
        ///////
        0.9,
        0.9,
        0.9,
    };

    for (int i = 0; i < 6; i++) {
        colors[i * 18 + 0] = cs[i * 3 + 0];
        colors[i * 18 + 1] = cs[i * 3 + 1];
        colors[i * 18 + 2] = cs[i * 3 + 2];

        colors[i * 18 + 3] = cs[i * 3 + 0];
        colors[i * 18 + 4] = cs[i * 3 + 1];
        colors[i * 18 + 5] = cs[i * 3 + 2];

        colors[i * 18 + 6] = cs[i * 3 + 0];
        colors[i * 18 + 7] = cs[i * 3 + 1];
        colors[i * 18 + 8] = cs[i * 3 + 2];

        colors[i * 18 + 9] = cs[i * 3 + 0];
        colors[i * 18 + 10] = cs[i * 3 + 1];
        colors[i * 18 + 11] = cs[i * 3 + 2];

        colors[i * 18 + 12] = cs[i * 3 + 0];
        colors[i * 18 + 13] = cs[i * 3 + 1];
        colors[i * 18 + 14] = cs[i * 3 + 2];

        colors[i * 18 + 15] = cs[i * 3 + 0];
        colors[i * 18 + 16] = cs[i * 3 + 1];
        colors[i * 18 + 17] = cs[i * 3 + 2];
    }
}

void k_ShapeCubePrint(const k_ShapeCube *restrict c) {
    float *a = (void *)c;
    int b = 0;
    for (int i = 0; i < sizeof(k_ShapeCube) / sizeof(float); i++) {
        printf("%.2f\t", a[i]);
        if (b == 2) {
            putchar('\n');
            b = 0;
        } else {
            b++;
        }
    }
    putchar('\n');
}

void k_ShapeHexagonBlockColor(float *restrict colors) {
    float cs[] = {
        // TOP ///////////////////////////////
        0.8,
        0.2,
        0.2,
        // SIDES /////////////////////////////
        0.2,
        0.8,
        0.2,
        // BOTTOM ////////////////////////////
        0.2,
        0.2,
        0.8,
    };

    int i = 0;
    int start = 0;
    size_t hs = sizeof(k_ShapeHexagon) / sizeof(float);
    size_t hbs = sizeof(k_ShapeHexagonBlock) / sizeof(float);

    // TOP
    for (i = start; i < (start + hs); i += 3) {
        float sub = i % 2 == 0 ? 0.4f : 0.0f;
        colors[i + 0] = cs[0] - sub;
        colors[i + 1] = cs[1] - sub;
        colors[i + 2] = cs[2] - sub;
    }

    // BOTTOM
    start += hs;
    for (i = start; i < (start + hs); i += 3) {
        float sub = i % 2 == 0 ? 0.4f : 0.0f;
        for (int j = 0; j < 3; j++) {
            colors[i + 0] = cs[3] - sub;
            colors[i + 1] = cs[4] - sub;
            colors[i + 2] = cs[5] - sub;
        }
    }

    start += hs;
    for (i = start; i < hbs; i += 3) {
        float sub = i % 2 == 0 ? 0.4f : 0.0f;
        colors[i + 0] = cs[6] - sub;
        colors[i + 1] = cs[7] - sub;
        colors[i + 2] = cs[8] - sub;
    }
}

#endif
