#include "skybox.h"

skybox* generate_skybox() {
	//Allocate memory for cube
	skybox* c = (skybox*)malloc(sizeof(skybox));
	//initialize cube coordinate arrays
	c->vertices = new_vectorf();
	c->texCoords = new_vectorf();
	c->indices = new_vectori();

	for(int i = 0; i < N_VERTICES * 3; i++)
		push_back_vecf(c->vertices, skybox_vertices[i]);

	for(int i = 0; i < N_TEXCOORDS * 2; i++)
		push_back_vecf(c->texCoords, skybox_texCoords[i]);

	for(int i = 0; i < N_INDICES; i++)
		push_back_veci(c->indices, skybox_indices[i]);

	return c;
}

void destroy_skybox(skybox* c) {
	destroy_vectorf(c->vertices);
	destroy_vectorf(c->texCoords);
	destroy_vectori(c->indices);
	free(c);
}
