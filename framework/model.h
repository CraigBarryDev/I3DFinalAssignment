#include "utils.h"
#include "vectors.h"

#ifndef MODEL_H
#define MODEL_H

typedef struct {
	vectorf* vertices;
	vectorf* normals;
	vectorf* texCoords;
	vectori* indices;
	GLuint texture;

	bool showTextures;
	bool renderTransformations;
	vec3 pos;
	vec3 rot;
	vec3 scale;
}model;

model* new_model(vectorf* vertices, vectorf* normals, vectorf* texCoords);
model* new_model_wIndices(vectorf* vertices, vectorf* normals, vectorf* texCoords, vectori* indices);

void render(model* m);
void destroy_model(model* m);

#endif