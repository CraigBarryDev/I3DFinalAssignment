#include "main.h"

//Game stats
int lives = INITIAL_LIVES;
int score = INITIAL_SCORE;
int nCorpses = 0;
bool gameOver = false;

//Main initialization
void init(void) 
{
	//Put cursor to the middle of the screen
	glutWarpPointer(windowWidth / 2, windowHeight / 2);

	//Initialize game states
	glShadeModel(GL_SMOOTH);
	glEnable(GL_CULL_FACE);
	//glEnable(GL_LIGHT0); 
	glEnable(GL_LIGHT1); 
	glEnable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);

	//Initialize game objects
	loadTextures();
	initTerrains();
	initProceduralObjs();
	initSkybox();
	initCars();
	initLogs();	
	initFrog(); 
	initParticles();
	initCorpses();
}

//Update function called before each draw call to update program state
void update(void) 
{
	//Gameover occurs when lives left reaches 0
	gameOver = lives <= 0;

	//Only update if game is still running
	if(!gameOver) {
		//Handle key and mouse input
		handleInput();

		//Update the frog's positions
		updateFrogPos(frogInst, terr);
		handleFrogRibbit();

		//Move the camera to the frog's position
		moveCamThirdPerson(frogInst->model->pos);

		//Kill frog if its out of the bounds of the map, or update score
		//if it has reached the end zone
		killOutOfBoundsFrog(&lives, &score, &nCorpses);
		updateFrogScore(&score);

		//Move objects
		moveLogs();
		moveCars();

		//Handle any collisions
		handleCarCollisions(&lives, &score, &nCorpses);
		handleLogCollisions(&lives, &score, &nCorpses);
		handleWaterCollision(&lives, &score, &nCorpses);

		//Make the water flow
		updateWater();
	}

	//Update particles (let them finish their animation
	//even in the game over state)
	updateParticles();
	
}

//Called every frame to render objects but before the view transofrmation
//is done, useful for drawing HUD and other screen overlays
void preCameraDisplay(void) 
{
	dispHUD(score, lives);
	//If game lost, display game over on screen
	if(gameOver) {
		dispGameOver();
	}
}

//Called every frame to render objects before the buffers are swapped
void display(void)
{
	//Set environment lighting
	setLighting();
	//Display entities
	dispSkybox();
	dispTerrain();
	dispLogs();
	dispCars();
	dispFrog();
	dispRoad();
	dispUnderwaterTerr();
	dispWater();
	dispCorpses(nCorpses);
	//Display particles last as they disable the depth test
	dispParticles();
}

//Called when the application ends to deallocate memory
void cleanUp(void) 
{
	//If they exist, deallocate their memory
	if(logModel)			destroy_model(logModel);
	if(frogInst)			destroy_frog(frogInst);
	if(terr)				destroy_terrain(terr);
	if(road)				destroy_terrain(road);
	if(water)				destroy_terrain(water);
	if(underwaterTerr)		destroy_terrain(underwaterTerr);
	if(skyboxModel)			destroy_model(skyboxModel);
	if(frogCoords)			free(frogCoords);
	if(cylinderCoords)		free(cylinderCoords);
	if(cubeCoords)			free(cubeCoords);
	if(skyboxCoords)		free(skyboxCoords);

	//Destroy individual car models
	for(int i = 0; i < nCarModels; i++) {
		destroy_model(carModels[i]);
	}
}