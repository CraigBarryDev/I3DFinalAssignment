#include "objLoader.h"

static void convertOBJModelToBin(const char* filename, vectorf* vertices, vectorf* texCoords, vectorf* normals) {
	//Writes model data to a binary file for efficent reading
	FILE* file = fopen(filename, "wb");
	const int sz = sizeof(unsigned int);
	const int sf = sizeof(float);

	const unsigned int nVertices = (unsigned int)vertices->size;
	const unsigned int nTexCoords = (unsigned int)texCoords->size;
	const unsigned int nNormals = (unsigned int)normals->size;

	fwrite((const char*)&nVertices, sz, 1, file);
	fwrite((const char*)&nTexCoords, sz, 1, file);
	fwrite((const char*)&nNormals, sz, 1, file);

	fwrite((const char*)vertices->data, sf, nVertices, file);
	fwrite((const char*)texCoords->data, sf, nTexCoords, file);
	fwrite((const char*)normals->data, sf, nNormals, file);

	fclose(file);
}

//Writes an amount of object files to a single binary file for quick parsing
//of model data without the need for processing plaintext
static void convertOBJModelsToBin(const char* filename, 
	vectorf** vertices, vectorf** texCoords, vectorf** normals, unsigned int nModels) {

	FILE* file = fopen(filename, "wb");
	//Get the size of input types
	const int sz = sizeof(unsigned int);
	const int sf = sizeof(float);

	fwrite((const char*)&nModels, sz, 1, file);

	//Iterate through each of the models
	for (int i = 0; i < nModels; i++) {
		//Get the number of vert/texCoords/normals of the current model
		const unsigned int nVertices = (unsigned int)vertices[i]->size;
		const unsigned int nTexCoords = (unsigned int)texCoords[i]->size;
		const unsigned int nNormals = (unsigned int)normals[i]->size;

		//Write number of vert/texCoord/normals to the file
		fwrite((const char*)&nVertices, sz, 1, file);
		fwrite((const char*)&nTexCoords, sz, 1, file);
		fwrite((const char*)&nNormals, sz, 1, file);

		//Write the vert/texCoord/Normal data to the file in binary format
		fwrite((const char*)vertices[i]->data, sf, nVertices, file);
		fwrite((const char*)texCoords[i]->data, sf, nTexCoords, file);
		fwrite((const char*)normals[i]->data, sf, nNormals, file);
	}

	//Close the file handle
	fclose(file);
}

static void parseIndex(char* indexStr, const vectorf* verticesList, const vectorf* normalsList, const vectorf* texCoordsList,
	vectorf* vertices, vectorf* normals, vectorf* texCoords) {

	//Reads the index data in the following formats:
	//vertex
	//vertex/texCoord
	//vertex/texCoord/normal
	//veretex//normal

	bool isTexCoords = true;
	char *t1, *t2, *t3;
	int vert, texCoord, normal;

	//Checks if data is in v//n format
	if (strstr(indexStr, "//")) {
		isTexCoords = false;
	}

	//Tokenizes input by slashes
	t1 = strtok(indexStr, "/");
	t2 = strtok(NULL, "/");
	t3 = strtok(NULL, "/");

	//Gets the vertices from the index data
	vert = atoi(t1);
	push_back_vecf(vertices, verticesList->data[((vert-1) * 3)]);
	push_back_vecf(vertices, verticesList->data[((vert-1) * 3) + 1]);
	push_back_vecf(vertices, verticesList->data[((vert-1) * 3) + 2]);

	//If data isn't in v//n format and there is a 2nd token, the 2nd token will be texture coords
	if (isTexCoords && t2) {
		texCoord = atoi(t2);
		push_back_vecf(texCoords, texCoordsList->data[((texCoord - 1) * 2)]);
		push_back_vecf(texCoords, texCoordsList->data[((texCoord - 1) * 2)] + 1);
	}

	//If the data is in v//n format and there is a 2nd token, the 2nd token will be a normal vector,
	//Otherwise if there is a 3rd token that will be the normal vector, if neither of these are true,
	//then there is no normal vector
	if (!isTexCoords && t2) {
		normal = atoi(t2);
		push_back_vecf(normals, normalsList->data[((normal - 1) * 3)]);
		push_back_vecf(normals, normalsList->data[((normal - 1) * 3) + 1]);
		push_back_vecf(normals, normalsList->data[((normal - 1) * 3) + 2]);
	}
	else if (t3) {
		normal = atoi(t3);
		push_back_vecf(normals, normalsList->data[((normal - 1) * 3)]);
		push_back_vecf(normals, normalsList->data[((normal - 1) * 3) + 1]);
		push_back_vecf(normals, normalsList->data[((normal - 1) * 3) + 2]);
	}
}

model* loadBinFileOBJ(const char* filename) {
	//Reads model data written by the convertOBJModelToBin function for efficient reading
	FILE* file = fopen(filename, "rb");
	const int sz = sizeof(unsigned int);
	const int sf = sizeof(float);

	unsigned int nVertices = 0, nTexCoords = 0, nNormals = 0;
	fread((char*)&nVertices, sz, 1, file);
	fread((char*)&nTexCoords, sz, 1, file);
	fread((char*)&nNormals, sz, 1, file);

	vectorf* vertices = new_vectorf();
	vectorf* texCoords = new_vectorf();
	vectorf* normals = new_vectorf();
	resize_vecf(vertices, nVertices);
	resize_vecf(texCoords, nTexCoords);
	resize_vecf(normals, nNormals);
	vertices->size = nVertices;
	texCoords->size = nTexCoords;
	normals->size = nNormals;

	fread((char*)vertices->data, sf, nVertices, file);
	fread((char*)texCoords->data, sf, nTexCoords, file);
	fread((char*)normals->data, sf, nNormals, file);

	fclose(file);

	return new_model(vertices, normals, texCoords);
}

model* loadOBJ(const char* filename, int objIndex) {
	int nVertices = 0;
	int nNormals = 0;
	int nTexCoords = 0;
	int nIndices = 0;

	//Lists hold temporary values of all the vertices/normals/texCoords which then need to be reordered for opengl to read them
	vectorf* verticesList = new_vectorf();
	vectorf* normalsList = new_vectorf();
	vectorf* texCoordsList = new_vectorf();

	//These arrays hold the actual values that will be passed to OpenGL,
	//ordered by the indices in the OBJ file from the values in the above lists
	vectorf* vertices = new_vectorf();
	vectorf* normals = new_vectorf();
	vectorf* texCoords = new_vectorf();

	FILE* fp;
	char buffer[512];
	char dataFilename[512];
	char *keyword, *a1, *a2, *a3;
	float v1, v2, v3;
	model* m;

	strcpy(dataFilename, filename);
	strcat(dataFilename, "data");

	bool objFound = objIndex == -1;
	int nObjsFound = -1;

	//Open the file
	fp = fopen(filename, "r");

	//Iterate through each line of the file
	while (fgets(buffer, 512, fp)) {
		//Tokenize strings
		keyword = strtok(buffer, " ");
		a1 = strtok(NULL, " ");
		a2 = strtok(NULL, " ");
		a3 = strtok(NULL, " ");

		//Determine what kind of point it is
		if (!strcmp(keyword, "vn")) {
			v1 = (float)atof(a1);
			v2 = (float)atof(a2);
			v3 = (float)atof(a3);
			push_back_vecf(normalsList, v1);
			push_back_vecf(normalsList, v2);
			push_back_vecf(normalsList, v3);
		}
		else if (!strcmp(keyword, "vt")) {
			v1 = (float)atof(a1);
			v2 = (float)atof(a2);
			push_back_vecf(texCoordsList, v1);
			push_back_vecf(texCoordsList, v2);
		}
		else if (!strcmp(keyword, "v")) {
			v1 = (float)atof(a1);
			v2 = (float)atof(a2);
			v3 = (float)atof(a3);
			push_back_vecf(verticesList, v1);
			push_back_vecf(verticesList, v2);
			push_back_vecf(verticesList, v3);
		}
		else if (!strcmp(keyword, "f") && objFound) {
			parseIndex(a1, verticesList, normalsList, texCoordsList, vertices, normals, texCoords);
			parseIndex(a2, verticesList, normalsList, texCoordsList, vertices, normals, texCoords);
			parseIndex(a3, verticesList, normalsList, texCoordsList, vertices, normals, texCoords);
		}else if (!strcmp(keyword, "o")) {
			nObjsFound++;
			objFound = nObjsFound == objIndex;
		}
	}

	//Create the model using the points
	m = new_model(vertices, normals, texCoords);

	//Create a .objdata file using the .obj file for much faster loading of models in the future
	convertOBJModelToBin(dataFilename, vertices, texCoords, normals);

	//Destroy now unused temporary lists
	destroy_vectorf(verticesList);
	destroy_vectorf(normalsList);
	destroy_vectorf(texCoordsList);

	//Close the file handle
	fclose(fp);

	return m;
}

int getNumOfOBJs(const char* filename) {
	FILE* fp;
	char buffer[512];
	char* keyword;
	//Set number of objects to 0 initially
	int nObjects = 0;

	//Open the file
	fp = fopen(filename, "r");

	//Iterate through each line of the file
	while (fgets(buffer, 512, fp)) {
		//Tokenize strings
		keyword = strtok(buffer, " ");
		//Increment number of objects
		if(!strcmp(keyword, "o")) {
			nObjects++;
		}
	}
	//Close file
	fclose(fp);

	return nObjects;
}

model** loadBinFileOBJs(const char* filename, int* nObjects) {
	char buffer[512];
	FILE* file = fopen(filename, "rb");

	//Get the size of data types
	const int sz = sizeof(unsigned int);
	const int sf = sizeof(float);

	//Get the number of objects in the file
	fread((char*)nObjects, sz, 1, file);

	//Initialize arrays
	vectorf** vertices = (vectorf**)malloc(sizeof(vectorf*) * (*nObjects));
	vectorf** texCoords = (vectorf**)malloc(sizeof(vectorf*) * (*nObjects));
	vectorf** normals = (vectorf**)malloc(sizeof(vectorf*) * (*nObjects));
	//Initialize model list
	model** models = (model**)malloc(sizeof(model*) * (*nObjects));

	//Iterate throguh each model
	for (int i = 0; i < *nObjects; i++) {
		unsigned int nVertices = 0, nTexCoords = 0, nNormals = 0;
		fread((char*)&nVertices, sz, 1, file);
		fread((char*)&nTexCoords, sz, 1, file);
		fread((char*)&nNormals, sz, 1, file);

		assert(nNormals == nVertices);

		//Initialize instance arrays
		vertices[i] = new_vectorf();
		texCoords[i] = new_vectorf();
		normals[i] = new_vectorf();
		//Resize instance arrays to approriate capacties/sizes
		resize_vecf(vertices[i], nVertices);
		resize_vecf(texCoords[i], nTexCoords);
		resize_vecf(normals[i], nNormals);
		vertices[i]->size = nVertices;
		texCoords[i]->size = nTexCoords;
		normals[i]->size = nNormals;

		//Read data from file into vectors
		fread((char*)vertices[i]->data, sf, nVertices, file);
		fread((char*)texCoords[i]->data, sf, nTexCoords, file);
		fread((char*)normals[i]->data, sf, nNormals, file);

		//Create the model form its vertex/texCoord/normal data store in OBJ bin file
		models[i] = new_model(vertices[i], normals[i], texCoords[i]);
	}
	
	//Close the file
	fclose(file);

	return models;
}

//Load an object file as an array of seperate objects
model** loadOBJs(const char* filename, int* nObjects) {
	char dataFilename[512];
	strcpy(dataFilename, filename);
	strcat(dataFilename, "data");

	//If the binary file doesn't exist
	if (!file_exists(dataFilename)) {
		//Get the number of objects inside OBJ file
		*nObjects = getNumOfOBJs(filename);
		//Initialize array of models
		model** models = (model**)malloc(sizeof(model*) * (*nObjects));

		vectorf** vertices = (vectorf**)malloc(sizeof(vectorf*) * *nObjects);
		vectorf** texCoords = (vectorf**)malloc(sizeof(vectorf*) * *nObjects);
		vectorf** normals = (vectorf**)malloc(sizeof(vectorf*) * *nObjects);

		for (int i = 0; i < *nObjects; i++) {
			//Load the model
			model* m = loadOBJ(filename, i);
			//Add its data to the initializers
			vertices[i] = m->vertices;
			texCoords[i] = m->texCoords;
			normals[i] = m->normals;
			models[i] = m;
		}

		//Convert model into entire model
		convertOBJModelsToBin(dataFilename, vertices, texCoords, normals, *nObjects);

		//Return model object
		return models;
	}
	else {
		//Return model object loaded from binary file
		return loadBinFileOBJs(dataFilename, nObjects);
	}
}	

AABB getOBJCollider(const char* filename, float scale) {
	FILE* fp;
	char buffer[512];
	char dataFilename[512];
	AABB aabb;
	aabb.pos = new_vec3(0.0f, 0.0f, 0.0f);
	aabb.size = new_vec3(0.0f, 0.0f, 0.0f);

	float lowX = 0.0f;
	float lowY = 0.0f;
	float lowZ = 0.0f;
	float highX = 0.0f;
	float highY = 0.0f;
	float highZ = 0.0f;

	char *keyword, *a1, *a2, *a3;
	float v1, v2, v3;

	//Open the file
	fp = fopen(filename, "r");

	//Iterate through each line of the file
	while (fgets(buffer, 512, fp)) {
		//Tokenize strings
		keyword = strtok(buffer, " ");
		a1 = strtok(NULL, " ");
		a2 = strtok(NULL, " ");
		a3 = strtok(NULL, " ");

		if (!strcmp(keyword, "v")) {
			v1 = (float)atof(a1);
			v2 = (float)atof(a2);
			v3 = (float)atof(a3);

			lowX = minf(lowX, v1);
			lowY = minf(lowY, v2);
			lowZ = minf(lowZ, v3);
			highX = maxf(highX, v1);
			highY = maxf(highY, v2);
			highZ = maxf(highZ, v3);
		}
	}

	//Apply scaling
	lowX *= scale;
	lowY *= scale;
	lowZ *= scale;
	highX *= scale;
	highY *= scale;
	highZ *= scale;

	//Calculate AABB size
	aabb.size.x = highX - lowX;
	aabb.size.y = highY - lowY;
	aabb.size.z = highZ - lowZ;
	//Position AABB in middle of object
	aabb.pos.x = highX - aabb.size.x / 2.0f;
	aabb.pos.y = highY - aabb.size.y / 2.0f;
	aabb.pos.z = highZ - aabb.size.z / 2.0f;

	//Close the file handle
	fclose(fp);

	return aabb;
}