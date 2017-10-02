#include "utils.h"

#ifndef PLANE_H
#define PLANE_H

typedef struct {
	vec3 normal, point;
	float d;
}plane;

//Creates a plane structure
plane create_plane(vec3 v1, vec3 v2, vec3 v3);
//Gets the distance from a plane
float distFromPlane(plane pl, vec3 pt);

#endif
