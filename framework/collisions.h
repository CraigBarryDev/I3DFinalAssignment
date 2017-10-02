#include "utils.h"
#include "plane.h"

#ifndef COLLISIONS_H
#define COLLISIONS_H

//Axis-Aligned Bounding Box
typedef struct {
	vec3 pos;
	vec3 size;
}AABB;

//Spherical Bounds Collision Detector
typedef struct {
	vec3 pos;
	float radius;
}SphericalCollider;


AABB new_collider_AABB(float x, float y, float z, float sizeX, float sizeY, float sizeZ);
bool colliding_AABB(const AABB* a, const AABB* b);

SphericalCollider new_collider_spherical(float x, float y, float z, float radius);
bool colliding_Spherical(const SphericalCollider* a, const SphericalCollider* b);

bool colliding_AABB_Spherical(const SphericalCollider* s, const AABB* a);

bool colliding_point_AABB_2D(vec2 pt, vec2 aabbMin, vec2 aabbMax);

#endif