#ifndef _K_GRAPHICS_SHAPE_H_
#define _K_GRAPHICS_SHAPE_H_

#include "../math/math.h"

typedef struct {
    k_Vec3 vertices[3];
} k_Triangle;

typedef struct {
    k_Triangle top;
    k_Triangle bottom;
} k_Rectangle;

typedef struct {
    k_Rectangle top;
    k_Rectangle left;
    k_Rectangle back;
    k_Rectangle right;
    k_Rectangle front;
    k_Rectangle bottom;
} k_Cube;

typedef struct {
    k_Triangle triangles[6];
} k_Hexagon;

typedef struct {
    k_Hexagon top;
    k_Hexagon bottom;
    k_Rectangle sides[6];
} k_HexagonBlock;

static inline void k_RectangleMake(k_Rectangle *restrict target,
                                   k_Vec3 topLeft,
                                   k_Vec3 topRight,
                                   k_Vec3 bottomLeft,
                                   k_Vec3 bottomRight) {
    target->top.vertices[0] = topLeft;
    target->top.vertices[1] = bottomLeft;
    target->top.vertices[2] = topRight;

    target->bottom.vertices[0] = topRight;
    target->bottom.vertices[1] = bottomLeft;
    target->bottom.vertices[2] = bottomRight;
}

static inline void k_CubeMake(k_Cube *restrict target, k_Vec3 center, float length) {
    float half = length / 2.0f;
    k_Vec3 less = k_Vec3Add(center, k_bVec3(.x = -half, .y = -half, .z = -half));
    k_Vec3 plus = k_Vec3Add(center, k_bVec3(.x = half, .y = half, .z = half));

    k_RectangleMake(&target->top,
                    k_bVec3(.y = plus.y, .z = less.z, .x = less.x),
                    k_bVec3(.y = plus.y, .z = less.z, .x = plus.x),
                    k_bVec3(.y = plus.y, .z = plus.z, .x = less.x),
                    k_bVec3(.y = plus.y, .z = plus.z, .x = plus.x));
    k_RectangleMake(&target->left,
                    k_bVec3(.x = less.x, .y = plus.y, .z = less.z),
                    k_bVec3(.x = less.x, .y = plus.y, .z = plus.z),
                    k_bVec3(.x = less.x, .y = less.y, .z = less.z),
                    k_bVec3(.x = less.x, .y = less.y, .z = plus.z));
    k_RectangleMake(&target->back,
                    k_bVec3(.z = less.z, .y = plus.y, .x = less.x),
                    k_bVec3(.z = less.z, .y = plus.y, .x = plus.x),
                    k_bVec3(.z = less.z, .y = less.y, .x = less.x),
                    k_bVec3(.z = less.z, .y = less.y, .x = plus.x));
    k_RectangleMake(&target->right,
                    k_bVec3(.x = plus.x, .y = plus.y, .z = plus.z),
                    k_bVec3(.x = plus.x, .y = plus.y, .z = less.z),
                    k_bVec3(.x = plus.x, .y = less.y, .z = plus.z),
                    k_bVec3(.x = plus.x, .y = less.y, .z = less.z));
    k_RectangleMake(&target->front,
                    k_bVec3(.z = plus.z, .y = plus.y, .x = less.x),
                    k_bVec3(.z = plus.z, .y = plus.y, .x = plus.x),
                    k_bVec3(.z = plus.z, .y = less.y, .x = less.x),
                    k_bVec3(.z = plus.z, .y = less.y, .x = plus.x));
    k_RectangleMake(&target->bottom,
                    k_bVec3(.y = less.y, .z = plus.z, .x = less.x),
                    k_bVec3(.y = less.y, .z = plus.z, .x = plus.x),
                    k_bVec3(.y = less.y, .z = less.z, .x = less.x),
                    k_bVec3(.y = less.y, .z = less.z, .x = plus.x));
}

static inline void k_HexagonMake(k_Hexagon *restrict target) {
    float edge = 1.0f;
    float halfDiagonal = edge;
    float halfEdge = edge / 2.0f;
    float height = (sqrtf(3.0f) / 2) * edge;

    //      0
    //   1     5
    //   2     4
    //      3
    target->triangles[0].vertices[0] = k_bVec3(.z = -height, .x = halfEdge);
    target->triangles[0].vertices[1] = k_bVec3(.z = -height, .x = -halfEdge);
    target->triangles[0].vertices[2] = k_bVec3();

    target->triangles[1].vertices[0] = k_bVec3(.z = -height, .x = -halfEdge);
    target->triangles[1].vertices[1] = k_bVec3(.x = -halfDiagonal);
    target->triangles[1].vertices[2] = k_bVec3();

    target->triangles[2].vertices[0] = k_bVec3(.x = -halfDiagonal);
    target->triangles[2].vertices[1] = k_bVec3(.x = -halfEdge, .z = height);
    target->triangles[2].vertices[2] = k_bVec3();

    target->triangles[3].vertices[0] = k_bVec3(.z = height, .x = -halfEdge);
    target->triangles[3].vertices[1] = k_bVec3(.z = height, .x = halfEdge);
    target->triangles[3].vertices[2] = k_bVec3();

    target->triangles[4].vertices[0] = k_bVec3(.x = halfEdge, .z = height);
    target->triangles[4].vertices[1] = k_bVec3(.x = halfDiagonal);
    target->triangles[4].vertices[2] = k_bVec3();

    target->triangles[5].vertices[0] = k_bVec3(.z = -height, .x = halfEdge);
    target->triangles[5].vertices[1] = k_bVec3(.x = halfDiagonal);
    target->triangles[5].vertices[2] = k_bVec3();
}

static inline void k_HexagonBlockMake(k_HexagonBlock *restrict target) {
    k_Hexagon *top = &target->top;
    k_Hexagon *bottom = &target->bottom;

    k_HexagonMake(&target->top);
    k_HexagonMake(&target->bottom);
    for (int i = 0; i < 6; i++) {
        top->triangles[i].vertices[0].y = 0.5f;
        top->triangles[i].vertices[1].y = 0.5f;
        top->triangles[i].vertices[2].y = 0.5f;

        bottom->triangles[i].vertices[0].y = -0.5f;
        bottom->triangles[i].vertices[1].y = -0.5f;
        bottom->triangles[i].vertices[2].y = -0.5f;
    }

    for (int i = 0; i < 6; i++) {
        k_RectangleMake(&target->sides[i],
                        top->triangles[i].vertices[0],
                        top->triangles[i].vertices[1],
                        bottom->triangles[i].vertices[0],
                        bottom->triangles[i].vertices[1]);
    }
}

#ifdef DebugBuild
#include <stdio.h>

static inline void k_CubeColor(float *restrict colors) {
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

static inline void k_CubePrint(const k_Cube *restrict c) {
    float *a = (void *)c;
    int b = 0;
    for (int i = 0; i < sizeof(k_Cube) / sizeof(float); i++) {
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

static inline void k_HexagonBlockColor(float *restrict colors) {
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
    size_t hs = sizeof(k_Hexagon) / sizeof(float);
    size_t hbs = sizeof(k_HexagonBlock) / sizeof(float);

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

#endif  //_K_GRAPHICS_SHAPE_H_
