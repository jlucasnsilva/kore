#ifndef _K_MATH_ANGLE_H_
#define _K_MATH_ANGLE_H_

#include "consts.h"

static inline float k_DegreeToRad(float angle) {
    return 2 * PI * (angle / 360);
}

#endif  // _K_MATH_ANGLE_H_
