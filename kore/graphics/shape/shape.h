#ifndef _K_GRAPHICS_SHAPE_H_
#define _K_GRAPHICS_SHAPE_H_

#include "../../math/math.h"

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

void k_RectangleMake(k_Rectangle *restrict target,
                     k_Vec3 topLeft,
                     k_Vec3 topRight,
                     k_Vec3 bottomLeft,
                     k_Vec3 bottomRight) {
    target->top.vertices[0] = topLeft;
    target->top.vertices[1] = topRight;
    target->top.vertices[2] = bottomLeft;

    target->bottom.vertices[0] = topRight;
    target->bottom.vertices[1] = bottomRight;
    target->bottom.vertices[2] = bottomLeft;
}

void k_CubeMake(k_Cube *restrict target, k_Vec3 center, float length) {
    float half = length / 2.0f;
    k_Vec3 less = k_Vec3Add(center, k_bVec3(.x = -half, .y = -half, .z = -half));
    k_Vec3 plus = k_Vec3Add(center, k_bVec3(.x = half, .y = half, .z = half));

    k_RectangleMake(&target->top,
                    k_bVec3(.y = less.y, .z = less.z, .x = less.x),
                    k_bVec3(.y = less.y, .z = less.z, .x = plus.x),
                    k_bVec3(.y = less.y, .z = plus.z, .x = less.x),
                    k_bVec3(.y = less.y, .z = plus.z, .x = plus.x));
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
                    k_bVec3(.x = plus.x, .y = plus.z, .z = less.z),
                    k_bVec3(.x = plus.x, .y = plus.z, .z = plus.z),
                    k_bVec3(.x = plus.x, .y = less.z, .z = less.z),
                    k_bVec3(.x = plus.x, .y = less.z, .z = plus.z));
    k_RectangleMake(&target->front,
                    k_bVec3(.z = plus.z, .y = plus.y, .x = less.x),
                    k_bVec3(.z = plus.z, .y = plus.y, .x = plus.x),
                    k_bVec3(.z = plus.z, .y = less.y, .x = less.x),
                    k_bVec3(.z = plus.z, .y = less.y, .x = plus.x));
    k_RectangleMake(&target->bottom,
                    k_bVec3(.y = less.y, .z = less.z, .x = less.x),
                    k_bVec3(.y = less.y, .z = less.z, .x = plus.x),
                    k_bVec3(.y = less.y, .z = plus.z, .x = less.x),
                    k_bVec3(.y = less.y, .z = plus.z, .x = plus.x));
}

#endif  //_K_GRAPHICS_SHAPE_H_
