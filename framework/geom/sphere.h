#include "../utils.h"

#ifndef SPHERE_H
#define SPHERE_H

typedef struct {
	vectorf* vertices;
	vectorf* normals;
	vectorf* texCoords;
	vectori* indices;
}sphere;

sphere* generate_sphere(int stacks, int slices, float radius);
void destroy_sphere(sphere* s);

#endif
