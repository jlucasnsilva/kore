#ifndef _K_TYPES_TYPES_H_
#define _K_TYPES_TYPES_H_

#include <GL/glew.h>
#include <GL/gl.h>

#include <stdint.h>
#include <stdbool.h>

#ifdef WindowsBuild
#else
typedef char k_Char;
#endif

typedef uint32_t k_Rune;

#define k_Maybe(T) Maybe__##T

#define K_DEFINE_MAYBE(T) \
    typedef struct {      \
        T value;          \
        bool ok;          \
    } Maybe__##T

#define k_Short(x) ((short)(x))
#define k_Int(x) ((int)(x))
#define k_Long(x) ((long)(x))
#define k_Int8(x) ((int8_t)(x))
#define k_Int16(x) ((int16_t)(x))
#define k_Int32(x) ((int32_t)(x))
#define k_Int64(x) ((int64_t)(x))
#define k_UInt8(x) ((uint8_t)(x))
#define k_UInt16(x) ((uint16_t)(x))
#define k_UInt32(x) ((uint32_t)(x))
#define k_UInt64(x) ((uint64_t)(x))

#define k_Float(x) ((float)(x))
#define k_Double(x) ((double)(x))

#define k_Ptr(x) ((void *)(x))

K_DEFINE_MAYBE(char);

K_DEFINE_MAYBE(GLuint);

#endif  // _K_TYPES_TYPES_H_
