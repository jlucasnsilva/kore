#include "Mesh.h"
#include "../IO/IO.h"
#include "../Log/Log.h"
#include "../Memory/Memory.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

static const size_t uvFloatCount = 2;
static const size_t vertexFloatCount = 3;
static const size_t triangleVertexCount = 3;

void allocateArrays(k_MeshSpreadedOBJ* restrict o, size_t count);

k_MeshSpreadedOBJ* k_LoadMeshSpreadedOBJ(const char* restrict filepath) {
    FILE* file = fopen(filepath, "r");
    if (!file) {
        k_LogFatalf("couldn't find the file '%s'\n", filepath);
    }

    k_MeshSpreadedOBJ* obj = k_New(k_MeshSpreadedOBJ, 1);
    if (!obj) {
        k_LogFatalf("failed to acquire memory for the mesh\n");
    }

    const int lineMaxSize = 1024;
    const int headerMaxSize = 256;
    char vertexCountStr[headerMaxSize];
    char descriptor[lineMaxSize];
    char line[lineMaxSize];
    *obj = (k_MeshSpreadedOBJ){
        .Vertices = NULL,
        .Normals = NULL,
        .UV = NULL,
        .Count = 0,
    };

    fgets(line, headerMaxSize, file);  // number of triagles
    sscanf(line, "%s %s", descriptor, vertexCountStr);
    fgets(line, headerMaxSize, file);  // schema

    size_t count = strtoul(vertexCountStr, NULL, 10);

    const size_t nFloatTriangle = triangleVertexCount * vertexFloatCount;
    const size_t nFloatNormal = triangleVertexCount * vertexFloatCount;
    const size_t nFloatUV = triangleVertexCount * uvFloatCount;
    const size_t lineFloatCount = nFloatTriangle + nFloatNormal + nFloatUV;
    const size_t totalFloats = count * lineFloatCount;

    allocateArrays(obj, count);

    for (size_t i = 0;
         i < totalFloats && !feof(file) && fgets(line, lineMaxSize, file);
         i += lineFloatCount) {
        size_t f = 0;
        char* tok = strtok(line, " ");

        while (f < nFloatTriangle && tok != NULL) {
            obj->Vertices[i + f] = strtof(tok, NULL);
            tok = strtok(NULL, " ");
            f++;
        }
        while (f < (nFloatTriangle + nFloatNormal) && tok != NULL) {
            obj->Normals[i + f] = strtof(tok, NULL);
            tok = strtok(NULL, " ");
            f++;
        }
        while (f < lineFloatCount && tok != NULL) {
            obj->UV[i + f] = strtof(tok, NULL);
            tok = strtok(NULL, " ");
            f++;
        }
    }

    fclose(file);
    return obj;
}

void k_MeshSpreadedOBJDestroy(k_MeshSpreadedOBJ** restrict o) {
    if (o) {
        k_Delete((*o)->Vertices);
        k_Delete(*o);
    }
}

void allocateArrays(k_MeshSpreadedOBJ* restrict o, size_t count) {
    const size_t totalVerticesFloats =
        count * triangleVertexCount * vertexFloatCount;
    const size_t totalNormalsFloats =
        count * triangleVertexCount * vertexFloatCount;
    const size_t totalUVsFloats =
        count * triangleVertexCount * uvFloatCount;
    const size_t totalFloats =
        totalVerticesFloats + totalNormalsFloats + totalUVsFloats;

    float* buffer = k_New(float, totalFloats);
    if (!buffer) {
        k_LogFatalf("failed to acquire memory for the mesh buffer\n");
    }

    o->Vertices = &buffer[0];
    o->Normals = &buffer[totalVerticesFloats];
    o->UV = &buffer[totalNormalsFloats];
    o->Count = count;
}
