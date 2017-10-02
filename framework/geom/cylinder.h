#include "../utils.h"

#ifndef CYLINDER_H
#define CYLINDER_H

typedef struct {
	vectorf* vertices;
	vectorf* normals;
	vectorf* texCoords;
	vectori* indices;
}cylinder;

cylinder* generate_cylinder(int stacks, int slices, float radius);
void destroy_cylinder(cylinder* c);

#endif
