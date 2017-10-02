#include "collisions.h"

typedef enum  {
	 TOP_PLANE = 0,
	 BOTTOM_PLANE = 1,
	 RIGHT_PLANE = 2,
	 LEFT_PLANE = 3,
	 NEAR_PLANE = 4,
	 FAR_PLANE = 5
}AABB_PLANES;

AABB new_collider_AABB(float x, float y, float z, float sizeX, float sizeY, float sizeZ) {
	AABB aabb;
	aabb.pos.x = x;
	aabb.pos.y = y;
	aabb.pos.z = z;
	aabb.size.x = sizeX;
	aabb.size.y = sizeY;
	aabb.size.z = sizeZ;
	return aabb;
}

bool colliding_AABB(const AABB* a, const AABB* b) {
	const float aHalfSizeX = a->size.x / 2.0f;
	const float aHalfSizeY = a->size.y / 2.0f;
	const float aHalfSizeZ = a->size.z / 2.0f;
	const float bHalfSizeX = b->size.x / 2.0f;
	const float bHalfSizeY = b->size.y / 2.0f;
	const float bHalfSizeZ = b->size.z / 2.0f;
	
	//Check for overlapping axes
	if ((a->pos.x - aHalfSizeX <= b->pos.x + bHalfSizeX &&
		a->pos.x + aHalfSizeX >= b->pos.x - bHalfSizeX) &&
		(a->pos.y - aHalfSizeY <= b->pos.y + bHalfSizeY &&
		a->pos.y + aHalfSizeY >= b->pos.y - bHalfSizeY) &&
		(a->pos.z - aHalfSizeZ <= b->pos.z + bHalfSizeZ &&
		a->pos.z + aHalfSizeZ >= b->pos.z - bHalfSizeZ)) {
		//If all of the axes overlap in each dimension then there is a collision,
		//between the bounding boxes
		return true;
	}
	//All of the axes aren't overlapping therefore there is no collision
	return false;
}

SphericalCollider new_collider_spherical(float x, float y, float z, float radius) {
	SphericalCollider sc;
	sc.pos.x = x;
	sc.pos.y = y;
	sc.pos.z = z;
	sc.radius = radius;
	return sc;
}

bool colliding_Spherical(const SphericalCollider* a, const SphericalCollider* b) {
	//Get the distance between the two positions
	vec3 pointVec = vec_subtract(a->pos, b->pos);
	//Get the distance between the two points
	float distBetweenPoints = magnitude(&pointVec);
	//Get the minimum distance before the points are considered colliding
	float minCollidingDistance = a->radius + b->radius;
	//Check if the minCollidingDistance is greater than the distance
	//between the points, then the points are considered to be colliding
	if (minCollidingDistance >= distBetweenPoints)
		return true;

	//Otherwise, the points are not colliding
	return false;
}

bool colliding_AABB_Spherical(const SphericalCollider* s, const AABB* a) {
	//The vector planes that represent the faces of the AABB
	plane planes[6];

	//Get a vector to each extreme point of the AABB
	vec3 farTopRight = vec_add(a->pos, vec_mult_scalar(a->size, 0.5f));
	vec3 farBottomRight = vec_subtract(farTopRight, new_vec3(0.0f, a->size.y, 0.0f));
	vec3 farTopLeft = vec_subtract(farTopRight, new_vec3(a->size.x, 0.0f, 0.0f));
	vec3 farBottomLeft = vec_subtract(farTopRight, new_vec3(a->size.x, a->size.y, 0.0f));
	vec3 nearTopRight = vec_subtract(farTopRight, new_vec3(0.0f, 0.0f, a->size.z));
	vec3 nearBottomRight = vec_subtract(nearTopRight, new_vec3(0.0f, a->size.y, 0.0f));
	vec3 nearTopLeft = vec_subtract(nearTopRight, new_vec3(a->size.x, 0.0f, 0.0f));
	vec3 nearBottomLeft = vec_subtract(nearTopRight, new_vec3(a->size.x, a->size.y, 0.0f));

	//Create a plane for each face of the AABB
	planes[TOP_PLANE] = create_plane(farTopLeft, nearTopLeft, nearTopRight);
	planes[BOTTOM_PLANE] = create_plane(farBottomRight, nearBottomRight, nearBottomLeft);
	planes[LEFT_PLANE] = create_plane(farBottomLeft, nearBottomLeft, nearTopLeft);
	planes[RIGHT_PLANE] = create_plane(farBottomRight, nearTopRight, nearBottomRight);
	planes[NEAR_PLANE] = create_plane(nearBottomRight, nearTopRight, nearTopLeft);
	planes[FAR_PLANE] = create_plane(farBottomLeft, farTopLeft, farTopRight);


	//Iterate over each plane of the AABB
	for (int i = 0; i < 6; i++) {
		//Get the distance from the plane to the spherical collider
		const float distance = distFromPlane(planes[i], s->pos);
		//if the distance minus the sphere's radius is negative,
		//then no part of the sphere is behind this plane, therefore
		//the sphere is not colliding with the AABB
		if (distance < -s->radius) {
			return false;
		}
	}
	//There sphere is somewhat behind all faces of the collider,
	//therefore it must be colliding with the AABB
	return true;
}

bool colliding_point_AABB_2D(vec2 pt, vec2 aabbMin, vec2 aabbMax) {
	//Check for overlapping axes
	if (pt.x <= aabbMax.x &&
		pt.x >= aabbMin.x &&
		pt.y <= aabbMax.y &&
		pt.y >= aabbMin.y) {
		//If all of the axes overlap in each dimension then there is a collision,
		//between the bounding boxes
		return true;
	}
	return false;
}