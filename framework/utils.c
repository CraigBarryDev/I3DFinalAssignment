#include "utils.h"

float radians(float deg)  {
	return deg * (float)(TWO_PI / 360.0f);
}

float degrees(float rad) {
	return rad * (float)(360.0f / TWO_PI);
}

//min is inclusive, max is exclusive
int randBetween(int min, int max) {
	//If values wrong way round, swap them
	if(min > max) {
		int temp = min;
		min = max;
		max = temp;
	}
	//Return random between given values
	return (rand() % (max - min)) + min;
}

float randBetweenf(float min, float max) {
	//If values wrong way round, swap them
	if(min > max) {
		float temp = min;
		min = max;
		max = temp;
	}
	//Return random between 0 and 1
	float rand1 = (float)rand() / (float)RAND_MAX;
	//Returns random between given values
	return (rand1 * (max - min)) + min;
}

bool file_exists(const char *fname) {
	FILE *file;
	if (file = fopen(fname, "r")) {
		fclose(file);
		return true;
	}
	return false;
}

int min(int a, int b) {
	return a < b ? a : b;
}

int max(int a, int b) {
	return a > b ? a : b;
}

float minf(float a, float b) {
	return a < b ? a : b;
}

float maxf(float a, float b) {
	return a > b ? a : b;
}

float absf(float a) {
	return a > 0.0f ? a : -a;
}

void swapf(float* a, float* b) {
	float temp = *a;
	*a = *b;
	*b = temp;
}