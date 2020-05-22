#include "../log/log.h"
#include "memory.h"

#include <stdio.h>
#include <stdlib.h>

static char* koreMemory = NULL;
static size_t capacity = 0;
static size_t used = 0;

void k_InitMemory(size_t megaBytes) {
    used = 0;
    capacity = megaBytes * 1024 * 1024;
    koreMemory = malloc(capacity);

    if (!koreMemory) {
        k_LogErrorf("Failed to allocate the system memory.\n");
        exit(EXIT_FAILURE);
    }
}

void* k_AllocChunk(size_t size) {
    return NULL;
}
