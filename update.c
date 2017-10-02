#include "main.h"

void resetGame(int* lives, int* score, int* nCorpses) {
	*lives = INITIAL_LIVES;
	*score = INITIAL_SCORE;
	*nCorpses = 0;
}

void resetFrog() {
	frogInst->isJumping = false;
	frogInst->model->pos = new_vec3(FROG_STARTING_POS);
	frogInst->model->rot = new_vec3(FROG_STARTING_ROT);
	frogInst->jumpSpeed = FROG_INITIAL_JUMP_SPEED;
	setCamRot(STARTING_CAMERA_ANGLE);
}

void createCorpse(int* nCorpses) {
	//Add a corpse to the list of corpses
	corpses[*nCorpses] = create_frog_corpse(frogInst);
	//Set corpse y position to on the terrain
	corpses[*nCorpses].pos.y = getTerrainHeightAtPos(terr, corpses[*nCorpses].pos.x, corpses[*nCorpses].pos.z) + 0.02f;
	//Increment the number of corpses
	(*nCorpses)++;
}

void killFrog(int* lives, int* score, int* nCorpses) {
	//Take one life for dying
	(*lives)--;
	
	//Don't reset frog is game finished
	if(*lives == 0)
		return;

	//Create an explosion at the frog's position
	explosion();
	createCorpse(nCorpses);

	//Debug option to auto-reset game
	#ifdef GAME_RESET
		//If player out of lives
		if(*lives <= 0) {
			//Reset the game
			resetGame(lives, score, nCorpses);	
		}
	#endif


	//Set frog's position/orientation
	resetFrog();
}

void killOutOfBoundsFrog(int* lives, int* score, int* nCorpses) {
	//If frog falls to death
	if(frogInst->model->pos.y < KILLZONE_Y)
		killFrog(lives, score, nCorpses);
}

float getLanePos(int nLanes, float planeSize, int* lane) {
	//Randomize which lane the model will be in
	*lane = randBetween(0, nLanes);
	//Split plane into number of lanes + 2 and middle points will define 
	//z positions of each lane
	return (float)((*lane + 1) / 2.0f) * (planeSize / (nLanes / 2.0f)) - (planeSize / 2.0f) - (planeSize / nLanes / 2.0f);
}

void moveX(model* m, float width, float* speed, int minSpeed, int maxSpeed, int nLanes, float planeSize, float* zPos) {
	//Move the model across the x axis with the speed value
	m->pos = new_vec3(m->pos.x + (*speed) * getFrameTime(), m->pos.y, m->pos.z);

	//If the model is over the end of the terrain
	if(m->pos.x > (terr->sizeX / 2.0f) + width ||
		m->pos.x < (-terr->sizeX / 2.0f) - width) {

		//Get a position in the lane
		//int lane = 0;
		//*zPos = getLanePos(nLanes, planeSize, &lane);

		//Alternate direction based on which lane the model is in
		if (randBetween(0, 2) == 0) {
			//Set position/speed (moving positive x)
			m->pos.x = (-terr->sizeX / 2.0f) - width;
			*speed = randBetweenf(minSpeed, maxSpeed);
		}
		else {
			//Set position/speed (moving negative x)
			m->pos.x = (terr->sizeX / 2.0f) + width;
			*speed = -randBetweenf(minSpeed, maxSpeed);
		}
	}
}

void moveLogs() {
	//Move logs across the terrain
	for(int i = 0; i < N_LOGS; i++) {
		logModel->pos = logPositions[i];
		//Update log's position
		moveX(logModel, LOG_LENGTH, &logSpeeds[i], MIN_LOG_SPEED, 
			MAX_LOG_SPEED, 4, WATER_SIZE_Z, &logModel->pos.z);
		logPositions[i] = logModel->pos;
	}
}

void moveCars() {
	//Move cars across the terrain
	for(int i = 0; i < N_CARS; i++) {
		carModels[0]->pos = carPositions[i];
		//Update car's position
		moveX(carModels[0], carCollider.size.x, &carSpeeds[i], 
			MIN_CAR_SPEED, MAX_CAR_SPEED, 4, ROAD_SIZE_Z, &carModels[0]->pos.z);
		carPositions[i] = carModels[0]->pos;
	}
}

void handleLogCollisions(int* lives, int* score, int* nCorpses) {
	//Check if frog is colliding with any logs
	for(int i = 0; i < N_LOGS; i++) {
		//If frog is on same x/z plane as log
		if(colliding_point_AABB_2D(new_vec2(frogInst->model->pos.x, frogInst->model->pos.z),
			new_vec2(logPositions[i].x - (LOG_HEIGHT * 2.0f), logPositions[i].z - (LOG_WIDTH * LOG_RADIUS)),
			new_vec2(logPositions[i].x + (LOG_HEIGHT * 2.0f), logPositions[i].z + (LOG_WIDTH * LOG_RADIUS)))) {
			//Z pos of frog relative to log
			float relZPos = logPositions[i].z - frogInst->model->pos.z;
			//Radius of the log
			float radius = LOG_RADIUS * LOG_WIDTH;
			//Height at which the frog should sit on the log (top of log at given z pos)
			float height = sqrt((radius*radius)-(relZPos*relZPos));

			//if frog is below the logs top position
			if(frogInst->model->pos.y < height + logPositions[i].y) {
				//Cancel any frog jumps
				frogInst->isJumping = false;

				//Set frog to log's pos, Minus small value to stop floating precision errors
				frogInst->model->pos.y = height + logPositions[i].y - 0.00002f;

				//Move across with the log
		 		moveX(frogInst->model, LOG_LENGTH, &logSpeeds[i], MIN_LOG_SPEED, MAX_LOG_SPEED,
					4, WATER_SIZE_Z, &frogInst->model->pos.z);

		 		//If the frog is carried off the terrain by the frog
		 		if(frogInst->model->pos.x > TERR_SIZE_X / 2.0f || 
		 			frogInst->model->pos.x < -TERR_SIZE_X / 2.0f) {
		 			//kill the frog
		 			killFrog(lives, score, nCorpses);
		 		}
			}
		}
	}
}

void handleCarCollisions(int* lives, int* score, int* nCorpses) {
	//Check for frog colliding with cars
	for(int i = 0; i < N_CARS; i++) {
		//Create AABB collider for car
		AABB cCollider = new_collider_AABB(carPositions[i].x, carPositions[i].y, 
			carPositions[i].z, carCollider.size.x, carCollider.size.y, carCollider.size.z);
		//Position collider in the middle of the car
		cCollider.pos = vec_add(carCollider.pos, cCollider.pos);

		//Check if the frog is colliding with the car
		if(colliding_AABB_Spherical(&frogInst->collider, &cCollider)) {
			//Kill the frog
			killFrog(lives, score, nCorpses);
		}
	}
}

void handleWaterCollision(int* lives, int* score, int* nCorpses) {
	vec2 frogPos = new_vec2(frogInst->model->pos.x, frogInst->model->pos.z);
	vec2 waterMin = new_vec2(water->pos.x - (WATER_SIZE_X / 2.0f), water->pos.z - (WATER_SIZE_Z / 2.0f));
	vec2 waterMax = new_vec2(water->pos.x + (WATER_SIZE_X / 2.0f), water->pos.z + (WATER_SIZE_Z / 2.0f));

	//If frog is on same x/z plane as the water
	if(colliding_point_AABB_2D(frogPos, waterMin, waterMax)) {
		//Z pos of frog relative to water
		float relZPos = frogInst->model->pos.z - water->pos.z;
		float relXPos = frogInst->model->pos.x - water->pos.x;
		//Height at which the frog should sit on the log (top of log at given z pos)
		float height = getTerrainHeightAtPos(water, relXPos, relZPos);

		//if frog is below the water
		if(frogInst->model->pos.y < height + water->pos.y) {
			//Kill the frog
			killFrog(lives, score, nCorpses);
		}

	}
}

void updateWater() {
	//Current time in seconds
	float t = getTimeSec();

	//Iterate through the vertices in the water
	for (int z = 0; z < water->nSquaresZ; z++) {
		for (int x = 0; x < water->nSquaresX; x++) {
			//Calculate the height of each vertex in the water
			float height = 0.15f * sin(x * 0.2f + t / 2.0f) * cos(z * 0.15 + t / 4.2f + 0.25f);
			//Set the height at each vectex in the water
			setTerrainHeightAtVertex(water, x, z, height);
		}
	}

	//Recalculate the water's normals after the height is changed
	updateNormals(water);
}

void updateFrogScore(int* score) {
	//If the frog has reached the end zone (past the water)
	//And the frog ins't jumping
	if(frogInst->model->pos.z < water->pos.z - WATER_SIZE_Z / 2.0f &&
		!frogInst->isJumping) {
		//Increment score
		(*score)++; 
		//Reset frog to start
		resetFrog();
	}
}

void explosion() {
	float t = getTimeMS();

	//Iterate throguh each particle
	for(int i = 0; i < N_PARTICLES; i++) {	
		//Randomize the particles end point
		vec3 endPos = new_vec3(randBetweenf(-3.0f, 3.0f), randBetweenf(-0.25f, 3.0f), randBetweenf(-3.0f, 3.0f));

		//Create the textured particle
		particles[i] = create_tex_particle(particleTexture, frogInst->model->pos, vec_add(endPos, frogInst->model->pos),
			new_vec3(PARTICLE_SCALE_START), new_vec3(PARTICLE_SCALE_END), t, t + randBetweenf(200.0f, 4000.0f), 1.0f, 0.0f);
	}
}

void updateParticles() {
	//Get curr time
	float t = getTimeMS();

	//Iterate through each particle
	for(int i = 0; i < N_PARTICLES; i++) {
		float t = getTimeMS();
		//If the particle still exists
		if(t < particles[i].t1) {
			//Animate the particle
			animateTexParticle(&particles[i], t);
		}
	}
}

void handleFrogRibbit() {
	static float t = 1000.0f;
	float currTime = getTimeMS();
	
	//If time for the frog to ribit
	if(currTime > t) {
		//Set the next time for the frog to ribbit
		t = getTimeMS() + randBetweenf(2000.0f, 3000.0f);
		//Make the frog ribbit
		frogRibbit(frogInst);
	}
}