#include "glGraphics.h"

int main(int argc, char **argv)
{
	time_t t;
	//Seed random numbers
	srand((unsigned int)time(&t));

	//Initialize OpenGL
	initGL(argc, argv);

	return EXIT_SUCCESS;
}

static void initGlut(int argc, char** argv) {
	//Initializes GLUT
	glutInit(&argc, argv);

	//Sets parameters for glut window
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(windowWidth, windowHeight);
	glutInitWindowPosition(100, 100);
	//Creates window
	windowID = glutCreateWindow("GLUT Window");

	//Setup the projection matrix
	setupProjection();
}

static void windowResize(int width, int height) {
	//Updates the size of the window
	windowWidth = width;
	windowHeight = height;
	//Resets the projection matrix with appropriate aspect ratios
	setupProjection();

	//Sets the rendering area of the window to the entire window
	glViewport(0, 0, windowWidth, windowHeight);
}

static void setupProjection() {
	//Sets the matrix mode to deal with projection
	glMatrixMode(GL_PROJECTION);
	
	//Loads the identity matrix
	glLoadIdentity();
	//Sets a perspective matrix with 45.0f fov
	gluPerspective(45.0f, (float)windowWidth / (float)windowHeight, 0.1f, 100.0f);

	//Sets the matrix mode back to dealing with model matrices
	glMatrixMode(GL_MODELVIEW);
}

static void updateCamera() {
	//Push view matrix
	glPushMatrix();
	//Set matrix to the identity matrix
	glLoadIdentity();

	//Set the camera position/rotation
	glRotatef(-getCamRotX(), 1.0f, 0.0f, 0.0f);
	glRotatef(-getCamRotY(), 0.0f, 1.0f, 0.0f);
	glTranslatef(-getCamPosX(), -getCamPosY(), -getCamPosZ());
}

static void glUpdate(void) {
	GLenum err;
	//Print OpenGL errors
    while ((err = glGetError()) != GL_NO_ERROR) {
        printf("OpenGL error: %s\n");
	}

	//If Escape pressed, end application
	if (onKeyUp(27)) {
		glClose();
		return;
	}

	//Updates the frame timer
	updateFrameTime();

	//Call main update function
	update();

	//Forces the display to update
	glutPostRedisplay();

	//Reset key up and key down events
	resetKeyEvents();
	//Reset mouse up and mouse down events
	resetMouseEvents();
}

static void glClose() {
	//Calls user function to cleanup any allocated memory
	cleanUp();
	//Destroys the window
	glutDestroyWindow(windowID);
}

static void glDisplay(void) {
	//Clear color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Call main pre-view transformation drawing
	preCameraDisplay();

	//Set view matrix
	updateCamera();

	//Call main display function
	display();

	//Pop view matrix
	glPopMatrix();

	//Swap buffers
	glutSwapBuffers();
}

void initGL(int argc, char** argv) {
	initGlut(argc, argv);

	//Sets clear color to black
	glClearColor(0.0, 0.7, 0.7, 0.0);

	initKeyboard();

	glEnable(GL_DEPTH_TEST);

	//Set glut callbacks
	glutDisplayFunc(glDisplay);
	glutIdleFunc(glUpdate);
	glutReshapeFunc(windowResize);
	//Set glut user input callbacks
	glutPassiveMotionFunc(mouseMoveHandler);
	glutKeyboardFunc(keyDownHandler);
	glutKeyboardUpFunc(keyUpHandler);
	glutSpecialFunc(specialKeysHandler);
	glutSpecialUpFunc(specialKeyUpHandler);
	glutMouseFunc(mouseButtonsHandler);
	glutMotionFunc(mouseDragHandler);

	//Calls user defined init function
	init();

	//Starts the rendering loop
	glutMainLoop();
}