#include "Shader.h"

#define STBI_ONLY_PNG
#define STB_IMAGE_IMPLEMENTATION
#include "../../ThirdParty/stb/stb_image.h"

// WindowsBuild just in case
// #define STBI_WINDOWS_UTF8
// int stbi_convert_wchar_to_utf8(char* buffer, size_t bufferlen, const wchar_t* input);

k_Image k_ImageLoad(const char *restrict path) {
    k_Image img;
    img.Content = stbi_load(path,
                            &img.Width,
                            &img.Height,
                            &img.Components,
                            3);

    return img;
}
