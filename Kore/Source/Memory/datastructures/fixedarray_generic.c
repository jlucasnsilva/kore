// TODO concluir

#include "fixedarray_generic.h"

#include <string.h>
#include <stdbool.h>

#define K_FIXED_ARRAY_DEFINE_IMPL(T, SKb)                                    \
                                                                             \
    typedef struct {                                                         \
        size_t cap;                                                          \
        size_t len;                                                          \
        T array[];                                                           \
    } k_##T##SKb##Array;                                                     \
                                                                             \
    static inline k_##T##SKb##Array* deref(T* restrict a) {                  \
        return (void*)(a - sizeof(k_##T##SKb##Array));                       \
    }                                                                        \
                                                                             \
    k_##T##SKb##Array* k_##T##SKb####T##ArrayCreate() {                      \
        size_t nbytes = 1024 * SKb;                                          \
        size_t cap = nbytes / sizeof(k_##T##SKb##Array);                     \
        k_##T##SKb##Array* a = malloc(nbytes);                               \
                                                                             \
        if (!a) {                                                            \
            return NULL;                                                     \
        }                                                                    \
                                                                             \
        *a = (k_##T##SKb##Array){                                            \
            .cap = cap,                                                      \
            .len = 0,                                                        \
        };                                                                   \
                                                                             \
        return a->array;                                                     \
    }                                                                        \
                                                                             \
    void k_##T##SKb####T##ArrayDelete(T** restrict a) {                      \
        if (a && *a) {                                                       \
            k_##T##SKb##Array* arr = deref(*a);                              \
            free(arr);                                                       \
            *a = NULL;                                                       \
        }                                                                    \
    }                                                                        \
                                                                             \
    size_t k_##T##SKb####T##ArrayCap(T* restrict a) {                        \
        if (a) {                                                             \
            return deref(a)->cap;                                            \
        }                                                                    \
                                                                             \
        return 0;                                                            \
    }                                                                        \
                                                                             \
    size_t k_##T##SKb####T##ArrayLen(T* restrict a) {                        \
        if (a) {                                                             \
            return deref(a)->len;                                            \
        }                                                                    \
                                                                             \
        return 0;                                                            \
    }                                                                        \
                                                                             \
    void* k_##T##SKb####T##ArrayAppend(T* restrict a, const T* restrict v) { \
        if (!a || !value) {                                                  \
            return false;                                                    \
        }                                                                    \
                                                                             \
        k_##T##SKb####T##Array* arr = deref(a);                              \
        if (arr->len >= arr->cap) {                                          \
            return false;                                                    \
        }                                                                    \
                                                                             \
        arr->array[arr->len] = *v;                                           \
        arr->len++;                                                          \
        return true;                                                         \
    }