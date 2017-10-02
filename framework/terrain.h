#include "utils.h"

#ifndef TERRAIN_H
#define TERRAIN_H

typedef struct {
	vectorf* vertices;
	vectorf* normals;
	vectorf* texCoords;
	vectori* indices;
	int texture;

	vec3 pos;
	float sizeX;
	float sizeZ;
	int nSquaresX;
	int nSquaresZ;
	bool showTextures;
}terrain;

terrain* generate_terrain(float sizeX, float sizeZ, int nSquaresX, int nSquaresZ);
terrain* generate_terrain_from_heightmap(float sizeX, float sizeZ, int nSquaresX,
	 int nSquaresZ, float minHeight, float maxHeight, const char * filename);

void render_terrain(terrain* t);
float getTerrainHeightAtVertex(terrain* t, int x, int z);
float getTerrainHeightAtPos(terrain* t, float x, float z);
vec3 getNormalAtVertex(terrain* t, int x, int z);
vec3 getNormalAtPos(terrain* t, float x, float z);
void setTerrainHeightAtVertex(terrain* t, int x, int z, float height);
void destroy_terrain(terrain* t);
void updateNormals(terrain* t);

#endif
