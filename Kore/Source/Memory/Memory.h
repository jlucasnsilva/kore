#ifndef _K_MEMORY_MEMORY_H_
#define _K_MEMORY_MEMORY_H_

#include "../Types/Types.h"

#include <stdlib.h>

#define k_Delete(obj) \
    {                 \
        free(obj);    \
        obj = NULL;   \
    }

#define k_New(T, n) ((T*)calloc(n, sizeof(T)))

void k_InitMemory(size_t size);

void* k_AllocChunk(size_t size);

#endif  // _K_MEMORY_MEMORY_H_
