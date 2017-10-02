#include "frog.h"

void init_frog_positions(frog* f) {
	int i = 0;
	//Initialize frogs initial position
	f->initPos.rotations[i++] = new_vec3(0.0f, -90.0f, 0.0f);
	f->initPos.rotations[i++] = new_vec3(165.0f, -10.0f, 0.0f);
	f->initPos.rotations[i++] = new_vec3(-140.0f, -10.0f, 0.0f);
	f->initPos.rotations[i++] = new_vec3(155.0f, -5.0f, 0.0f);

	f->initPos.rotations[i++] = new_vec3(180.0f, 10.0f, 0.0f);
	f->initPos.rotations[i++] = new_vec3(180.0f, 0.0f, 0.0f);
	f->initPos.rotations[i++] = new_vec3(180.0f, -10.0f, 0.0f);

	f->initPos.rotations[i++] = new_vec3(165.0f, 10.0f, 0.0f);
	f->initPos.rotations[i++] = new_vec3(-140.0f, 10.0f, 0.0f);
	f->initPos.rotations[i++] = new_vec3(155.0f, 5.0f, 0.0f);

	f->initPos.rotations[i++] = new_vec3(180.0f, 10.0f, 0.0f);
	f->initPos.rotations[i++] = new_vec3(180.0f, 0.0f, 0.0f);
	f->initPos.rotations[i++] = new_vec3(180.0f, -10.0f, 0.0f);

	f->initPos.rotations[i++] = new_vec3(-32.0f, 5.0f, 0.0f);
	f->initPos.rotations[i++] = new_vec3(-120.0f, 5.0f, 0.0f);
	f->initPos.rotations[i++] = new_vec3(155.0f, 0.0f, 0.0f);

	f->initPos.rotations[i++] = new_vec3(0.0f, 10.0f, 0.0f);
	f->initPos.rotations[i++] = new_vec3(0.0f, 0.0f, 0.0f);
	f->initPos.rotations[i++] = new_vec3(0.0f, -10.0f, 0.0f);

	f->initPos.rotations[i++] = new_vec3(-32.0f, -5.0f, 0.0f); 
	f->initPos.rotations[i++] = new_vec3(-120.0f, -5.0f, 0.0f); 
	f->initPos.rotations[i++] = new_vec3(155.0f, 0.0f, 0.0f);

	f->initPos.rotations[i++] = new_vec3(0.0f, 10.0f, 0.0f);
	f->initPos.rotations[i++] = new_vec3(0.0f, 0.0f, 0.0f);
	f->initPos.rotations[i++] = new_vec3(0.0f, -10.0f, 0.0f);

	f->initPos.rotations[i++] = new_vec3(0.0f, 0.0f, 0.0f);
	f->initPos.rotations[i++] = new_vec3(0.0f, 0.0f, 0.0f); 
	f->initPos.rotations[i++] = new_vec3(0.0f, 0.0f, 0.0f); 
	f->initPos.rotations[i++] = new_vec3(0.0f, 0.0f, 0.0f); 
	f->initPos.rotations[i++] = new_vec3(0.0f, 0.0f, 0.0f); 
	f->initPos.rotations[i++] = new_vec3(4.0f, 0.0f, 0.0f); 
	f->initPos.rotations[i++] = new_vec3(-4.0f, 0.0f, 0.0f);

	i = 0;
	//Initialize frog's jump position
	f->jumpPos.rotations[i++] = new_vec3(15.0f, -90.0f, 0.0f);
	f->jumpPos.rotations[i++] = new_vec3(60.0f, -10.0f, 0.0f);
	f->jumpPos.rotations[i++] = new_vec3(-60.0f, -10.0f, 0.0f);
	f->jumpPos.rotations[i++] = new_vec3(30.0f, -5.0f, 0.0f);
	f->jumpPos.rotations[i++] = new_vec3(180.0f, 10.0f, 0.0f);
	f->jumpPos.rotations[i++] = new_vec3(180.0f, 0.0f, 0.0f);
	f->jumpPos.rotations[i++] = new_vec3(180.0f, -10.0f, 0.0f);
	f->jumpPos.rotations[i++] = new_vec3(60.0f, 10.0f, 0.0f);
	f->jumpPos.rotations[i++] = new_vec3(-60.0f, 10.0f, 0.0f);
	f->jumpPos.rotations[i++] = new_vec3(30.0f, 5.0f, 0.0f);
	f->jumpPos.rotations[i++] = new_vec3(180.0f, 10.0f, 0.0f);
	f->jumpPos.rotations[i++] = new_vec3(180.0f, 0.0f, 0.0f);
	f->jumpPos.rotations[i++] = new_vec3(180.0f, -10.0f, 0.0f);
	f->jumpPos.rotations[i++] = new_vec3(-12.0f, 5.0f, 0.0f);
	f->jumpPos.rotations[i++] = new_vec3(-30.0f, 5.0f, 0.0f);
	f->jumpPos.rotations[i++] = new_vec3(155.0f, 0.0f, 0.0f);
	f->jumpPos.rotations[i++] = new_vec3(-30.0f, 10.0f, 0.0f);
	f->jumpPos.rotations[i++] = new_vec3(-30.0f, 0.0f, 0.0f);
	f->jumpPos.rotations[i++] = new_vec3(-30.0f, -10.0f, 0.0f);
	f->jumpPos.rotations[i++] = new_vec3(-12.0f, -5.0f, 0.0f); 
	f->jumpPos.rotations[i++] = new_vec3(-30.0f, -5.0f, 0.0f); 
	f->jumpPos.rotations[i++] = new_vec3(155.0f, 0.0f, 0.0f);
	f->jumpPos.rotations[i++] = new_vec3(-30.0f, 10.0f, 0.0f);
	f->jumpPos.rotations[i++] = new_vec3(-30.0f, 0.0f, 0.0f);
	f->jumpPos.rotations[i++] = new_vec3(-30.0f, -10.0f, 0.0f);
	f->jumpPos.rotations[i++] = new_vec3(25.0f, 0.0f, 0.0f);
	f->jumpPos.rotations[i++] = new_vec3(0.0f, 0.0f, 0.0f); 
	f->jumpPos.rotations[i++] = new_vec3(0.0f, 0.0f, 0.0f); 
	f->jumpPos.rotations[i++] = new_vec3(0.0f, 0.0f, 0.0f); 
	f->jumpPos.rotations[i++] = new_vec3(0.0f, 0.0f, 0.0f); 
	f->jumpPos.rotations[i++] = new_vec3(12.0f, 0.0f, 0.0f); 
	f->jumpPos.rotations[i++] = new_vec3(-12.0f, 0.0f, 0.0f);

	//Initialize frog's ribbit position
	f->ribbitPos = f->initPos;
	f->ribbitPos.rotations[mouth_top] = new_vec3(30.0f, 0.0f, 0.0f);
	f->ribbitPos.rotations[mouth_bottom] = new_vec3(-30.0f, 0.0f, 0.0f);
}

void init_frog_parts(frog* f) {
	treeNode* nodes[N_FROG_PARTS];
	//Use two iterators as windows gcc iterates q first but linux gcc iterates p first, therefore
	//two variables must be used to work on both windows and linux
	FROG_PART p = 0, q = 0;
	f->frogPartsList[p++] = (frogPart){q++, new_vec3(-0.35f, 0.55f, 0.0f), new_vec3(0.5f, 0.4f, 0.75f), new_vec3(0.0f, 0.7f, 0.0f)}; //body
	f->frogPartsList[p++] = (frogPart){q++, new_vec3(-0.25f, 0.0f, 0.05f), new_vec3(0.24f, 0.3f, -0.6f), new_vec3(0.0f, 0.6f, 0.0f)}; //tl_leg
	f->frogPartsList[p++] = (frogPart){q++, new_vec3(0.0f, 0.0f, 0.6f), new_vec3(0.2f, 0.2f, -0.5f), new_vec3(0.0f, 0.5f, 0.0f)}; //ml_leg
	f->frogPartsList[p++] = (frogPart){q++, new_vec3(0.0f, 0.0f, 0.5f), new_vec3(0.18f, 0.18f, -0.2f), new_vec3(0.0f, 0.4f, 0.0f)}; //bl_leg
	f->frogPartsList[p++] = (frogPart){q++, new_vec3(-0.05f, 0.09f, 0.11f), new_vec3(0.05f, 0.02f, 0.2f), new_vec3(0.0f, 0.3f, 0.0f) }; //l_leg_l_toe
	f->frogPartsList[p++] = (frogPart){q++, new_vec3(0.0f, 0.09f, 0.11f), new_vec3(0.05f, 0.02f, 0.2f), new_vec3(0.0f, 0.3f, 0.0f) }; //l_leg_m_toe
	f->frogPartsList[p++] = (frogPart){q++, new_vec3(0.05f, 0.09f, 0.11f), new_vec3(0.05f, 0.02f, 0.2f), new_vec3(0.0f, 0.3f, 0.0f) }; //l_leg_r_toe
	f->frogPartsList[p++] = (frogPart){q++, new_vec3(0.25f, 0.0f, 0.05f), new_vec3(0.24f, 0.3f, -0.6f), new_vec3(0.0f, 0.6f, 0.0f)}; //tr_leg
	f->frogPartsList[p++] = (frogPart){q++, new_vec3(0.0f, 0.0f, 0.6f), new_vec3(0.2f, 0.2f, -0.5f), new_vec3(0.0f, 0.5f, 0.0f)}; //mr_leg
	f->frogPartsList[p++] = (frogPart){q++, new_vec3(0.0f, 0.0f, 0.5f), new_vec3(0.18f, 0.18f, -0.2f), new_vec3(0.0f, 0.4f, 0.0f)}; //br_leg
	f->frogPartsList[p++] = (frogPart){q++, new_vec3(-0.05f, 0.09f, 0.11f), new_vec3(0.05f, 0.02f, 0.2f), new_vec3(0.0f, 0.3f, 0.0f) }; //r_leg_l_toe
	f->frogPartsList[p++] = (frogPart){q++, new_vec3(0.0f, 0.09f, 0.11f), new_vec3(0.05f, 0.02f, 0.2f), new_vec3(0.0f, 0.3f, 0.0f) }; //r_leg_m_toe
	f->frogPartsList[p++] = (frogPart){q++, new_vec3(0.05f, 0.09f, 0.11f), new_vec3(0.05f, 0.02f, 0.2f), new_vec3(0.0f, 0.3f, 0.0f) }; //r_leg_r_toe
	f->frogPartsList[p++] = (frogPart){q++, new_vec3(-0.2f, -0.12f, -0.7f), new_vec3(0.13f, 0.13f, 0.3f), new_vec3(0.0f, 0.6f, 0.0f)}; //tl_arm
	f->frogPartsList[p++] = (frogPart){q++, new_vec3(0.0f, 0.0f, -0.3f), new_vec3(0.09f, 0.09f, 0.25f), new_vec3(0.0f, 0.5f, 0.0f)}; //ml_arm
	f->frogPartsList[p++] = (frogPart){q++, new_vec3(0.0f, 0.0f, -0.25f), new_vec3(0.11f, 0.11f, 0.10f), new_vec3(0.0f, 0.4f, 0.0f)}; //bl_arm
	f->frogPartsList[p++] = (frogPart){q++, new_vec3(-0.05f, -0.04f, -0.07f), new_vec3(0.05f, 0.02f, 0.1f), new_vec3(0.0f, 0.3f, 0.0f) }; //l_arm_l_toe
	f->frogPartsList[p++] = (frogPart){q++, new_vec3(0.0f, -0.04f, -0.07f), new_vec3(0.05f, 0.02f, 0.1f), new_vec3(0.0f, 0.3f, 0.0f) }; //l_arm_m_toe
	f->frogPartsList[p++] = (frogPart){q++, new_vec3(0.05f, -0.04f, -0.07f), new_vec3(0.05f, 0.02f, 0.1f), new_vec3(0.0f, 0.3f, 0.0f) }; //l_arm_r_toe
	f->frogPartsList[p++] = (frogPart){q++, new_vec3(0.2f, -0.12f, -0.7f), new_vec3(0.13f, 0.13f, 0.3f), new_vec3(0.0f, 0.6f, 0.0f)}; //tr_arm
	f->frogPartsList[p++] = (frogPart){q++, new_vec3(0.0f, 0.0f, -0.3f), new_vec3(0.09f, 0.09f, 0.25f), new_vec3(0.0f, 0.5f, 0.0f)}; //mr_arm
	f->frogPartsList[p++] = (frogPart){q++, new_vec3(0.0f, 0.0f, -0.25f), new_vec3(0.11f, 0.11f, 0.10f), new_vec3(0.0f, 0.4f, 0.0f)}; //br_arm
	f->frogPartsList[p++] = (frogPart){q++, new_vec3(-0.05f, -0.04f, -0.07f), new_vec3(0.05f, 0.02f, 0.1f), new_vec3(0.0f, 0.3f, 0.0f) }; //r_arm_l_toe
	f->frogPartsList[p++] = (frogPart){q++, new_vec3(0.0f, -0.04f, -0.07f), new_vec3(0.05f, 0.02f, 0.1f), new_vec3(0.0f, 0.3f, 0.0f) }; //r_arm_m_toe
	f->frogPartsList[p++] = (frogPart){q++, new_vec3(0.05f, -0.04f, -0.07f), new_vec3(0.05f, 0.02f, 0.1f), new_vec3(0.0f, 0.3f, 0.0f) }; //r_arm_r_toe
	f->frogPartsList[p++] = (frogPart){q++, new_vec3(0.0f, 0.2f, -0.50f), new_vec3(0.45f,0.38f, 0.35f), new_vec3(0.0f, 0.6f, 0.0f)}; //head
	f->frogPartsList[p++] = (frogPart){q++, new_vec3(-0.21f, 0.19f, -0.21f), new_vec3(0.21f, 0.16f, 0.21f), new_vec3(1.0f, 1.0f, 1.0f)}; //l_eye
	f->frogPartsList[p++] = (frogPart){q++, new_vec3(0.0f, 0.0f, -0.01f), new_vec3(0.15f, 0.11f, 0.21f), new_vec3(0.0f, 0.0f, 0.0f)}; //l_eye_pupil
	f->frogPartsList[p++] = (frogPart){q++, new_vec3(0.21f, 0.19f, -0.21f), new_vec3(0.21f, 0.16f, 0.21f), new_vec3(1.0f, 1.0f, 1.0f)}; //r_eye
	f->frogPartsList[p++] = (frogPart){q++, new_vec3(0.0f, 0.0f, -0.01f), new_vec3(0.15f, 0.11f, 0.21f), new_vec3(0.0f, 0.0f, 0.0f)}; //r_eye_pupil
	f->frogPartsList[p++] = (frogPart){q++, new_vec3(0.0f, 0.0f, -0.35f), new_vec3(0.21f, 0.05f, 0.28f), new_vec3(0.0f, 0.7f, 0.0f)}; //t_mouth
	f->frogPartsList[p++] = (frogPart){q++, new_vec3(0.0f, 0.0f, -0.35f),  new_vec3(0.21f, 0.05f, 0.28f), new_vec3(0.0f, 0.7f, 0.0f)}; //b_mouth

	p = 0;
	f->frogParts = create_tree(&f->frogPartsList[body]);
	//Left Leg
	nodes[++p] = tree_add(f->frogParts->root, &f->frogPartsList[top_left_leg]);
	nodes[++p] = tree_add(nodes[top_left_leg], &f->frogPartsList[middle_left_leg]);
	nodes[++p] = tree_add(nodes[middle_left_leg], &f->frogPartsList[bottom_left_leg]);
	nodes[++p] = tree_add(nodes[bottom_left_leg], &f->frogPartsList[left_leg_left_toe]);
	nodes[++p] = tree_add(nodes[bottom_left_leg], &f->frogPartsList[left_leg_middle_toe]);
	nodes[++p] = tree_add(nodes[bottom_left_leg], &f->frogPartsList[left_leg_right_toe]);
	//Right leg
	nodes[++p] = tree_add(f->frogParts->root, &f->frogPartsList[top_right_leg]);
	nodes[++p] = tree_add(nodes[top_right_leg], &f->frogPartsList[middle_right_leg]);
	nodes[++p] = tree_add(nodes[middle_right_leg], &f->frogPartsList[bottom_right_leg]);
	nodes[++p] = tree_add(nodes[bottom_right_leg], &f->frogPartsList[right_leg_left_toe]);
	nodes[++p] = tree_add(nodes[bottom_right_leg], &f->frogPartsList[right_leg_middle_toe]);
	nodes[++p] = tree_add(nodes[bottom_right_leg], &f->frogPartsList[right_leg_right_toe]);
	//Left arm
	nodes[++p] = tree_add(f->frogParts->root, &f->frogPartsList[top_left_arm]);
	nodes[++p] = tree_add(nodes[top_left_arm], &f->frogPartsList[middle_left_arm]);
	nodes[++p] = tree_add(nodes[middle_left_arm], &f->frogPartsList[bottom_left_arm]);
	nodes[++p] = tree_add(nodes[bottom_left_arm], &f->frogPartsList[left_arm_left_toe]);
	nodes[++p] = tree_add(nodes[bottom_left_arm], &f->frogPartsList[left_arm_middle_toe]);
	nodes[++p] = tree_add(nodes[bottom_left_arm], &f->frogPartsList[left_arm_right_toe]);
	//Right arm
	nodes[++p] = tree_add(f->frogParts->root, &f->frogPartsList[top_right_arm]);
	nodes[++p] = tree_add(nodes[top_right_arm], &f->frogPartsList[middle_right_arm]);
	nodes[++p] = tree_add(nodes[middle_right_arm], &f->frogPartsList[bottom_right_arm]);
	nodes[++p] = tree_add(nodes[bottom_right_arm], &f->frogPartsList[right_arm_left_toe]);
	nodes[++p] = tree_add(nodes[bottom_right_arm], &f->frogPartsList[right_arm_middle_toe]);
	nodes[++p] = tree_add(nodes[bottom_right_arm], &f->frogPartsList[right_arm_right_toe]);
	//Head
	nodes[++p] = tree_add(f->frogParts->root, &f->frogPartsList[head]);
	nodes[++p] = tree_add(nodes[head], &f->frogPartsList[left_eye]);
	nodes[++p] = tree_add(nodes[left_eye], &f->frogPartsList[left_eye_pupil]);
	nodes[++p] = tree_add(nodes[head], &f->frogPartsList[right_eye]);
	nodes[++p] = tree_add(nodes[right_eye], &f->frogPartsList[right_eye_pupil]);
	nodes[++p] = tree_add(nodes[head], &f->frogPartsList[mouth_top]);
	nodes[++p] = tree_add(nodes[head], &f->frogPartsList[mouth_bottom]);

	frogPart* t = f->frogParts->root->data;
}

frog* create_frog(model* m) {
	//Allocate memory for frog
	frog* f = (frog*)malloc(sizeof(frog));

	//Set initial values
	f->model = m;
	f->isJumping = false;
	f->jumpSpeed = 1.0f;
	f->jumpAngle = 45.0f;
	f->nProjCurveVertices = 8;
	
	//Setup projectile motion
	f->proj = new_projectile(f->model->pos, new_vec3(0.0f, 0.0f, 0.0f));
	f->projCurve = genProjectileCurveParametric(&f->proj, f->nProjCurveVertices );

	//Setup frog collider
	f->collider = new_collider_spherical(0.0f, 0.0f, 0.0f, 0.05f);

	init_frog_parts(f);
	init_frog_positions(f);

	//Return frog object
	return f;
}

frogCorpse create_frog_corpse(frog* f) {
	//Create Corpse Object
	frogCorpse fc;

	//Set pointer to frog instance
	fc.frogInst = f;

	//If the pointer is a frog, then set
	//the values of the corpse obj
	if(f) {
		fc.pos = f->model->pos;
		fc.rot = f->model->rot;
		fc.scale = f->model->scale;
		fc.scale.y = CORPSE_SCALE_Y;
	}
	
	//Return corpse obj
	return fc;
}

void draw_frog_part_recursive(frog* f, treeNode* t) {
	frogPart* fp = (frogPart*)t->data;

	glPushMatrix();
	//Move to frog's position
	glTranslatef(fp->pos.x, fp->pos.y, fp->pos.z);

	float t0 = getTimeMS();

	//Set animation
	if(f->isRibbiting && t0 - f->ribbitStartTime < (f->ribbitEndTime - f->ribbitStartTime) * 2.0f) {
		//Interpolate between start and end of jump animation based on current time
		vec3 lerpV = vec_sinusoidal_lerp(f->ribbitStartTime, f->initPos.rotations[fp->part],
										f->ribbitEndTime, f->ribbitPos.rotations[fp->part], t0);
		glRotatef(lerpV.x, 1.0f, 0.0f, 0.0f);
	 	glRotatef(lerpV.y, 0.0f, 1.0f, 0.0f);
	 	glRotatef(lerpV.z, 0.0f, 0.0f, 1.0f);
	}else if(f->isJumping && t0 - f->jumpStartTime < (f->jumpEndTime - f->jumpStartTime) * 2.0f) {
		//Interpolate between start and end of jump animation based on current time
		vec3 lerpV = vec_sinusoidal_lerp(f->jumpStartTime, f->initPos.rotations[fp->part],
										f->jumpEndTime, f->jumpPos.rotations[fp->part], t0);
		glRotatef(lerpV.x, 1.0f, 0.0f, 0.0f);
	 	glRotatef(lerpV.y, 0.0f, 1.0f, 0.0f);
	 	glRotatef(lerpV.z, 0.0f, 0.0f, 1.0f);
	}else{
		//Sets initial position
		glRotatef(f->initPos.rotations[fp->part].x, 1.0f, 0.0f, 0.0f);
	 	glRotatef(f->initPos.rotations[fp->part].y, 0.0f, 1.0f, 0.0f);
	 	glRotatef(f->initPos.rotations[fp->part].z, 0.0f, 0.0f, 1.0f);
	}
	
	//Push matrix before scaling as scaling will affect
	//the next rotation which is undesirable
	glPushMatrix();
	glScalef(fp->scale.x, fp->scale.y, fp->scale.z);

	//Set color
	glColor3f(fp->color.x, fp->color.y, fp->color.z);
	float color[] = {fp->color.x, fp->color.y, fp->color.z, 0.0f};
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color);

	//Draw frog part
	render(f->model);
	//Remove scaling factor
	glPopMatrix();

	//Draw children parts recursively
	for(int i = 0; i < t->nChildren; i++) {
		treeNode* child = &t->children[i];
		draw_frog_part_recursive(f, child);
	}

	//Remove transformations in hierachy
	glPopMatrix();
}


void drawFrog(frog* f) {
	//render(f->model);
	glPushMatrix();
	
	//Perform inital transformations to frog's position
	glTranslatef(f->model->pos.x, f->model->pos.y, f->model->pos.z);
 	glRotatef(f->model->rot.x, 1.0f, 0.0f, 0.0f);
	glRotatef(f->model->rot.y, 0.0f, 1.0f, 0.0f);
	glRotatef(f->model->rot.z, 0.0f, 0.0f, 1.0f);
	glScalef(f->model->scale.x, f->model->scale.y, f->model->scale.z);

	//Start recursive draw of frog parts hierarchy tree
	draw_frog_part_recursive(f, f->frogParts->root);

	glPopMatrix();
}

void drawFrogCorpse(frogCorpse f) {
	//render(f->model);
	glPushMatrix();
	
	//Perform inital transformations to frog's position
	glTranslatef(f.pos.x, f.pos.y, f.pos.z);
 	glRotatef(f.rot.x, 1.0f, 0.0f, 0.0f);
	glRotatef(f.rot.y, 0.0f, 1.0f, 0.0f);
	glRotatef(f.rot.z, 0.0f, 0.0f, 1.0f);
	glScalef(f.scale.x, f.scale.y, f.scale.z);

	//Store whether the frog was jumping or not
	bool isJumping = f.frogInst->isJumping;
	//Set the frog to not jumping (to force initial animation)
	f.frogInst->isJumping = false;

	//Start recursive draw of frog parts hierarchy tree
	draw_frog_part_recursive(f.frogInst, f.frogInst->frogParts->root);

	//Set whether the frog was jumping back to initial state
	f.frogInst->isJumping = isJumping;

	glPopMatrix();
}

void drawFrogProjCurve(frog* f) {
	//Generate the projectile curve (only update it while not jumping,
	//so the frog will follow the curve when jumping)
	if(!f->isJumping) f->projCurve = genProjectileCurveParametric(&f->proj, f->nProjCurveVertices);
	//Draw the projectile curve
	drawProjectileCurve(&f->projCurve);
}

void updateFrogPos(frog* f, terrain* t) {
	//If the frog is jumping
	if(f->isJumping) {
		//Increment projectile motion
		increment_proj_motion(&f->proj, getFrameTime());
		f->model->pos = f->proj.pos;

		float tHeight = getTerrainHeightAtPos(t, f->model->pos.x, f->model->pos.z);

		if (f->proj.pos.y < tHeight) {
			//Update position values
			f->proj.pos.y = tHeight;
			f->model->pos = f->proj.pos;

			//Stop frog jumping
			f->isJumping = false;
		}
	}

	//Convert positional and projectile data into initial projectile velocity
	f->proj.pos0 = f->model->pos;
	float x = f->jumpSpeed * cosf(radians(-f->model->rot.y)) * cosf(radians(f->jumpAngle));
	float y = f->jumpSpeed * sinf(radians(f->jumpAngle));
	float z = f->jumpSpeed * sinf(radians(-f->model->rot.y)) * cosf(radians(f->jumpAngle));
	f->proj.vel0 = new_vec3(x, y, z);
	//Update collider position
	f->collider.pos = f->model->pos;
}

void startFrogJump(frog* f) {
	//Only jump if the frog is currently not jumping
	if(!f->isJumping) {
		f->isRibbiting = false;
		f->isJumping = true;
		//Set initial points
		f->proj.vel = f->proj.vel0;
		f->proj.pos = f->model->pos;
		f->jumpStartTime = getTimeMS();

		float endTime = (magnitude(&f->proj.vel0) * 2.0f * (f->proj.vel0.y /   
			magnitude(&f->proj.vel0))) / GRAVITY_CONST;
		f->jumpEndTime = f->jumpStartTime + (endTime*500.0f);
	}
}

void frogRibbit(frog* f) {
	//Make sure the frog is not jumping
	if(!f->isJumping) {
		//Set ribbiting animation to true
		f->isRibbiting = true;
		f->ribbitStartTime = getTimeMS();
		f->ribbitEndTime = getTimeMS() + 200.0f;
	}
}

void destroy_frog(frog* f) {
	destroy_tree(f->frogParts);
	//Destroy data allocated by the frog model
	destroy_model(f->model);
	//Free data allocated for the frog object
	free(f);
}