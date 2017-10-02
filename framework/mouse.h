#include "utils.h"

#ifndef MOUSE_H
#define MOUSE_H

#include "camera.h"

static int mouseX = 0;
static int mouseY = 0;

static bool cursorHidden = false;

static bool leftMousePressed = false;
static bool middleMousePressed = false;
static bool rightMousePressed = false;

static bool leftMouseDown = false;
static bool middleMouseDown = false;
static bool rightMouseDown;

static bool leftMouseUp = false;
static bool middleMouseUp = false;
static bool rightMouseUp = false;

static bool mouseWarped = false;

static bool firstPersonCamEnabled = false;
static bool thirdPersonCamEnabled = false;
static bool zoomCamEnabled = false;

static int mouseMoveX = 0;
static int mouseMoveY = 0;

void mouseButtonsHandler(int button, int state, int x, int y);
void mouseMoveHandler(int x, int y);
void mouseDragHandler(int x, int y);
void resetMouseEvents();

void setMouse(int mouseX, int mouseY);

void hideMouse();
void unhideMouse();
void toggleHideMouse();

void enableFirstPersonCam();
void enableThirdPersonCam();
void enableZoomCam();

void disableFirstPersonCam();
void disableThirdPersonCam();
void disableZoomCam();

void toggleFirstPersonCam();
void toggleThirdPersonCam();
void toggleZoomCam();

const int getMouseX();
const int getMouseY();

const bool isRightMousePressed();
const bool isLeftMousePressed();
const bool isMiddleMousePressed();
const bool onRightMouseUp();
const bool onLeftMouseUp();
const bool onMiddleMouseUp();
const bool onRightMouseDown();
const bool onLeftMouseDown();
const bool onMiddleMouseDown();


#endif