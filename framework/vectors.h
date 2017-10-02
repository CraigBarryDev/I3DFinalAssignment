#include <stdlib.h>

#ifndef VECTORS_H
#define VECTORS_H

typedef struct vector_integer{
	//The data the vector holds
	int* data;
	//The number of integers the vector holds
	int size;
	//The number of integers the vector can hold before resizing (its size in memory)
	int capacity;
}vectori;

typedef struct vector_float{
	//The data the vector holds
	float* data;
	//The number of floats the vector holds
	int size;
	//The number of floats the vector can hold before resizing (its size in memory)
	int capacity;
}vectorf;

vectori* new_vectori();
vectorf* new_vectorf();
void destroy_vectorf(vectorf* v);
void destroy_vectori(vectori* v);

void resize_veci(vectori* v, int size);
void resize_vecf(vectorf* v, int size);
void push_back_veci(vectori* v, int data);
void push_back_vecf(vectorf* v, float data);
void remove_at_veci(vectori* v, int index);
void remove_at_vecf(vectorf* v, int index);

#endif