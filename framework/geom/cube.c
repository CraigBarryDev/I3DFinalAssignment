#include "cube.h"

cube* generate_cube() {
	//Allocate memory for cube
	cube* c = (cube*)malloc(sizeof(cube));
	//initialize cube coordinate arrays
	c->vertices = new_vectorf();
	c->normals = new_vectorf();
	c->indices = new_vectori();

	for(int i = 0; i < N_VERTICES * 3; i++)
		push_back_vecf(c->vertices, cube_vertices[i]);
	for(int i = 0; i < N_NORMALS * 3; i++)
		push_back_vecf(c->normals, cube_normals[i]);
	for(int i = 0; i < N_INDICES; i++)
		push_back_veci(c->indices, cube_indices[i]);

	return c;
}

void destroy_cube(cube* c) {
	destroy_vectorf(c->vertices);
	destroy_vectorf(c->normals);
	destroy_vectori(c->indices);
	free(c);
}