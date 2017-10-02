#include "particles.h"


particle create_particle(vec3 pos0, vec3 pos1, vec3 color0, vec3 color1, float t0, float t1) {
	particle p;
	//Set particle attributes
	p.pos0 = pos0;
	p.pos1 = pos1;
	p.color0 = color0;
	p.color1 = color1;
	p.t0 = t0;
	p.t1 = t1;
	p.pos = pos0;
	p.color = color0;
	//Return particle object
	return p;
}

void animateParticle(particle* p, float t) {
	p->color = vec_cosine_lerp(p->t0, p->color0, p->t1, p->color1, t);
	p->pos = vec_cosine_lerp(p->t0, p->pos0, p->t1, p->pos1, t);
}

texturedParticle create_tex_particle(texture tex, vec3 pos0, vec3 pos1, vec3 scale0, vec3 scale1, float t0, float t1, float alpha0, float alpha1) {
	texturedParticle p;
	//Set particle attributes
	p.pos0 = pos0;
	p.pos1 = pos1;
	p.scale0 = scale0;
	p.scale1 = scale1;
	p.t0 = t0;
	p.t1 = t1;
	p.pos = pos0;
	p.scale = scale0;
	p.tex = tex;
	p.alpha0 = alpha0;
	p.alpha1 = alpha1;
	p.alpha = alpha0;
	//Return particle object
	return p;
}

void animateTexParticle(texturedParticle* p, float t) {
	p->pos = vec_cosine_lerp(p->t0, p->pos0, p->t1, p->pos1, t);
	p->scale = vec_cosine_lerp(p->t0, p->scale0, p->t1, p->scale1, t);
	p->alpha = cosine_lerp(p->t0, p->alpha0, p->t1, p->alpha1, t);
}

static float vertices[] = {
	-1.0f, 1.0f, 0.0f,
	-1.0f, -1.0f, 0.0f,
	1.0f, -1.0f, 0.0f,
	1.0f, 1.0f, 0.0f
};

static float texCoords[] = {
	0.0f, 0.0f,
	0.0f, 1.0f,
	1.0f, 1.0f,
	1.0f, 0.0f 
};

void renderTexParticle(texturedParticle* p, float camRotX, float camRotY) {
	glPushMatrix();
	//Set transformations
	glTranslatef(p->pos.x, p->pos.y, p->pos.z);

	//Set color
	GLfloat color[] = {1.0f, 1.0f, 1.0f, p->alpha};
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color);
	glColor4f(1.0f, 1.0f, 1.0f, p->alpha);

	//Reverse the view transformation
	glRotatef(camRotY, 0.0f, 1.0f, 0.0f);
	glRotatef(camRotX, 1.0f, 0.0f, 0.0f);
	
	//Set particle scale
	glScalef(p->scale.x, p->scale.y, p->scale.z);

	//Bind texture
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, p->tex);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_DEPTH_TEST);

	//Set texture coordinates
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, 0, texCoords);
	//Sets the models vertices to the VAO
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, &vertices[0]);

	//Draws particle
	glDrawArrays(GL_QUADS, 0, 4);

	//Disable client state
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);

	//Unbind Texture
	glBindTexture(GL_TEXTURE_2D, 0);

	glPopMatrix();
}