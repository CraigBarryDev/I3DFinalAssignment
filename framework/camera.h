#include "utils.h"

#ifndef CAMERA_H
#define CAMERA_H

static float CAM_SPEED = 2.5f;
static float camX = 0.0f;
static float camY = 0.0f;
static float camZ = 0.0f;
static float camRX = 0.0f;
static float camRY = 0.0f;
static float camDist = 2.5f;

void moveCamFirstPerson();
void moveCamThirdPerson(vec3 pos) ;

void rotateCamFirstPerson(int x, int y);
void rotateCamThirdPerson(int x, int y);
void zoomCam(int y);

void toggleFirstPersonCam();
void toggleThirdPersonCam();

void setCamRot(float rotX, float rotY);
void setCamPos(float x, float y, float z);
void setCamDist(float dist);

const float getCamRotX();
const float getCamRotY();
const float getCamPosX();
const float getCamPosY();
const float getCamPosZ();

#endif