#ifndef _K_DATASTRUCTURE_UINT8_ARRAY_MAP_H_
#define _K_DATASTRUCTURE_UINT8_ARRAY_MAP_H_

#include <stdint.h>
#include <stdlib.h>

typedef struct {
    size_t count;
    size_t objSize;
    uint8_t* keys;
    void* values;
} Uint8ArrayMap;

#endif  // _K_DATASTRUCTURE_UINT8_ARRAY_MAP_H_
