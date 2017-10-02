#include "cylinder.h"

static void addCylinderCap(cylinder* c, float radius, float slices, bool top);

cylinder* generate_cylinder(int stacks, int slices, float radius) {
	//Allocate memory for cylinder object
	cylinder* c = (cylinder*)malloc(sizeof(cylinder));
	//Init cylinder coordinate vectors
	c->vertices = new_vectorf();
	c->normals = new_vectorf();
	c->indices = new_vectori();
	c->texCoords = new_vectorf();

	for(unsigned int j = 0; j <= stacks; j++) {
		for (unsigned int i = 0; i <= slices; i++) {
			//Determine the angle from the centre of the circle
			float theta = (float)((float)i / (float)(slices)) * (2.0f * 3.1419f);

			//Generate the points of the circle based on the redius and angle from the centre
			float x = radius * cosf(theta);
			float y = (((float)j / (float)stacks) - 0.5f) * (radius * 2.0f);
			float z = radius * sinf(theta);
			//Add the xyz coordinates to the points array
			push_back_vecf(c->vertices, x);
			push_back_vecf(c->vertices, y);
			push_back_vecf(c->vertices, z);

			//Calculate the surface normal
			vec3 normal = vec_normalize(new_vec3(x,0.0f,z));
			//Add normals to coordinates arrays
			push_back_vecf(c->normals, normal.x);
			push_back_vecf(c->normals, normal.y);
			push_back_vecf(c->normals, normal.z);

			//Set texture coordinates
			push_back_vecf(c->texCoords, (float)i / (float)slices);
			push_back_vecf(c->texCoords, (float)j / (float)stacks);
		}
	}

	for(unsigned int j = 0; j < stacks; j++) {
		for (unsigned int i = 0; i < slices; i++) {
			//Set indicies
	 		push_back_veci(c->indices, i + (j * (slices + 1)));
			push_back_veci(c->indices, i + 1 + ((j + 1) * (slices + 1)));
			push_back_veci(c->indices, i + 1 + (j * (slices + 1)));
	
			push_back_veci(c->indices, i + 1 + ((j + 1) * (slices + 1)));
			push_back_veci(c->indices, i + (j * (slices + 1)));
			push_back_veci(c->indices, i + ((j + 1) * (slices + 1)));
		}
	}

	//Add cylinder's top and bottom
	addCylinderCap(c, radius, slices, true);
	addCylinderCap(c, radius, slices, false);

	//Return cylinder object
	return c;
}

static void addCylinderCap(cylinder* c, float radius, float slices, bool top) {
	int nVertices = c->vertices->size / 3;

	push_back_vecf(c->vertices, 0.0f);
	push_back_vecf(c->vertices, top ? radius : -radius);
	push_back_vecf(c->vertices, 0.0f);
	push_back_vecf(c->normals, 0.0f);
	push_back_vecf(c->normals, top ? 1.0f : -1.0f);
	push_back_vecf(c->normals, 0.0f);
	push_back_vecf(c->texCoords, top ? 1.0f : 0.0f);
	push_back_vecf(c->texCoords, top ? 1.0f : 0.0f);
		
	for (unsigned int i = 0; i <= slices; i++) {
		//Determine the angle from the centre of the circle
		float theta = (float)((float)i / (float)(slices)) * (2.0f * 3.1419f);
		//Generate the points of the circle based on the redius and angle from the centre
		float x = radius * cosf(theta);
		float y = top ? radius : -radius;
		float z = radius * sinf(theta);
		//Add the xyz coordinates to the points array
		push_back_vecf(c->vertices, x);
		push_back_vecf(c->vertices, y);
		push_back_vecf(c->vertices, z);

		//Add normals to coordinates arrays
		push_back_vecf(c->normals, 0.0f);
		push_back_vecf(c->normals, top ? 1.0f : -1.0f);
		push_back_vecf(c->normals, 0.0f);

		//Set texture coordinates
		push_back_vecf(c->texCoords, top ? 1.0f : 0.0f);
		push_back_vecf(c->texCoords, top ? 1.0f : 0.0f);
	}

	for (unsigned int i = 0; i < slices; i++) {
		//Set indicies
		if(top) {
			push_back_veci(c->indices, i + nVertices + 2);
	 		push_back_veci(c->indices, i + nVertices + 1);
			push_back_veci(c->indices, nVertices);
		}else {
			push_back_veci(c->indices, nVertices);
	 		push_back_veci(c->indices, i + nVertices + 1);
			push_back_veci(c->indices, i + nVertices + 2);
		}
		
	}
}

void destroy_cylinder(cylinder* c) {
	//free memory allocated for the sphere coordinates
	destroy_vectorf(c->vertices);
	destroy_vectori(c->indices);
	destroy_vectorf(c->normals);
	destroy_vectorf(c->texCoords);
	//free memory allocated for sphere object
	free(c);
}