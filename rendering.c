#include "rendering.h"
#include "main.h"

void renderBitmapString(float x,float y, char* text) {  
	//Sets the matrix mode to deal with projection
	glMatrixMode(GL_PROJECTION);

	//Save current projection matrix
	glPushMatrix();
	//Loads the identity matrix
	glLoadIdentity();
	//Set orthographic matrix of screen coordinates
	glOrtho(0.0f, windowWidth, windowHeight, 0.0f, -1.0f, 1.0f);
	
	char *c;
	//Set rendering position (in screen coordinates)
	glRasterPos3f(x, y, 0.0f);
	//Iterate through characters in string
	for (c=text; *c != '\0'; c++) {
		//Print each character to screen
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
	}

	//Remove orthographic matrix and return to projection
	glPopMatrix();
	//Sets the matrix mode back to dealing with model matrices
	glMatrixMode(GL_MODELVIEW);
}

void toggleWireframeRendering() {
	renderWireframes = !renderWireframes;
	if (renderWireframes)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void setLighting()
{
	//Lighting variables
	GLfloat lightPos[] = { 1.0f, 1.0f, 1.0f, 0.0f };
	GLfloat lightPos2[] = { -1.0f, 1.0f, 0.0f, 0.0f };
	GLfloat lightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat lightDiffuse[] = { 1.8f, 1.8f, 1.8f, 1.0f };
	GLfloat lightAmbient[] = { 0.2f, 0.2f, 0.2f, 1.0f };

	GLfloat frogPos[] = { frogInst->model->pos.x, frogInst->model->pos.y + 4.75f, frogInst->model->pos.z, 1.0f };
	GLfloat lightPointSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat lightPointDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat lightPointAmbient[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	//Set light variables
	glLightfv(GL_LIGHT0, GL_POSITION, frogPos);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightPointAmbient);
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightPointDiffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightPointSpecular);
	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1.0f);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.00f);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.02f);

	glLightfv(GL_LIGHT1, GL_POSITION, lightPos);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDiffuse);
	glLightfv(GL_LIGHT1, GL_AMBIENT, lightAmbient);
}

void setColor(float red, float green, float blue)
{
	float color[] = {red, green, blue};
	glColor3f(red, green, blue);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color);
}