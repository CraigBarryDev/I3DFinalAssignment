#include "utils.h"

#ifndef PROJECTILE_MOTION_H
#define PROJECTILE_MOTION_H

#define GRAVITY_CONST 9.8f

typedef struct {
	vec3 pos0;
	vec3 vel0;
	vec3 pos;
	vec3 vel;
}projectile;

projectile new_projectile(vec3 pos, vec3 vel);

void increment_proj_motion(projectile* p, float deltaTime);

#endif