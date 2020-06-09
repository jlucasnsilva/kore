#ifndef _K_GRAPHICS_SHADER_H_
#define _K_GRAPHICS_SHADER_H_

#include <GL/glew.h>
#include <GL/gl.h>

typedef enum {
    k_ShaderTypeNone,
    k_ShaderTypeVertex,
    k_ShaderTypeFragment,
} k_ShaderType;

#ifdef LinuxBuild
typedef GLuint k_ShaderProgram;
#endif

const char* k_ShaderNameType(k_ShaderType type);

#endif  // _K_GRAPHICS_SHADER_H_
