#ifndef _K_UTIL_H_
#define _K_UTIL_H_

#include <stdint.h>
#include <stdbool.h>

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

#endif  // _K_UTIL_H_
