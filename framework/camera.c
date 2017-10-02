#include "camera.h"
#include "keys.h"
#include "frameTimer.h"

float thirdPersonRX = 0.0f;
float thirdPersonRY = 0.0f;

void moveCamFirstPerson() {
	float t = getFrameTime();
	//Camera WASD controls
	if (isKeyPressed('w')) {
		camX += t * CAM_SPEED * (float)cos(radians(camRY + 90.0f));
		camY += t * CAM_SPEED * (float)sin(radians(camRX));
		camZ += t * CAM_SPEED * (float)sin(radians(camRY - 90.0f));
	}
	if (isKeyPressed('s')) {
		camX -= t * CAM_SPEED * (float)cos(radians(camRY + 90.0f));
		camY -= t * CAM_SPEED * (float)sin(radians(camRX));
		camZ -= t * CAM_SPEED * (float)sin(radians(camRY - 90.0f));
	}
	if (isKeyPressed('d')) {
		camZ += t * CAM_SPEED * (float)sin(radians(-camRY));
		camX += t * CAM_SPEED * (float)cos(radians(camRY));
	}
	if (isKeyPressed('a')) {
		camZ -= t * CAM_SPEED * (float)sin(radians(-camRY));
		camX -= t * CAM_SPEED * (float)cos(radians(camRY));
	}
	if (isKeyPressed('e')) {
		camY += t * CAM_SPEED;
	}
	if (isKeyPressed('q')) {
		camY -= t * CAM_SPEED;
	}
}

void rotateCamFirstPerson(int x, int y) {
	float MOUSE_SENSITIVTY = 15.0f;
	static bool warped = false;

	if (!warped) {
		int mouseMoveX = (windowWidth / 2) - x;
		int mouseMoveY = (windowHeight / 2) - y;

		camRX += (float)mouseMoveY * MOUSE_SENSITIVTY;
		camRY += (float)mouseMoveX * MOUSE_SENSITIVTY;

		//Stop over-rotation (flipping upside-down)
		if (camRX > 89.0f) camRX = 89.0f;
		if (camRX < -89.0f) camRX = -89.0f;

		warped = true;
		glutWarpPointer(windowWidth / 2, windowHeight / 2);
	}
	else {
		warped = false;
	}
}

void moveCamThirdPerson(vec3 pos) 
{
	//Clamps camera to a given position, with a viewing angle given by dist and rotations
	camX = (camDist * sinf(radians(thirdPersonRY)) * cosf(radians(-thirdPersonRX))) + pos.x;
	camY = (camDist * sinf(radians(-thirdPersonRX))) + pos.y;
	camZ = (camDist * cosf(radians(thirdPersonRY)) * cosf(radians(-thirdPersonRX))) + pos.z;
	camRY = thirdPersonRY;
	camRX = thirdPersonRX;
}

void rotateCamThirdPerson(int x, int y) {
	float MOUSE_SENSITIVTY = 0.035f;
	static bool warped = false;

	if (!warped) {
		int mouseMoveX = (windowWidth / 2) - x;
		int mouseMoveY = (windowHeight / 2) - y;

		thirdPersonRX += (float)mouseMoveY * MOUSE_SENSITIVTY;
		thirdPersonRY += (float)mouseMoveX * MOUSE_SENSITIVTY;

		//Stop over-rotation (flipping upside-down)
		//if (thirdPersonRX > 1.0f) thirdPersonRX = 1.0f;
		if (thirdPersonRX > 89.0f) thirdPersonRX = 89.0f;
		if (thirdPersonRX < -89.0f) thirdPersonRX = -89.0f;

		warped = true;
		glutWarpPointer(windowWidth / 2, windowHeight / 2);
	}
	else {
		warped = false;
	}
}

void zoomCam(int y) {
	float MOUSE_SENSITIVTY = 0.035f;
	static bool warped = false;

	if (!warped) {
		int mouseMoveY = (windowHeight / 2) - y;

		camDist -= (float)mouseMoveY * MOUSE_SENSITIVTY;

		if(camDist < 1.0f) camDist = 1.0f;
		if(camDist > 15.0f) camDist = 15.0f;

		warped = true;
		glutWarpPointer(windowWidth / 2, windowHeight / 2);
	}
	else {
		warped = false;
	}
}

void setCamDist(float dist) {
	camDist = dist;
}

void setCamRot(float rotX, float rotY) {
	camRX = rotX;
	camRY = rotY;

	//Keep and third person changes aswell
	thirdPersonRX = rotX;
	thirdPersonRY = rotY;
}

void setCamPos(float x, float y, float z) {
	camX = x;
	camY = y;
	camZ = z;
}

const float getCamRotX() { return camRX; }
const float getCamRotY() { return camRY; }
const float getCamPosX() { return camX; }
const float getCamPosY() { return camY; }
const float getCamPosZ() { return camZ; }