#include "model.h"
#include "collisions.h"
#include <assert.h>

#ifndef OBJ_LOADER_H
#define OBJ_LOADER_H

model* loadOBJ(const char* filename, int objIndex);
model** loadOBJs(const char* filename, int* nObjects);
AABB getOBJCollider(const char* filename, float scale);

#endif