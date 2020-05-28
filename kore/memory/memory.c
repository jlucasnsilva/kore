#include "../log/log.h"
#include "memory.h"

#include <stdio.h>
#include <stdlib.h>

static char* gKoreMemory = NULL;
static size_t gCapacity = 0;
static size_t gUsed = 0;

void k_InitMemory(size_t megaBytes) {
    gUsed = 0;
    gCapacity = megaBytes * 1024 * 1024;
    gKoreMemory = malloc(gCapacity);

    if (!gKoreMemory) {
        k_LogErrorf("Failed to allocate the system memory.\n");
        exit(EXIT_FAILURE);
    }
}

void* k_AllocChunk(size_t size) {
    return NULL;
}
