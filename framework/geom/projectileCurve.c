#include "projectileCurve.h"

//Private function prototypes
static void setNormalsAndTangents(projectileCurve* p, float velX);
static void setFirstNormalAndTangent(projectileCurve* p, float velX);
static void setLastNormalAndTangent(projectileCurve* p, float velX);

projectileCurve genProjectileCurveParametric(const projectile* p, int nVertices) {
	//Create a new projectile curve object
	projectileCurve pc;
	//Initialize dynamic arrays
	pc.normals = new_vectorf();
	pc.tangents = new_vectorf();
	pc.points = new_vectorf();

	vec3 planeVector = new_vec3(p->vel0.x, 0.0f, p->vel0.z);
	//Angle of initial velocity from the horizontal plane
	float angle = vec_angle_between(vec_normalize(p->vel0), vec_normalize(planeVector));
	//Magnitude of velocity
	float velocMag = magnitude(&p->vel0);
	//The time value when the projectile reaches it's starting y value
	float endTime = (velocMag * 2.0f * (p->vel0.y / velocMag)) / GRAVITY_CONST;
	//Holds the current position of the projectile
	vec3 currPos = new_vec3(p->pos0.x, p->pos0.y, p->pos0.z);

	//Time handling variables
	float currTime = 0.0f;
	float time_interval = endTime / (nVertices - 1);

	//Iterate through the points calculating their positions
	for(unsigned int i = 0; i < nVertices - 1; i++) {
		//Set the vertex position
		push_back_vecf(pc.points, currPos.x);
		push_back_vecf(pc.points, currPos.y);
		push_back_vecf(pc.points, currPos.z);

		//Increment the time period
		currTime += time_interval;
		//Calculate the next vertex position
		currPos.x = p->pos0.x + p->vel0.x * currTime;
		currPos.y = p->pos0.y + velocMag * sinf(radians(angle)) * currTime - 4.9f * currTime * currTime;
		currPos.z = p->pos0.z + p->vel0.z * currTime;
	}

	//Calculate the final vertex position
	currPos.x = p->pos0.x + p->vel0.x * endTime;
	currPos.y = p->pos0.y;
	currPos.z = p->pos0.z + p->vel0.z * endTime;
	//Set the final vertex position
	push_back_vecf(pc.points, currPos.x);
	push_back_vecf(pc.points, currPos.y);
	push_back_vecf(pc.points, currPos.z);

	//Set normals and tangents
	setNormalsAndTangents(&pc, p->vel0.x);

	//Return projectile curve object
	return pc;
}

static void setFirstNormalAndTangent(projectileCurve* p, float velX) {
	//Get the current and next positions
	vec3 currPos = new_vec3(p->points->data[0], p->points->data[1], p->points->data[2]);
	vec3 nextPos = new_vec3(p->points->data[3], p->points->data[4], p->points->data[5]);

	//Calculate the tangent line
	vec3 tangent = vec_subtract(nextPos, currPos);
	//Calculate the normal using the tangent
	vec3 normal = cross_prod(new_vec3(0.0f, 0.0f, 1.0f), tangent);
	if (velX < 0.0f) normal = vec_negate(normal);
	//Normalize vectors
	normalize(&tangent);
	normalize(&normal);

	//Set normal
	push_back_vecf(p->normals, normal.x);
	push_back_vecf(p->normals, normal.y);
	push_back_vecf(p->normals, normal.z);
	//Set tangent
	push_back_vecf(p->tangents, tangent.x);
	push_back_vecf(p->tangents, tangent.y);
	push_back_vecf(p->tangents, tangent.z);
}

static void setLastNormalAndTangent(projectileCurve* p, float velX) {
	int nPoints = p->points->size;
	//Get the current and next positions
	vec3 currPos = new_vec3(p->points->data[nPoints - 3], p->points->data[nPoints - 2], p->points->data[nPoints - 1]);
	vec3 prevPos = new_vec3(p->points->data[nPoints - 6], p->points->data[nPoints - 5], p->points->data[nPoints - 4]);

	//Calculate the tangent line
	vec3 tangent = vec_subtract(currPos, prevPos);
	//Calculate the normal using the tangent
	vec3 normal = cross_prod(new_vec3(0.0f, 0.0f, 1.0f), tangent);
	if (velX < 0.0f) normal = vec_negate(normal);
	//Normalize vectors
	normalize(&tangent);
	normalize(&normal);

	//Set normal
	push_back_vecf(p->normals, normal.x);
	push_back_vecf(p->normals, normal.y);
	push_back_vecf(p->normals, normal.z);
	//Set tangent
	push_back_vecf(p->tangents, tangent.x);
	push_back_vecf(p->tangents, tangent.y);
	push_back_vecf(p->tangents, tangent.z);
}

static void setNormalsAndTangents(projectileCurve* p, float velX) {
	//Sets the first normal and tangent
	setFirstNormalAndTangent(p,velX);

	//Iterate through each of the points
	for (int i = 3; i < p->points->size - 3; i += 3) {
		//Get the previous and next vertex positions
		vec3 prevPos = new_vec3(p->points->data[i - 3], p->points->data[i - 2], p->points->data[i - 1]);
		vec3 nextPos = new_vec3(p->points->data[i + 3], p->points->data[i + 4], p->points->data[i + 5]);
		//Calculate the tangent line
		vec3 tangent = vec_subtract(nextPos, prevPos);
		//Calculate the normal using the tangent
		vec3 normal = cross_prod(new_vec3(0.0f, 0.0f, 1.0f), tangent);
		if (velX < 0.0f) normal = vec_negate(normal);
		//Normalize vectors
		normalize(&tangent);
		normalize(&normal);

		//Set normal
		push_back_vecf(p->normals, normal.x);
		push_back_vecf(p->normals, normal.y);
		push_back_vecf(p->normals, normal.z);
		//Set tangent
		push_back_vecf(p->tangents, tangent.x);
		push_back_vecf(p->tangents, tangent.y);
		push_back_vecf(p->tangents, tangent.z);
	}

	//Sets the final normal and tangent
	setLastNormalAndTangent(p, velX);
}

void drawProjectileCurve(projectileCurve* p) {
	//Save current state of program
	glPushAttrib(GL_LIGHTING_BIT | GL_CURRENT_BIT);

	//Set lighting and color
	glDisable(GL_LIGHTING);
	glColor3f(0.0f, 0.0f, 1.0f);

	//Enable the vertex array
	glEnableClientState(GL_VERTEX_ARRAY);
	//Add the points to the vertex array
	glVertexPointer(3, GL_FLOAT, 0, p->points->data);

	glPushMatrix();

	//Draw the points
	glDrawArrays(GL_LINE_STRIP, 0, p->points->size / 3);

	glPopMatrix();

	//Disable the vertex array
	glDisableClientState(GL_VERTEX_ARRAY);

	//Reset the state of the program
	glPopAttrib();
}

void destroyProjectileCurve(projectileCurve* p) {
	destroy_vectorf(p->normals);
	destroy_vectorf(p->points);
	destroy_vectorf(p->tangents);
}