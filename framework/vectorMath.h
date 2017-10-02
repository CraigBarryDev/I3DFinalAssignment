#include <math.h>
#include "utils.h"

#ifndef VECTOR_MATH_H
#define VECTOR_MATH_H

typedef struct {
	float x, y;
}vec2;

typedef struct {
	float x, y, z;
}vec3;

typedef struct {
	float x, y, z, w;
}vec4;

vec2 new_vec2(float x, float y);
vec3 new_vec3(float x, float y, float z);
vec4 new_vec4(float x, float y, float z, float w);

vec3 cross_prod(vec3 v1, vec3 v2);
vec3 vec_negate(vec3 v);
vec3 vec_add(vec3 v1, vec3 v2);
vec3 vec_subtract(vec3 v1, vec3 v2);
vec3 vec_mult_scalar(vec3 v, float scalar);
vec3 getNormalFromPlane(vec3 p1, vec3 p2, vec3 p3);
vec3 vec_normalize(vec3);
vec3 vec_sinusoidal_lerp(float t0, vec3 v0, float t1, vec3 v1, float t);
vec3 vec_cosine_lerp(float t0, vec3 v0, float t1, vec3 v1, float t);

void normalize(vec3* v);
float magnitude(const vec3* v);
float dot_prod(vec3 v1, vec3 v2);
float vec_angle_between(vec3 v1, vec3 v2);
float barryCentricInterpolation(vec3 p1, vec3 p2, vec3 p3, vec2 pos);
float sinusoidal_lerp(float t0, float v0, float t1, float v1, float t);
float cosine_lerp(float t0, float v0, float t1, float v1, float t);

#endif