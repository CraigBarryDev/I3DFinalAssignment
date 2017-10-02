#include "input.h"
#include "main.h"

void handleKeys();
void handleMouse();

void handleInput() 
{
	//Handles key inputs
	handleKeys();
	//Handles mouse inputs
	handleMouse();
}

void handleKeys() {
	//Toggle wireframe
	if (onKeyDown('p')) toggleWireframeRendering();

	//Increase/descrease frog jump speed
	if(isKeyPressed('w')) frogInst->jumpSpeed += FROG_ANGLE_SPEED * getFrameTime();
	if(isKeyPressed('s')) frogInst->jumpSpeed -= FROG_ANGLE_SPEED * getFrameTime();
	if(frogInst->jumpSpeed > FROG_MAX_JUMP_SPEED) frogInst->jumpSpeed = FROG_MAX_JUMP_SPEED;
	if(frogInst->jumpSpeed < 0.0f) frogInst->jumpSpeed = 0.0f;

	//Increase/decrease frog jump angle
	if(isKeyPressed('a')) frogInst->jumpAngle += FROG_ROT_SPEED * getFrameTime();
	if(isKeyPressed('d')) frogInst->jumpAngle -= FROG_ROT_SPEED * getFrameTime();
	if(frogInst->jumpAngle > 90.0f) frogInst->jumpAngle = 90.0f;
	if(frogInst->jumpAngle < 0.0f) frogInst->jumpAngle = 0.0f;

	//Rotate frog
	if(isSpecialKeyPressed(SPECIAL_KEY_LEFT)) 
		frogInst->model->rot.y += FROG_ROT_ANGLE_SPEED * getFrameTime();
	if(isSpecialKeyPressed(SPECIAL_KEY_RIGHT)) 
		frogInst->model->rot.y -= FROG_ROT_ANGLE_SPEED * getFrameTime();

	//Make the frog jump by pressing spacebar
	if (isKeyPressed(32)) startFrogJump(frogInst);
}

void handleMouse() {
	//Move camera on left mouse down
	if (onLeftMouseDown()) {
		glutWarpPointer(windowWidth / 2, windowHeight / 2);
		enableThirdPersonCam();
	}
	//Stop moving camera on left mouse up
	if (onLeftMouseUp()) {
		glutWarpPointer(windowWidth / 2, windowHeight / 2); 
		disableThirdPersonCam();
	}

	//Zoom camera on right mouse down
	if (onRightMouseDown() && !isLeftMousePressed()) {
		glutWarpPointer(windowWidth / 2, windowHeight / 2);
		enableZoomCam();
		
	}
	//Stop zooming camera on left mouse down
	if (onRightMouseUp() && !isLeftMousePressed()) {
		glutWarpPointer(windowWidth / 2, windowHeight / 2); 
		disableZoomCam();
	}

	//Hide mouse if in any cam mode
	if(isLeftMousePressed() || isRightMousePressed()) {
		hideMouse();
	}else {
		unhideMouse();
	}
}