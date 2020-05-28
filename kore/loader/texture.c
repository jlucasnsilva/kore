#include "texture.h"
#include "image.h"

#include <stdio.h>

k_Texture k_LoadTexture(const char *restrict path) {
    k_Image img = k_ImageLoad(path);
    k_Texture tex = {.id = 0,
                     .Width = -1,
                     .Height = -1};

    if (img.Width < 0 || img.Height < 0) {
        return tex;
    }
    tex = k_TextureCreate(&img);
    k_ImageFinalize(&img);
    return tex;
}