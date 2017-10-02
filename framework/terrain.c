#include "terrain.h"

terrain* generate_terrain(float sizeX, float sizeZ, int nSquaresX, int nSquaresZ) {
	int x = 0;
	int z = 0;
	terrain* t = (terrain*)malloc(sizeof(terrain));
	t->sizeX = sizeX;
	t->sizeZ = sizeZ;
	t->nSquaresX = nSquaresX;
	t->nSquaresZ = nSquaresZ;
	t->vertices = new_vectorf();
	t->normals = new_vectorf();
	t->texCoords = new_vectorf();
	t->indices = new_vectori();
	t->pos = new_vec3(0.0f, 0.0f, 0.0f);
	t->showTextures = true;

	nSquaresX += 1;
	nSquaresZ += 1;

	//Iterate across the x axis
	for (z = 0; z < nSquaresZ; z++) {
		//Iterate across the z axis
		for (x = 0; x < nSquaresX; x++) {
			// Set x,y,z vertex positions respectively
			push_back_vecf(t->vertices, sizeX * ((float)x / (nSquaresX - 1)) - sizeX / 2.0f);
			push_back_vecf(t->vertices, 0.0f); //y set as 0 for now
			push_back_vecf(t->vertices, sizeZ * ((float)z / (nSquaresZ - 1)) - sizeZ / 2.0f);
			//Set normals, Normal will be straight up as y is set to 0
			push_back_vecf(t->normals, 0.0f);
			push_back_vecf(t->normals, 1.0f);
			push_back_vecf(t->normals, 0.0f);
			//Set TexCoords
			push_back_vecf(t->texCoords, ((float)x / (nSquaresX - 1)) * sizeX);
			push_back_vecf(t->texCoords, ((float)z / (nSquaresZ - 1)) * sizeZ);
		}
	}

	//Iterate across the z axis
	for (z = 0; z < nSquaresZ - 1; z++) {
		//Iterate across the x axis
		for (x = 0; x < nSquaresX - 1; x++) {
			//Get the vertex indices of each corner of the square
			int topLeft = x + (z * nSquaresZ);
			int topRight = (x + 1) + (z * nSquaresZ);
			int bottomLeft = x + ((z + 1) * nSquaresZ);
			int bottomRight = (x + 1) + ((z + 1) * nSquaresZ);

			//Put the indices for the top left triangle in cc order
			push_back_veci(t->indices, topLeft);
			push_back_veci(t->indices, bottomLeft);
			push_back_veci(t->indices, topRight);
			//Put the indices for the bottom right triangle in cc order
			push_back_veci(t->indices, topRight);
			push_back_veci(t->indices, bottomLeft);
			push_back_veci(t->indices, bottomRight);
		}
	}

	return t;
}

terrain* generate_terrain_from_heightmap(float sizeX, float sizeZ, int nSquaresX,
	 int nSquaresZ, float minHeight, float maxHeight, const char * filename) {

	//Heightmap data
	int mWidth, mHeight, mChannels;
	float heightRange = maxHeight - minHeight;

	//Generate a new terrain object
	terrain* t = generate_terrain(sizeX, sizeZ, nSquaresX, nSquaresZ);

	//Load heightmap from file
	unsigned char *map = SOIL_load_image(filename, &mWidth, &mHeight, &mChannels, SOIL_LOAD_RGB);

	//There is one more vertex than squares
	nSquaresX += 1;
	nSquaresZ += 1;

	//Iterate across the z axis
	for (int z = 0; z < nSquaresZ; z++) {
		//Iterate across the x axis
		for (int x = 0; x < nSquaresX; x++) {
			//Calculate which pixel from the heightmap to use
			int mapPixelX = ((float)x / (float)(nSquaresX)) * (mWidth);
			int mapPixelZ = ((float)z / (float)(nSquaresZ)) * (mHeight);

			int index = ((mapPixelX + (mapPixelZ * (mWidth))) * mChannels);

			//Get the height of the from the pixel map
			float height = ((int)map[index] / 255.0f) * heightRange + minHeight;

			//height = 1.0f;

			//Update height of the terrain point
			setTerrainHeightAtVertex(t, x, z, height);	
		}
	}

	//Free image
	SOIL_free_image_data(map);

	//Update the terrain's normals
	updateNormals(t);

	//Return new terrain object
	return t;
}

void render_terrain(terrain* t) {
	glPushMatrix();
	glTranslatef(t->pos.x, t->pos.y, t->pos.z);

	if(t->showTextures && t->texture != -1) {
		//Bind texture
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, t->texture);

		//Set the texture coords
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glTexCoordPointer(2, GL_FLOAT, 0, t->texCoords->data);
	}

	//Sets the models normals
	glEnableClientState(GL_NORMAL_ARRAY);
	glNormalPointer(GL_FLOAT, 0, t->normals->data);

	//Sets the models vertices to the VAO
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, t->vertices->data);

	//Draws the model
	glDrawElements(GL_TRIANGLES, t->indices->size, GL_UNSIGNED_INT, t->indices->data);
	
	//Unbind texture
	glBindTexture(GL_TEXTURE_2D, 0);

	//Disable client states
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);

	glPopMatrix();
}

float getTerrainHeightAtVertex(terrain* t, int x, int z) {
	int index3f = (x + (z * (t->nSquaresZ + 1))) * 3;
	return t->vertices->data[index3f + 1];
}

float getTerrainHeightAtPos(terrain* t, float x, float z) {
	x += (t->sizeX / 2.0f);
	z += (t->sizeZ / 2.0f);
	//Get x,z size of terrain squares
	float gridSquareSizeX = t->sizeX / (t->nSquaresX);
	float gridSquareSizeZ = t->sizeZ / (t->nSquaresZ);
	//Get which grid square the position is in
	int gridX = (x / gridSquareSizeX);
	int gridZ = (z / gridSquareSizeZ);
	//Get the position within the square (from <x,z>:(0,0) to (1,1))
	float xCoord = fmod(x, gridSquareSizeX) / gridSquareSizeX;
	float zCoord = fmod(z, gridSquareSizeZ) / gridSquareSizeZ;

	//Check the grid square actually exists
	if (gridX >= t->nSquaresX || (float)x < 0.0f ||
		gridZ >= t->nSquaresZ || (float)z < 0.0f) {
		return -20.0f;
	}

	float yCoord;
	//Test which triangle we are inside (the middle of the triangle will be the x=1-zCoord,
	//so testing which triangle we are in is simply testing if x < 1-zCoord and vice versa)
	if (xCoord <= (1.0f - zCoord)) {
		yCoord = barryCentricInterpolation(new_vec3(0.0f, getTerrainHeightAtVertex(t, gridX, gridZ), 0.0f), 
			new_vec3(1.0f, getTerrainHeightAtVertex(t, gridX + 1, gridZ), 0.0f),
			new_vec3(0.0f, getTerrainHeightAtVertex(t, gridX, gridZ + 1), 1.0f),
			new_vec2(xCoord, zCoord));
	}
	else {
		yCoord = barryCentricInterpolation(new_vec3(1.0f, getTerrainHeightAtVertex(t, gridX + 1, gridZ), 0.0f),
			new_vec3(0.0f, getTerrainHeightAtVertex(t, gridX, gridZ + 1), 1.0f),
			new_vec3(1.0f, getTerrainHeightAtVertex(t, gridX + 1, gridZ + 1), 1.0f),
			new_vec2(xCoord, zCoord));
	}

	//Return height at position
	return yCoord;
}

void setTerrainHeightAtVertex(terrain* t, int x, int z, float height) {
	t->vertices->data[((x + (z * (t->nSquaresZ + 1))) * 3) + 1] = height;
}

vec3 getNormalAtVertex(terrain* t, int x, int z) {
	int index3f = (x + (z * t->nSquaresZ)) * 3;
	x = min(max(x, t->nSquaresX), 0);
	z = min(max(z, t->nSquaresZ), 0);
	return new_vec3(t->normals->data[index3f], t->normals->data[index3f + 1], t->normals->data[index3f + 2]);
}

void updateNormals(terrain* t) {
	int x, z;

	const float INTERVAL_2X = (t->sizeX / t->nSquaresX) * 2;
	const float INTERVAL_2Z = (t->sizeZ / t->nSquaresZ) * 2;

	//Iterate across the x axis
	for (z = 0; z < t->nSquaresZ; z++) {
		//Iterate across the z axis
		for (x = 0; x < t->nSquaresX; x++) {
			const int index3f = (x + (z * t->nSquaresZ)) * 3;
			const int index6f = (x + (z * t->nSquaresZ)) * 6;
			//Calculate the interval between 2 squares on a terrain
			float interval2X = INTERVAL_2X;
			float interval2Z = INTERVAL_2Z;

			//If its on the edge then the intervals need to be halfed (as they use the same point for the neighbouring
			//point on the edge side meaning the interval between the 2 points is half what it noramly is)
			if (x == 0 || x == t->nSquaresX - 1) interval2X /= 2;
			if (z == 0 || z == t->nSquaresZ - 1) interval2Z /= 2;

			//Calculate the vector connection the two neighbouring points across the x-axis
			vec3 xVec = new_vec3(interval2X, getTerrainHeightAtVertex(t, min(x + 1, t->nSquaresX - 1), z) - getTerrainHeightAtVertex(t, max(x - 1, 0), z), 0.0f);
			//Calculate the vector connecting the two neighbouring points accross the z-axis
			vec3 zVec = new_vec3(0.0f, getTerrainHeightAtVertex(t, x, min(z + 1, t->nSquaresZ - 1)) - getTerrainHeightAtVertex(t, x, max(z - 1, 0)), interval2Z);
			//Calculate the normal (the cross product of the z and x vectors)
			vec3 normal = cross_prod(zVec, xVec);

			//Normalize the normal vector
			normalize(&normal);
			//Set the normal
			t->normals->data[index3f] = normal.x;
			t->normals->data[index3f + 1] = normal.y;
			t->normals->data[index3f + 2] = normal.z;
		}
	}
	
}

void destroy_terrain(terrain* t) {
	destroy_vectorf(t->vertices);
	destroy_vectorf(t->normals);
	destroy_vectorf(t->texCoords);
	destroy_vectori(t->indices);
	free(t);
}