#ifndef _K_GRAPHICS_IMAGE_H_
#define _K_GRAPHICS_IMAGE_H_

#include "../memory/memory.h"

typedef struct {
    unsigned char *Content;
    int Components;
    int Height;
    int Width;
} k_Image;

static inline void k_ImageFinalize(k_Image *restrict img) {
    k_Delete(img->Content);
    img->Components = -1;
    img->Height = -1;
    img->Width = -1;
}

#endif  // _K_GRAPHICS_IMAGE_H_
