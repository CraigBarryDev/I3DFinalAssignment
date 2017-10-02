#include "vectorMath.h"

vec2 new_vec2(float x, float y) {
	vec2 v;
	v.x = x;
	v.y = y;
	return v;
}

vec3 new_vec3(float x, float y, float z) {
	vec3 v;
	v.x = x;
	v.y = y;
	v.z = z;
	return v;
}

vec3 vec_negate(vec3 v) {
	//Negates all components of a vector
	v.x = -v.x;
	v.y = -v.y;
	v.z = -v.z;
	return v;
}
vec3 vec_add(vec3 v1, vec3 v2) {
	//Component-wise addition of two 3 dimensional vectors
	vec3 rv;
	rv.x = v1.x + v2.x;
	rv.y = v1.y + v2.y;
	rv.z = v1.z + v2.z;
	return rv;
}
vec3 vec_subtract(vec3 v1, vec3 v2) {
	//Component-wise subtraction of two 3 dimensional vectors
	vec3 rv;
	rv.x = v1.x - v2.x;
	rv.y = v1.y - v2.y;
	rv.z = v1.z - v2.z;
	return rv;
}

vec3 cross_prod(vec3 v1, vec3 v2) {
	//Calculates a vector that is parallel to both of the given vectors
	//with the direction given by the right hand rule (reverse the parameters
	//to get the corresponding opposite vector)
	vec3 cp;
	cp.x = v1.y * v2.z - v1.z * v2.y;
	cp.y = v1.z * v2.x - v1.x * v2.z;
	cp.z = v1.x * v2.y - v1.y * v2.x;
	return cp;
}

vec3 vec_normalize(vec3 v) {
	//Gets the magnitude of the vector
	float mag = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	//Divides each property by the magnitude, resluting in a unit vector
	//of the same directions
	v.x /= mag;
	v.y /= mag;
	v.z /= mag;
	//Return the normalized vector
	return v; 
}

void normalize(vec3* v) {
	//Gets the magnitude of the vector
	float mag = sqrt(v->x * v->x + v->y * v->y + v->z * v->z);
	//Divides each property by the magnitude, resluting in a unit vector
	//of the same directions
	v->x /= mag;
	v->y /= mag;
	v->z /= mag;
}

float magnitude(const vec3* v) {
	//Gets the magnitude of a vector
	return sqrt(v->x * v->x + v->y * v->y + v->z * v->z);
}

float dot_prod(vec3 v1, vec3 v2) {
	//Gets the scalar product of a vector
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

float vec_angle_between(vec3 v1, vec3 v2) {
	//Rearranges the traditional vector dot product to get cos(theta)
	//of the angle between the vectors
	float val = dot_prod(v1, v2) / (magnitude(&v1) * magnitude(&v2));
	//If floating point value precision causes the value to go slightly above 1, return 0 (as acos(1)= 0)
	if (val > 1.0f)
		return 0.0f;
	else
		//Otherwise return acos(theta) and convert to degrees
		//(57.2957795131 == 180/PI)
		return acos(val) * 57.2957795131;
}

vec3 vec_mult_scalar(vec3 v, float scalar) {
	//Component-wise multiplaction of a vector and a scalar
	return new_vec3(v.x * scalar, v.y * scalar, v.z * scalar);
}

vec3 getNormalFromPlane(vec3 p1, vec3 p2, vec3 p3) {
	//Gives a normal that comes from the front facing face of a plane
	//(Front face is determines by face with vertices in counter clockwise order)

	//Get the vectors that connect the points together, creating the plane
	vec3 a = vec_subtract(p2, p1);
	vec3 b = vec_subtract(p2, p3);
	vec3 c = vec_subtract(p3, p1);
	//Get the vectors that go from a corner to their opposing side's midpoint
	vec3 d = vec_subtract(vec_negate(b), vec_mult_scalar(c, 0.5f));
	vec3 e = vec_add(b, vec_mult_scalar(a, 0.5f));
	//Perform the cross-product of the two vectors, thereby retrieving the normal of the plane
	vec3 normal = cross_prod(d, e);
	//Normalize the normal vector
	normalize(&normal);
	//Return the normal from the plane
	return normal;
}

//Takes in a plane (p1,p2,p3 defines a plane) and then a 2D x,z position on the plane
//And works out out its height on the terrain by interpolating the heights of each corner of the plane
float barryCentricInterpolation(vec3 p1, vec3 p2, vec3 p3, vec2 pos) {
	float det = (p2.z - p3.z) * (p1.x - p3.x) + (p3.x - p2.x) * (p1.z - p3.z);
	float l1 = ((p2.z - p3.z) * (pos.x - p3.x) + (p3.x - p2.x) * (pos.y - p3.z)) / det;
	float l2 = ((p3.z - p1.z) * (pos.x - p3.x) + (p1.x - p3.x) * (pos.y - p3.z)) / det;
	float l3 = 1.0f - l1 - l2;
	return l1 * p1.y + l2 * p2.y + l3 * p3.y;
}

vec4 new_vec4(float x, float y, float z, float w) {
	vec4 v;
	v.x = x;
	v.y = y;
	v.z = z;
	v.w = w;
	return v;
}

float sinusoidal_lerp(float t0, float v0, float t1, float v1, float t) {
	//time range over which the lerp will occur
	float range = t1 - t0;
	//the current time offset from the start
	float dt = (t - t0);
	//the current time on a 0 to pi scale
	float dtx = (dt/range) * M_PI;

	//interoplate linearly over a sinusoidal animation curve
	//(that is to accelerate over a sine wave for more realistic movement)
	return v0 + (-cos(dtx)+1)/2.0f * (v1 - v0);
}

vec3 vec_sinusoidal_lerp(float t0, vec3 v0, float t1, vec3 v1, float t) {
	vec3 v;
	//Interpolate across each individual axis
	v.x = sinusoidal_lerp(t0, v0.x, t1, v1.x, t);
	v.y = sinusoidal_lerp(t0, v0.y, t1, v1.y, t);
	v.z = sinusoidal_lerp(t0, v0.z, t1, v1.z, t);
	//Return interoplated vector
	return v;
}

float cosine_lerp(float t0, float v0, float t1, float v1, float t) {
	//time range over which the lerp will occur
	float range = t1 - t0;
	//the current time offset from the start
	float dt = (t - t0);
	//the current time on a 0 to pi/2 scale
	float dtx = (dt/range) * M_PI/2.0f;

	//interoplate linearly over a sinusoidal animation curve
	//(that is to accelerate over a cosine wave for a sudden
	//acceleration followed by slow deceleration to end
	return v0 + sin(dtx) * (v1 - v0);
}

vec3 vec_cosine_lerp(float t0, vec3 v0, float t1, vec3 v1, float t) {
	vec3 v;
	//Interpolate across each individual axis
	v.x = cosine_lerp(t0, v0.x, t1, v1.x, t);
	v.y = cosine_lerp(t0, v0.y, t1, v1.y, t);
	v.z = cosine_lerp(t0, v0.z, t1, v1.z, t);
	//Return interoplated vector
	return v;
}

