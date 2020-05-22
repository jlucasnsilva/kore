#ifndef _K_UTIL_H_
#define _K_UTIL_H_

#include <stdint.h>
#include <stdbool.h>

#define Maybe(T) Maybe__##T

#define DEFINE_MAYBE(T) \
    typedef struct {    \
        T value;        \
        bool ok;        \
    } Maybe__##T

#define Short(x) ((short)(x))
#define Int(x) ((int)(x))
#define Long(x) ((long)(x))
#define Int8(x) ((int8_t)(x))
#define Int16(x) ((int16_t)(x))
#define Int32(x) ((int32_t)(x))
#define Int64(x) ((int64_t)(x))
#define UInt8(x) ((uint8_t)(x))
#define UInt16(x) ((uint16_t)(x))
#define UInt32(x) ((uint32_t)(x))
#define UInt64(x) ((uint64_t)(x))

#define Float(x) ((float)(x))
#define Double(x) ((double)(x))

#define Ptr(x) ((void *)(x))

#endif  // _K_UTIL_H_
