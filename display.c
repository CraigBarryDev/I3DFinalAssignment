#include "main.h"

//Display Heads Up Display
void dispHUD(int score, int lives) {
	//Save current state of program
	glPushAttrib(GL_LIGHTING_BIT | GL_CURRENT_BIT);

	//Disable lighting
	glDisable(GL_LIGHTING);
	//Set HUD color
	setColor(HUD_COLOR);

	char scoreStr[512];
	char livesStr[512];
	char fpsStr[512];
	char ftimeStr[512];

	//Create strings to render
	sprintf(scoreStr, "Score: %d", score);
	sprintf(livesStr, "Lives: %d", lives);
	sprintf(fpsStr, "FPS: %d", getFPS());
	sprintf(ftimeStr, "Frame Time: %.0fms", getFrameTime() * 1000.0f);

	//Render strings
	renderBitmapString(10,22, scoreStr);
	renderBitmapString(10, 45, livesStr);
	renderBitmapString(10, 68, fpsStr);
	renderBitmapString(10, 91, ftimeStr);

	//Reset program states
	glPopAttrib();
}

void dispGameOver() {
	//Save current state of program
	glPushAttrib(GL_LIGHTING_BIT | GL_CURRENT_BIT);

	//Disable lighting
	glDisable(GL_LIGHTING);
	//Set HUD color
	setColor(HUD_COLOR);

	//Render game over string
	renderBitmapString(windowWidth / 2 - 57,windowHeight / 2 - 30, "GAME OVER");

	//Reset program states
	glPopAttrib();
}

void dispSkybox() {
	//Save current state of program
	glPushAttrib(GL_LIGHTING_BIT | GL_CURRENT_BIT);

	//Disable lighting and backface culling
	glDisable(GL_LIGHTING);
	glDisable(GL_CULL_FACE);

	setColor(SKYBOX_COLOR);
	render(skyboxModel);

	//Reset program states
	glPopAttrib();
}

void dispTerrain() {
	setColor(TERR_COLOR);
	render_terrain(terr);
}

void dispLogs() {
	setColor(LOG_COLOR);

	glPushMatrix();

	//Iterate through the logs
	for(int i = 0; i < N_LOGS; i++) {
		//Set log model to position
		logModel->pos = logPositions[i];
		//Draw log at position
		render(logModel);
	}

	glPopMatrix();
}

void dispCars() {
	//Save current state of program
	glPushAttrib(GL_LIGHTING_BIT | GL_CURRENT_BIT);

	//Enable transparency
	glEnable(GL_BLEND);
	//Blend using the alpha value, value will be the 1 minus the current
	//value of the pixel
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHT0);
	glColorMaterial(GL_FRONT, GL_DIFFUSE);

	GLfloat ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat specular[] = { 0.8f, 0.8f, 0.8f, 1.0f };
	GLfloat shininess = 25.0f;
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);

	//Iterate through the cars
	for(int i = 0; i < N_CARS; i++) {
		//Iterate through car's parts
		for(int j = 0; j < nCarModels; j++) {
			//Set car position
			carModels[j]->pos = carPositions[i];
			//Set car part's color
			glColor4f(carColors[j].x, carColors[j].y, carColors[j].z, carColors[j].w);

			//Flip car depending on the direction it is travelling
			if (carSpeeds[i] < 0.0f)
				carModels[j]->scale.z = minf(carModels[j]->scale.z, -carModels[j]->scale.z);
			else
				carModels[j]->scale.z = maxf(carModels[j]->scale.z, -carModels[j]->scale.z);

			//Render car part
			render(carModels[j]);
		}
	}

	//Disable transparency
	glDisable(GL_BLEND);
	glDisable(GL_LIGHT0);
	glDisable(GL_COLOR_MATERIAL);
	glPopAttrib();
}

void dispFrog() {
	glDisable(GL_LIGHTING);

	drawFrog(frogInst);

	glEnable(GL_LIGHTING);

	//Draw frog's projectile curve
	drawFrogProjCurve(frogInst);
}

void dispRoad() {
	//Save curr matrix pos
	glPushMatrix();

	//Set road color
	setColor(ROAD_COLOR);
	//Draw road
	render_terrain(road);

	//Reset matrix pos
	glPopMatrix();
}

void dispUnderwaterTerr() {
	//Save curr matrix pos
	glPushMatrix();

	//Set terr color
	setColor(UNDERWATER_TERR_COLOR);
	//Draw terr
	render_terrain(underwaterTerr);

	//Reset matrix pos
	glPopMatrix();
}

void dispWater() {
	GLfloat color[] = { WATER_COLOR };

	//Save curr matrix pos
	glPushMatrix();

	//Enable transparency
	glEnable(GL_BLEND);
	//Blend using the alpha value, value will be the 1 minus the current
	//value of the pixel
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//Set water's lighting values
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color);

	//Draw water
	render_terrain(water);

	//Disbale blending (transparency)
	glDisable(GL_BLEND);

	//Reset matrix pos
	glPopMatrix();
}

void dispParticles() {
	glPushMatrix();

	//Save current state of program
	glPushAttrib(GL_LIGHTING_BIT | GL_CURRENT_BIT);

	//Disable lighting and backface culling
	glDisable(GL_LIGHTING);
	glDisable(GL_CULL_FACE);

	float t = getTimeMS();

	//Iterate through each particle
	for(int i = 0; i < N_PARTICLES; i++) {
		if(t < particles[i].t1) {
			renderTexParticle(&particles[i], getCamRotX(), getCamRotY());
		}
	}

	//Reset program state
	glPopAttrib();

	glPopMatrix();
}

void dispCorpses(int nCorpses) {
	glDisable(GL_LIGHTING);

	//Iterate through corpses
	for(int i = 0; i < nCorpses; i++) {
		drawFrogCorpse(corpses[i]);
	}

	glEnable(GL_LIGHTING);
}