#include "mouse.h"

void mouseButtonsHandler(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		leftMousePressed = true;
		leftMouseDown = true;
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		rightMousePressed = true;
		rightMouseDown = true;
	}
	else if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) {
		middleMousePressed = true;
		middleMouseDown = true;
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)  {
		leftMousePressed = false;
		leftMouseUp = true;
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP) {
		rightMousePressed = false;
		rightMouseUp = true;
	}
	else if (button == GLUT_MIDDLE_BUTTON && state == GLUT_UP) {
		middleMousePressed = false;
		middleMouseUp = true;
	}
}

void resetMouseEvents() {
	leftMouseDown = false;
	rightMouseDown = false;
	middleMouseDown = false;

	leftMouseUp = false;
	rightMouseUp = false;
	middleMouseUp = false;

	mouseMoveX = 0;
	mouseMoveY = 0;
}

const bool isRightMousePressed() {
	return rightMousePressed;
}
const bool isLeftMousePressed() {
	return leftMousePressed;
}
const bool isMiddleMousePressed() {
	return middleMousePressed;
}
const bool onRightMouseUp() {
	return rightMouseUp;
}
const bool onLeftMouseUp() {
	return leftMouseUp;
}
const bool onMiddleMouseUp() {
	return middleMouseUp;
}
const bool onRightMouseDown() {
	return rightMouseDown;
}
const bool onLeftMouseDown() {
	return leftMouseDown;
}
const bool onMiddleMouseDown() {
	return middleMouseDown;
}
const int getMouseX() {
	return mouseX;
}
const int getMouseY() {
	return mouseY;
}

void mouseMoveHandler(int x, int y) {
	mouseX = x;
	mouseY = y;

	if(firstPersonCamEnabled)
		rotateCamFirstPerson(x, y);
	else if(thirdPersonCamEnabled)
		rotateCamThirdPerson(x, y);
	else if(zoomCamEnabled)
		zoomCam(y);

}

const int getMouseMoveX() {
	return mouseMoveX;
}
const int getMouseMoveY() {
	return mouseMoveY;
}

void mouseDragHandler(int x, int y) {
	mouseMoveHandler(x, y);
}

void toggleFirstPersonCam() {
	firstPersonCamEnabled = !firstPersonCamEnabled;
}

void toggleThirdPersonCam() {
	thirdPersonCamEnabled = !thirdPersonCamEnabled;
}

void toggleZoomCam() {
	zoomCamEnabled = !zoomCamEnabled;
}

void enableFirstPersonCam() {
	firstPersonCamEnabled = true;
}

void enableThirdPersonCam() {
	thirdPersonCamEnabled = true;
}

void enableZoomCam() {
	zoomCamEnabled = true;
}

void disableFirstPersonCam() {
	firstPersonCamEnabled = false;
}

void disableThirdPersonCam() {
	thirdPersonCamEnabled = false;
}

void disableZoomCam() {
	zoomCamEnabled = false;
}

void setMouse(int mouseX, int mouseY) {
	mouseWarped = true;
	glutWarpPointer(mouseX, mouseY);
}

void hideMouse() {
	cursorHidden = true;
	glutSetCursor(GLUT_CURSOR_NONE);
}

void unhideMouse() {
	cursorHidden = false;
	glutSetCursor(GLUT_CURSOR_INHERIT);
}

void toggleHideMouse() {
	cursorHidden ? unhideMouse() : hideMouse();
}