#ifndef _K_GRAPHICS_COLOR_H_
#define _K_GRAPHICS_COLOR_H_

#include "../math/math.h"

#include <stdint.h>

typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
} k_Color;

#define k_bColor(...) ((k_Color){.r = 0,   \
                                 .g = 0,   \
                                 .b = 0,   \
                                 .a = 255, \
                                 __VA_ARGS__})

#define k_bColorVec3Spread(...) k_Vec3Spread(k_ColorToVec3((k_Color){.r = 0,   \
                                                                     .g = 0,   \
                                                                     .b = 0,   \
                                                                     .a = 255, \
                                                                     __VA_ARGS__}))

#define k_bColorVec4Spread(...) k_Vec4Spread(k_ColorToVec4((k_Color){.r = 0,   \
                                                                     .g = 0,   \
                                                                     .b = 0,   \
                                                                     .a = 255, \
                                                                     __VA_ARGS__}))

static inline k_Vec3 k_ColorToVec3(k_Color color) {
    return k_bVec3(.x = ((float)color.r) / 255.0f,
                   .y = ((float)color.g) / 255.0f,
                   .z = ((float)color.b) / 255.0f);
}

static inline k_Vec4 k_ColorToVec4(k_Color color) {
    return k_bVec4(.x = ((float)color.r) / 255.0f,
                   .y = ((float)color.g) / 255.0f,
                   .z = ((float)color.b) / 255.0f,
                   .w = ((float)color.a) / 255.0f);
}

static inline k_Color k_ColorFromVec3(k_Vec3 color) {
    return k_bColor(.r = ((uint8_t)color.x * 255.0f),
                    .g = ((uint8_t)color.y * 255.0f),
                    .b = ((uint8_t)color.z * 255.0f));
}

static inline k_Color k_ColorFromVec4(k_Vec4 color) {
    return k_bColor(.r = ((uint8_t)color.x * 255.0f),
                    .g = ((uint8_t)color.y * 255.0f),
                    .b = ((uint8_t)color.z * 255.0f),
                    .a = ((uint8_t)color.w * 255.0f));
}

#endif  // _K_GRAPHICS_COLOR_H_
