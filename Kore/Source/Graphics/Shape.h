#ifndef _K_GRAPHICS_SHAPE_H_
#define _K_GRAPHICS_SHAPE_H_

#include "../Math/Math.h"

#include <stdlib.h>

typedef struct {
    k_Vec3 Vertices[3];
} k_ShapeTriangle;

typedef struct {
    k_ShapeTriangle Top;
    k_ShapeTriangle Bottom;
} k_ShapeRectangle;

typedef struct {
    k_ShapeRectangle Top;
    k_ShapeRectangle Left;
    k_ShapeRectangle Back;
    k_ShapeRectangle Right;
    k_ShapeRectangle Front;
    k_ShapeRectangle Bottom;
} k_ShapeCube;

typedef struct {
    k_ShapeTriangle Triangles[6];
} k_ShapeHexagon;

typedef struct {
    k_ShapeHexagon Top;
    k_ShapeHexagon Bottom;
    k_ShapeRectangle Sides[6];
} k_ShapeHexagonBlock;

void k_ShapeRectangleMake(k_ShapeRectangle *restrict target,
                          k_Vec3 topLeft,
                          k_Vec3 topRight,
                          k_Vec3 bottomLeft,
                          k_Vec3 bottomRight);

// TODO make it safe
void k_ShapeRectangleUV(float *restrict uv);

void k_ShapeCubeMake(k_ShapeCube *restrict target);

// TODO make it safe
void k_ShapeCubeUV(float *restrict uv);

void k_ShapeHexagonMake(k_ShapeHexagon *restrict target);
void k_ShapeHexagonUV(float *restrict uv, size_t count);

void k_ShapeHexagonBlockMake(k_ShapeHexagonBlock *restrict target);

#ifdef DebugBuild
#include <stdio.h>
void k_ShapeCubeColor(float *restrict colors);
void k_ShapeCubePrint(const k_ShapeCube *restrict c);
void k_ShapeHexagonBlockColor(float *restrict colors);
#endif

#endif  //_K_GRAPHICS_SHAPE_H_
