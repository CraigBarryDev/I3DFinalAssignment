#ifndef UTILS_H
#define UTILS_H

#define TWO_PI 6.28318530718

//If on windows system, include windows.h
#ifdef _WIN32

#include <Windows.h>
#define M_PI (TWO_PI / 2.0f) 

#endif

#include <stdio.h>
#include <stdlib.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "SOIL.h"
#include <string.h>

#include <time.h>

#include "vectors.h"
#include "vectorMath.h"

static int windowWidth = 1000;
static int windowHeight = 800;
static int windowID = 0;

typedef enum Bool {
	false, true
}bool;

float radians(float deg);
float degrees(float rad);

int min(int a, int b);
int max(int a, int b);
float minf(float a, float b);
float maxf(float a, float b);

float absf(float a);

int randBetween(int min, int max);
float randBetweenf(float min, float max);

bool file_exists(const char* fname);

void swapf(float* a, float* b);

#endif
