#include "framework/model.h"
#include "framework/frameTimer.h"
#include "framework/geom/projectileCurve.h"
#include "framework/terrain.h"
#include "framework/collisions.h"
#include "framework/tree.h"

#ifndef FROG_H
#define FROG_H

#define N_FROG_PARTS 32
#define CORPSE_SCALE_Y 0.02f

typedef enum 
{
	body,
	top_left_leg,
	middle_left_leg,
	bottom_left_leg,
	left_leg_left_toe,
	left_leg_middle_toe,
	left_leg_right_toe,
	top_right_leg,
	middle_right_leg,
	bottom_right_leg,
	right_leg_left_toe,
	right_leg_middle_toe,
	right_leg_right_toe,
	top_left_arm,
	middle_left_arm,
	bottom_left_arm,
	left_arm_left_toe,
	left_arm_middle_toe,
	left_arm_right_toe,
	top_right_arm,
	middle_right_arm,
	bottom_right_arm,
	right_arm_left_toe,
	right_arm_middle_toe,
	right_arm_right_toe,
	head,
	left_eye,
	left_eye_pupil,
	right_eye,
	right_eye_pupil,
	mouth_top,
	mouth_bottom
}FROG_PART;

typedef struct 
{
	FROG_PART part;
	vec3 pos;
	vec3 scale;
	vec3 color;
}frogPart;

typedef struct 
{
	vec3 rotations[N_FROG_PARTS];
}frogPosition;

typedef struct
{
	model* model;
	tree* frogParts;
	frogPart frogPartsList[N_FROG_PARTS];

	frogPosition initPos;
	frogPosition jumpPos;
	frogPosition ribbitPos;

	bool isJumping;
	bool isRibbiting;

	float jumpSpeed;
	float jumpAngle;

	float jumpStartTime;
	float jumpEndTime;
	float ribbitStartTime;
	float ribbitEndTime;

	int nProjCurveVertices;

	projectile proj;
	projectileCurve projCurve;

	SphericalCollider collider;
}frog;

typedef struct 
{
	frog* frogInst;
	vec3 pos;
	vec3 rot;
	vec3 scale;
}frogCorpse;

frog* create_frog(model* m);
void destroy_frog(frog* f);

frogCorpse create_frog_corpse(frog* f);
void drawFrogCorpse(frogCorpse f);

void updateFrogPos(frog* f, terrain* t);
void startFrogJump(frog* f);

void frogRibbit(frog* f);

void drawFrog(frog* f);
void drawFrogProjCurve(frog* f) ;

#endif