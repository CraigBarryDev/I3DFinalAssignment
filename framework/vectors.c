#include "vectors.h"

vectori* new_vectori() {
	//Capacity of a new vector
	const static int capacity = 10;
	vectori* v;
	//Allocate memory for vector
	v = (vectori*)malloc(sizeof(vectori));
	//Allocate memory for data
	v->data = (int*)malloc(sizeof(int) * capacity);
	//Set initial values
	v->size = 0;
	v->capacity = capacity;
	//Return new vector
	return v;
}

void destroy_vectori(vectori* v) {
	free(v->data);
	free(v);
}

void resize_veci(vectori* v, int size) {
	//Resizes the array to a given size
	v->data = (int*)realloc(v->data, sizeof(int) * size);
	//Updates the capacity value
	v->capacity = size;
}

void push_back_veci(vectori* v, int data) {
	//If adding this element requires more memory
	if (v->size == v->capacity) {
		if (v->capacity < 100)
			//if capacity is under 100 grow memory by 10
			resize_veci(v, v->capacity + 10);
		else
			//If capacity is over 100, grow memory by 10%
			resize_veci(v, v->capacity + (v->capacity * 0.1));
	}
	//Add the element
	v->data[v->size++] = data;
}

void remove_at_veci(vectori* v, int index) {
	//TO BE IMPLEMENTED
}

//Creates a new vector
vectorf* new_vectorf() {
	//Capacity of a new vector
	const static int capacity = 10;
	vectorf* v;
	//Allocate memory for vector
	v = (vectorf*)malloc(sizeof(vectorf));
	//Allocate memory for data
	v->data = (float*)malloc(sizeof(float) * capacity);
	//Set initial values
	v->size = 0;
	v->capacity = capacity;
	//Return new vector
	return v;
}

//Frees the memory of a vector
void destroy_vectorf(vectorf* v) {
	free(v->data);
	free(v);
}

void resize_vecf(vectorf* v, int size) {
	//Resizes the array to a given size
	v->data = (float*)realloc(v->data, sizeof(float) * size);
	//Updates the capacity value
	v->capacity = size;
}

void push_back_vecf(vectorf* v, float data) {
	//If adding this element requires more memory
	if (v->size == v->capacity) {
		if (v->capacity < 100)
			//if capacity is under 100 grow memory by 10
			resize_vecf(v, v->capacity + 10);
		else 
			//If capacity is over 100, grow memory by 10%
			resize_vecf(v, v->capacity + (v->capacity * 0.1));
	}
	//Add the element
	v->data[v->size++] = data;
}

void remove_at(vectorf* v, int index) {
	//TO BE IMPLEMENTED
}
