#ifndef _K_IO_IO_H_
#define _K_IO_IO_H_

#include <stdint.h>
#include <stdlib.h>

typedef struct {
    char* Input;
    int64_t Length;
    int64_t FileSize;
} k_IOFileContent;

k_IOFileContent k_IOReadFile(const char* restrict path);
void k_IOReadFileInto(const char* restrict path,
                      k_IOFileContent* restrict into,
                      size_t capacity);

k_IOFileContent k_IOReadTextFile(const char* restrict path);
void k_IOReadTextFileInto(const char* restrict path,
                          k_IOFileContent* restrict into,
                          size_t capacity);

#endif  // _K_IO_IO_H_
