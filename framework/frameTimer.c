#include "frameTimer.h"

static bool timeUpdated = false;

int getFPS() {
	//Return the currFPS (Will stay the same for the entire second)
	return currFPS;
}

void printFPS() {
	int fps = getFPS();
	if(timeUpdated) printf("FPS: %d\n", fps);
}

float getFrameTime() {
	return frameTime;
}

float getTimeSec() {
	return glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
}

float getTimeMS() {
	return glutGet(GLUT_ELAPSED_TIME);
}

void updateFrameTime() {
	static float lastFrame = 0;
	frameTime = (glutGet(GLUT_ELAPSED_TIME) - lastFrame) / 1000.0f;
	lastFrame = (float)glutGet(GLUT_ELAPSED_TIME);

	static int framesThisSecond = 0;
	static int lastSecond = 0;

	//Updates the current time
	double currTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;

	//If a second has passed
	if ((int)currTime > lastSecond) {
		//Update the current FPS
		currFPS = framesThisSecond;
		//Reset the frame counter
		framesThisSecond = 0;

		//the last second 
		lastSecond = (int)currTime;
		timeUpdated = true;
	}
	else {
		//Update the frame counter
		framesThisSecond++;
		timeUpdated = false;
	}
}