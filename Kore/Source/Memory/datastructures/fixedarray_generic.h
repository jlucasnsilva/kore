#ifndef _K_DATASTRUCTURE_FIXED_ARRAY_GENERIC_H_
#define _K_DATASTRUCTURE_FIXED_ARRAY_GENERIC_H_

// TODO concluir

#include <stdlib.h>
#include <stdbool.h>

#define K_FIXED_ARRAY_DEFINE_HEADER(T, SKb)             \
                                                        \
    typedef struct k_##T##SKb##Array k_##T##SKb##Array; \
                                                        \
    T *k_##T##SKb####T##ArrayCreate();                  \
    void k_##T##SKb##ArrayDelete(T **restrict a);       \
                                                        \
    size_t k_##T##SKb##ArrayCap(T *restrict a);         \
    size_t k_##T##SKb##ArrayLen(T *restrict a);         \
                                                        \
    bool k_##T##SKb##ArrayAdd(T *restrict a);           \
    k_##T##SKb##ArrayPop(T *restrict a);                \
    size_t k_##T##SKb##ArrayRemove(T *restrict a);      \
    size_t k_##T##SKb##ArrayClear(T *restrict a);       \
                                                        \
    bool *k_##T##SKb##ArrayAppend(T *restrict a, const T *restrict value);

#endif  // _K_DATASTRUCTURE_FIXED_ARRAY_GENERIC_H_
