#define STBI_ONLY_PNG
#define STBI_WINDOWS_UTF8
#define STB_IMAGE_IMPLEMENTATION
#include "../third-party/stb/stb_image.h"

int stbi_convert_wchar_to_utf8(char* buffer, size_t bufferlen, const wchar_t* input);
unsigned char* data = stbi_load(filename, &x, &y, &n, 0)