#include "utils.h"
#include "texture.h"

#ifndef PARTICLES_H
#define PARTICLES_H

typedef struct {
	vec3 pos, color;
	vec3 pos0, pos1;
	vec3 color0, color1;
	float t0, t1;
}particle;

typedef struct {
	float alpha;
	vec3 pos, scale;
	vec3 pos0, pos1;
	vec3 scale0, scale1;
	texture tex;
	float t0, t1;
	float alpha0, alpha1;
}texturedParticle;

particle create_particle(vec3 pos0, vec3 pos1, vec3 color0, vec3 color1, float t0, float t1);
void animateParticle(particle* p, float t);

texturedParticle create_tex_particle(texture tex, vec3 pos0, vec3 pos1, vec3 scale0, vec3 scale1, float t0, float t1, float alpha0, float alpha1);
void animateTexParticle(texturedParticle* p, float t);
void renderTexParticle(texturedParticle* p, float camRotX, float camRotY);

#endif