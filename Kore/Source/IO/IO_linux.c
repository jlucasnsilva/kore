#ifdef LinuxBuild
#include "IO.h"

#include <stdint.h>
#include <stdlib.h>

#include <SDL2/SDL.h>

// ========================================================
//
// Implementation
//
// ========================================================

k_IOFileContent k_IOReadFile(const char* restrict path) {
    k_IOFileContent ret = {.Input = NULL, .Length = -1, .FileSize = -1};
    SDL_RWops* in = SDL_RWFromFile(path, "rb");
    if (!in) {
        return ret;
    }

    int64_t size = SDL_RWsize(in);
    if (size < 0) {
        return ret;
    }

    ret.Input = malloc(size);
    if (!ret.Input) {
        return ret;
    }

    SDL_RWread(in, ret.Input, size, 1);
    ret.FileSize = size;
    ret.Length = size;
    SDL_RWclose(in);
    return ret;
}

void k_IOReadFileInto(const char* restrict path,
                      k_IOFileContent* restrict into,
                      size_t capacity) {
    *into = (k_IOFileContent){.Input = NULL, .Length = -1, .FileSize = -1};

    SDL_RWops* in = SDL_RWFromFile(path, "rb");
    if (!in) {
        return;
    }

    int64_t size = SDL_RWsize(in);
    if (size < 0) {
        return;
    }

    SDL_RWread(in, into->Input, capacity, 1);
    into->FileSize = size;
    into->Length = capacity;
    SDL_RWclose(in);
    return;
}

k_IOFileContent k_IOReadStringFile(const char* restrict path) {
    k_IOFileContent ret = {.Input = NULL, .Length = -1, .FileSize = -1};
    SDL_RWops* in = SDL_RWFromFile(path, "r");
    if (!in) {
        return ret;
    }

    int64_t size = SDL_RWsize(in);
    if (size < 0) {
        return ret;
    }

    size_t cap = size + 1;
    ret.Input = malloc(cap);
    if (!ret.Input) {
        return ret;
    }

    SDL_RWread(in, ret.Input, size, 1);
    ret.Input[size] = '\0';
    ret.FileSize = cap;
    ret.Length = cap;
    SDL_RWclose(in);
    return ret;
}

void k_IOReadStringFileInto(const char* restrict path,
                            k_IOFileContent* restrict into,
                            size_t capacity) {
    *into = (k_IOFileContent){.Input = NULL, .Length = -1, .FileSize = -1};

    SDL_RWops* in = SDL_RWFromFile(path, "rb");
    if (!in) {
        return;
    }

    int64_t size = SDL_RWsize(in);
    if (size < 0) {
        return;
    }

    SDL_RWread(in, into->Input, capacity - 1, 1);
    into->Input[capacity > size ? size : capacity] = '\0';
    into->Length = capacity;
    into->FileSize = size;
    SDL_RWclose(in);
    return;
}

#endif
