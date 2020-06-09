#ifndef _K_GRAPHICS_TEXTURE_H_
#define _K_GRAPHICS_TEXTURE_H_

#include "Image.h"
#include "Image.h"

#include <stdint.h>

#ifdef LinuxBuild
#include <GL/glew.h>
#include <GL/gl.h>

typedef struct {
    GLuint id;
    int16_t Width;
    int16_t Height;
} k_Texture;
#endif  // LinuxBuild

k_Texture k_TextureCreate(k_Image *restrict img);
void k_TextureDestroy(k_Texture *restrict tex);

#endif  // _K_GRAPHICS_TEXTURE_H_
