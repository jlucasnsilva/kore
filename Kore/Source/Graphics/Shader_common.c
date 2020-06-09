#include "Shader.h"

static const char* shaderTypeNames[] = {
    [k_ShaderTypeNone] = "none",
    [k_ShaderTypeVertex] = "vertext",
    [k_ShaderTypeFragment] = "framgment",
};

const char* k_ShaderNameType(k_ShaderType type) {
    return shaderTypeNames[type];
}
