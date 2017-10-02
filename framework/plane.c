#include "plane.h"

//Creates a plane structure
plane create_plane(vec3 v1, vec3 v2, vec3 v3) {
	plane p;
	//Temporary vectors
	vec3 a1, a2;

	//Get vectors from v2 to other points
	a1 = vec_subtract(v1, v2);
	a2 = vec_subtract(v3, v2);
	//Calculate the plane normal from the cross product of these points
	p.normal = vec_normalize(cross_prod(a2, a1));

	//Calculate dot product of plane
	p.d = -dot_prod(p.normal, v2);

	return p;
}

//Gets the distance of a point from a plane
float distFromPlane(plane pl, vec3 pt) {
	return pl.d + dot_prod(pl.normal, pt);
}