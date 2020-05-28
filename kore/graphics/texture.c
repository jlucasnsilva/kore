#include "texture.h"
#include "../types/types.h"

k_Texture k_TextureCreate(k_Image *restrict img) {
    k_Texture tex;

    glGenTextures(1, &tex.id);
    glBindTexture(GL_TEXTURE_2D, tex.id);
    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 GL_RGB,
                 img->Width,
                 img->Height,
                 0,
                 GL_RGB,
                 GL_UNSIGNED_BYTE,
                 img->Content);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    tex.Height = k_Int16(img->Height);
    tex.Width = k_Int16(img->Width);

    return tex;
}

void k_TextureDestroy(k_Texture *restrict tex) {
    glDeleteTextures(1, &tex->id);
    tex->Height = -1;
    tex->Width = -1;
}
