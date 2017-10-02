#include "projectileMotion.h"

projectile new_projectile(vec3 pos, vec3 vel) {
	projectile p = { pos, vel, pos, vel };
	return p;
}

void increment_proj_motion(projectile* p, float deltaTime) {
	//Update the values of based on their current velocity multipled
	//by the amount of time that has passed
	p->pos.x += p->vel.x * deltaTime;
	p->pos.y += p->vel.y * deltaTime;
	p->pos.z += p->vel.z * deltaTime;
	
	//Updates the Y velocity to account for gravity
	//Gravity will constantly force the projectile downwards
	p->vel.y += -GRAVITY_CONST * deltaTime;
}