#include "sphere.h"

sphere* generate_sphere(int stacks, int slices, float radius) {
	//Allocate memory for sphere object
	sphere* s = (sphere*)malloc(sizeof(sphere));
	//Init sphere coordinate vectors
	s->vertices = new_vectorf();
	s->normals = new_vectorf();
	s->texCoords = new_vectorf();
	s->indices = new_vectori();

	//The angle covered by a given stack from the middle
	float sliceAngle = 180.0;
	float currSliceAngle = 0.0f;

	for(unsigned int j = 0; j <= stacks; j++) {
		for (unsigned int i = 0; i <= slices; i++) {
			//Determine the angle from the centre of the circle
			float theta = (float)((float)i / (float)(slices)) * (2.0f * 3.1419f);
			float currSliceAngle = (float)((float)j / (float)(stacks)) * (3.1419f);
			//Generate the points of the circle based on the radius and angle from the centre
			// float x = radius * cosf(theta) * sinf(currSliceAngle);
			// float y = radius * sinf(theta) * sinf(currSliceAngle);
			// float z = radius * cosf(currSliceAngle);
			float x = radius * cosf(theta) * sinf(currSliceAngle);
			float y = radius * cosf(currSliceAngle);
			float z = radius * sinf(theta) * sinf(currSliceAngle);
			//Add the xyz coordinates to the points array
			push_back_vecf(s->vertices, x);
			push_back_vecf(s->vertices, y);
			push_back_vecf(s->vertices, z);

			//Calculate the surface normal
			vec3 normal = vec_normalize(new_vec3(x,y,z));
			//Add normals to coordinates arrays
			push_back_vecf(s->normals, normal.x);
			push_back_vecf(s->normals, normal.y);
			push_back_vecf(s->normals, normal.z);

			//Calculate texture coordinates
			push_back_vecf(s->texCoords, ((float)(slices - i) / (float)(slices)));
			push_back_vecf(s->texCoords, ((float)(stacks - j) / (float)(stacks)));
		}
	}

	for(unsigned int j = 0; j < stacks; j++) {
		for (unsigned int i = 0; i < slices; i++) {
			push_back_veci(s->indices, i + 1 + (j * (slices + 1)));
			push_back_veci(s->indices, i + 1 + ((j + 1) * (slices + 1)));
			push_back_veci(s->indices, i + (j * (slices + 1)));
	
			push_back_veci(s->indices, i + ((j + 1) * (slices + 1)));
			push_back_veci(s->indices, i + (j * (slices + 1)));
			push_back_veci(s->indices, i + 1 + ((j + 1) * (slices + 1)));
		}
	}
	
	return s;
}

void destroy_sphere(sphere* s) {
	//free memory allocated for the sphere coordinates
	destroy_vectorf(s->vertices);
	destroy_vectori(s->indices);
	destroy_vectorf(s->normals);
	destroy_vectorf(s->texCoords);
	//free memory allocated for sphere object
	free(s);
}