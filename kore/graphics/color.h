#ifndef _K_GRAPHICS_COLOR_H_
#define _K_GRAPHICS_COLOR_H_

#include "../math/math.h"

#include <stdint.h>

typedef struct {
    uint8_t R;
    uint8_t G;
    uint8_t B;
    uint8_t A;
} k_Color;

#define k_bColor(...) ((k_Color){.R = 0,   \
                                 .G = 0,   \
                                 .B = 0,   \
                                 .A = 255, \
                                 __VA_ARGS__})

#define k_bColorVec3Spread(...) k_Vec3Spread(k_ColorToVec3((k_Color){.R = 0,   \
                                                                     .G = 0,   \
                                                                     .B = 0,   \
                                                                     .A = 255, \
                                                                     __VA_ARGS__}))

#define k_bColorVec4Spread(...) k_Vec4Spread(k_ColorToVec4((k_Color){.R = 0,   \
                                                                     .G = 0,   \
                                                                     .B = 0,   \
                                                                     .A = 255, \
                                                                     __VA_ARGS__}))

static inline k_Vec3 k_ColorToVec3(k_Color color) {
    return k_bVec3(.X = ((float)color.R) / 255.0f,
                   .Y = ((float)color.G) / 255.0f,
                   .Z = ((float)color.B) / 255.0f);
}

static inline k_Vec4 k_ColorToVec4(k_Color color) {
    return k_bVec4(.X = ((float)color.R) / 255.0f,
                   .Y = ((float)color.G) / 255.0f,
                   .Z = ((float)color.B) / 255.0f,
                   .W = ((float)color.A) / 255.0f);
}

static inline k_Color k_ColorFromVec3(k_Vec3 color) {
    return k_bColor(.R = ((uint8_t)color.X * 255.0f),
                    .G = ((uint8_t)color.Y * 255.0f),
                    .B = ((uint8_t)color.Z * 255.0f));
}

static inline k_Color k_ColorFromVec4(k_Vec4 color) {
    return k_bColor(.R = ((uint8_t)color.X * 255.0f),
                    .G = ((uint8_t)color.Y * 255.0f),
                    .B = ((uint8_t)color.Z * 255.0f),
                    .A = ((uint8_t)color.W * 255.0f));
}

#endif  // _K_GRAPHICS_COLOR_H_
