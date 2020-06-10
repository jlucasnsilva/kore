#ifndef _K_LOADER_MSTH_H_
#define _K_LOADER_MSTH_H_

#include <stdlib.h>

typedef struct {
    float* Vertices;
    float* UV;
    float* Normals;
    size_t Count;
} k_MeshSpreadedOBJ;

k_MeshSpreadedOBJ* k_LoadMeshSpreadedOBJ(const char* restrict filepath);
void k_MeshSpreadedOBJDestroy(k_MeshSpreadedOBJ** restrict o);

#endif  // _K_LOADER_MSTH_H_
