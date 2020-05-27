#ifdef LinuxBuild
#include "io.h"

#include <stdint.h>
#include <stdlib.h>

#include <SDL2/SDL.h>

// ========================================================
//
// Implementation
//
// ========================================================

k_IOFileContent k_IOReadFile(const char* restrict path) {
    k_IOFileContent ret = {.input = NULL, .len = -1, .fileSize = -1};
    SDL_RWops* in = SDL_RWFromFile(path, "rb");
    if (!in) {
        return ret;
    }

    int64_t size = SDL_RWsize(in);
    if (size < 0) {
        return ret;
    }

    ret.input = malloc(size);
    if (!ret.input) {
        return ret;
    }

    SDL_RWread(in, ret.input, size, 1);
    ret.fileSize = size;
    ret.len = size;
    SDL_RWclose(in);
    return ret;
}

void k_IOReadFileInto(const char* restrict path,
                      k_IOFileContent* restrict into,
                      size_t capacity) {
    *into = (k_IOFileContent){.input = NULL, .len = -1, .fileSize = -1};

    SDL_RWops* in = SDL_RWFromFile(path, "rb");
    if (!in) {
        return;
    }

    int64_t size = SDL_RWsize(in);
    if (size < 0) {
        return;
    }

    SDL_RWread(in, into->input, capacity, 1);
    into->fileSize = size;
    into->len = capacity;
    SDL_RWclose(in);
    return;
}

k_IOFileContent k_IOReadStringFile(const char* restrict path) {
    k_IOFileContent ret = {.input = NULL, .len = -1, .fileSize = -1};
    SDL_RWops* in = SDL_RWFromFile(path, "r");
    if (!in) {
        return ret;
    }

    int64_t size = SDL_RWsize(in);
    if (size < 0) {
        return ret;
    }

    size_t cap = size + 1;
    ret.input = malloc(cap);
    if (!ret.input) {
        return ret;
    }

    SDL_RWread(in, ret.input, size, 1);
    ret.input[size] = '\0';
    ret.fileSize = cap;
    ret.len = cap;
    SDL_RWclose(in);
    return ret;
}

void k_IOReadStringFileInto(const char* restrict path,
                            k_IOFileContent* restrict into,
                            size_t capacity) {
    *into = (k_IOFileContent){.input = NULL, .len = -1, .fileSize = -1};

    SDL_RWops* in = SDL_RWFromFile(path, "rb");
    if (!in) {
        return;
    }

    int64_t size = SDL_RWsize(in);
    if (size < 0) {
        return;
    }

    SDL_RWread(in, into->input, capacity - 1, 1);
    into->input[capacity > size ? size : capacity] = '\0';
    into->fileSize = size;
    into->len = capacity;
    SDL_RWclose(in);
    return;
}
#endif