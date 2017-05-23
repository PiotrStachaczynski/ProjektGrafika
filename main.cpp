#include <windows.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <glut.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include "Drone.h"
#include "Model_OBJ.h"
#include "BMPPIC.h"
#include "glm.h"
#include "Texture.h"
#define KEY_ESCAPE 27
#define PI 3.1415

// On mouse move
GLfloat xRot = 0.0f;
GLfloat yRot = 0.0f;
GLdouble xCam, xCam2, xCam3, xMove, ham = 0, poch1, poch2, yCam, zCam, angle = 0, curve = 0, xd = 0;
//FIZYKA INIT
GLdouble G = 0;
bool* keyStates = new bool[256];

void keyPressed(unsigned char key, int x, int y) {
	keyStates[key] = true;
}

void keyUp(unsigned char key, int x, int y) {
	keyStates[key] = false; // Set the state of the current key to not pressed  
}

void keyOperations(void)
{
	if (keyStates['w'])
	{
		zCam += cos(angle) * 4;
		xCam += sin(angle) * 4;
		ham = 1.5;
	}

	if (keyStates['s'])
	{
		zCam -= cos(angle) * 4;
		xCam -= sin(angle) * 4;
	}

	if (keyStates['a'])
	{
		angle += PI / 290;
		//xCam += sin(angle);
		xCam2 -= 1.5;
		xCam3 += 1.5;
	}

	if (keyStates['d'])
	{
		angle -= PI / 290;
		//xCam += sin(angle);
		xCam2 += 1.5;
		xCam3 -= 1.5;
	}

	if (keyStates[32])
	{
		G += 0.15;
	}

}

typedef struct {
	int width;
	int height;
	char* title;

	float field_of_view_angle;
	float z_near;
	float z_far;
} glutWindow;

Model_OBJ obj;
Model_OBJ obj2;
float g_rotation;
glutWindow win;

GLMmodel *plane;
GLMmodel *plane2;
GLMmodel *plane3;
GLMmodel *dron;
void Las() {
	if (!plane) {
		plane = glmReadOBJ("plane.obj");
		if (!plane) exit(0);
		glmFacetNormals(plane);
		glmVertexNormals(plane, 90.0);
	}
	glmDraw(plane, GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE, " Plane");
	glmDraw(plane, GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE, " Plane");
	glmDraw(plane, GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE, " Cube");
	glPushMatrix();
	glPopMatrix();

}

void Curve() {
	if (!plane2) {
		plane2 = glmReadOBJ("plate2obj.obj");
		if (!plane2) exit(0);
		glmFacetNormals(plane2);
		glmVertexNormals(plane2, 90.0);
	}
	glmDraw(plane2, GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE, " Plane");
	glmDraw(plane2, GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE, " Plane");
	glmDraw(plane2, GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE, " Cube");
	glPushMatrix();
	glPopMatrix();
}

void Curve2() {
	if (!plane3) {
		plane3 = glmReadOBJ("plate4.obj");
		if (!plane3) exit(0);
		glmFacetNormals(plane3);
		glmVertexNormals(plane3, 90.0);
	}
	glmDraw(plane3, GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE, " Plane");
	glmDraw(plane3, GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE, " Plane");
	glmDraw(plane3, GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE, " Cube");
	glPushMatrix();
	glPopMatrix();
}

void Dron() {
	if (!dron) {
		dron = glmReadOBJ("dron.obj");
		if (!dron) exit(0);
		glmFacetNormals(dron);
		glmVertexNormals(dron, 90.0);
	}
	glmDraw(dron, GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE, " Sphere");
	glmDraw(dron, GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE, " Cube");
	glPushMatrix();
	glPopMatrix();

}

void display()
{
	keyOperations();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(xCam * 3, yCam, zCam, xCam * 3, 0, zCam + 100, 0, 1, 0);
	glPushMatrix();
	glScalef(0.5, 0.5, 0.5);
	glTranslatef(0, 50, 0);
	//glRotatef(g_rotation, xRot, yRot, 0);
	//glRotatef(90, 0, 1, 0);
	glPopMatrix();

	glPushMatrix();

	glScalef(10, 10, 10);
	glRotatef(g_rotation, xRot, yRot, 0);
	//obj.Draw();
	glPopMatrix();

	glPushMatrix();
	glScalef(5, 5, 5);
	glTranslatef(0, -6, 30);
	glRotatef(90, 0, 1, 0);
	//obj2.Draw(1, 0, 0);
	Las();
	glPopMatrix();

	glPushMatrix();
	glScalef(5, 5, 5);
	glTranslatef(0, -6, 130);
	glRotatef(90, 0, 1, 0);
	//obj2.Draw(1, 0, 0);
	Las();
	glPopMatrix();

	glPushMatrix();
	glScalef(5, 5, 5);
	glTranslatef(0, -6, 230);
	glRotatef(90, 0, 1, 0);
	//obj2.Draw(1, 0, 0);
	Las();
	glPopMatrix();

	glPushMatrix();
	glScalef(5, 5, 5);
	glTranslatef(6, -6, 327);
	glRotatef(90, 0, 1, 0);
	//obj2.Draw(1, 0, 0);
	Curve();
	glPopMatrix();

	glPushMatrix();
	glScalef(5, 5, 5);
	glTranslatef(35, -6, 292);
	glRotatef(270, 0, 1, 0);
	//obj2.Draw(1, 0, 0);
	Curve2();
	glPopMatrix();

	glPushMatrix();
	glScalef(5, 5, 5);
	glTranslatef(33.8, -6, 391.5);
	glRotatef(90, 0, 1, 0);
	//obj2.Draw(1, 0, 0);
	Las();
	glPopMatrix();

	//glPushMatrix();
	//glScalef(5, 5, 5);
	//glTranslatef(13, -6, 370);
	//glRotatef(90, 0, 1, 0);
	////obj2.Draw(1, 0, 0);
	//Las2();
	//glPopMatrix();

	glPushMatrix();
	glScalef(3, 3, 3);
	glTranslatef(xCam, 0, zCam*0.335);
	glTranslatef(0, -4, 15);
	glRotatef(xCam3, 0, 1, 0);
	glRotatef(xCam2 * 2, 0, 0, 1);
	//glRotatef(90, 0, 1, 0);
	//obj2.Draw(1, 0, 0);
	Dron();
	glPopMatrix();
	glutSwapBuffers();

	G -= 0.035;
	if (xCam2 > 25)
	{
		xCam2 = 25;
	}

	if (xCam2 < -25)
	{
		xCam2 = -25;
	}

	if (xCam3 > 90)
	{
		xCam3 = 90;
	}

	if (xCam3 < -90)
	{
		xCam3 = -90;
	}

	if (G > 6)
	{
		G = 6;
	}

	if (!keyStates['w'])
	{
		zCam += ham;
		if (ham > 0)
		{
			ham = ham - 0.1;
		}
	}

	if (xCam2 != 0)
	{
		if (!keyStates['d'] && !keyStates['a'])
		{
			//angle -= PI / 180;
			if (xCam2 < 0)
			{
				xCam2 += 1.5;
			}
			if (xCam2 > 0)
			{
				xCam2 -= 1.5;
			}
			//xCam3 += sin(angle) * 7;
		}
	}
	//if (xCam3 != 0)
	//{
	//	if (!keyStates['d'] && !keyStates['a'])
	//	{
	//		//angle -= PI / 180;
	//		if (xCam3 < 0)
	//		{
	//			xCam3 += 1.5;
	//		}
	//		if (xCam3 > 0)
	//		{
	//			xCam3 -= 1.5;
	//		}
	//		//xCam3 += sin(angle) * 7;
	//	}
	//}

}

void initialize()
{
	glMatrixMode(GL_PROJECTION);
	glViewport(0, 0, win.width, win.height);
	GLfloat aspect = (GLfloat)win.width / win.height;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(win.field_of_view_angle, aspect, win.z_near, win.z_far);
	glMatrixMode(GL_MODELVIEW);
	glShadeModel(GL_SMOOTH);
	glClearColor(1.0f, 1.0f, 1.0f, 0.5f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	GLfloat amb_light[] = { 0.1, 0.1, 0.1, 1.0 };
	GLfloat diffuse[] = { 0.6, 0.6, 0.6, 1 };
	GLfloat specular[] = { 0.7, 0.7, 0.3, 1 };
	/*glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb_light);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glEnable(GL_LIGHT0);*/
	glEnable(GL_COLOR_MATERIAL);
	glShadeModel(GL_SMOOTH);
	//glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);
	//Jaskinia();
	//glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);
}

void keyboard(int key, int x, int y)
{
	switch (key) {
	case KEY_ESCAPE:
		exit(0);
		break;

	case GLUT_KEY_LEFT:
		//xCam -= 5;
		angle += PI / 80;
		xCam2 += 2.5;
		break;

	case GLUT_KEY_RIGHT:
		//xCam += 5;
		angle -= PI / 80;
		xCam2 -= 2.5;
		break;

	case GLUT_KEY_UP:
		zCam += cos(angle) * 5;
		xCam += sin(angle) * 5;
		poch2 -= 1.5;
		break;

	case GLUT_KEY_DOWN:
		zCam -= cos(angle) * 5;
		xCam -= sin(angle) * 5;
		break;

	case GLUT_KEY_PAGE_UP:
		G += 0.055;
		break;

	case GLUT_KEY_PAGE_DOWN:
		yCam -= 5;
		break;

	default:
		break;
	}
}

int main(int argc, char **argv)
{
	// set window values
	win.width = 800;
	win.height = 600;
	win.title = "Projekt Grafika";
	win.field_of_view_angle = 45;
	win.z_near = 1.0f;
	win.z_far = 2000.0f;
	// initialize and run program
	glutInit(&argc, argv);                                      // GLUT initialization
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);  // Display Mode
	glutInitWindowSize(win.width, win.height);					// set window size
	glutCreateWindow(win.title);								// create Window
	glutDisplayFunc(display);									// register Display Function
	glutIdleFunc(display);									// register Idle Function
	//glutKeyboardFunc(keyboard);								// register Keyboard Handler
	glutKeyboardFunc(keyPressed); // Tell GLUT to use the method "keyPressed" for key presses  
	glutKeyboardUpFunc(keyUp); // Tell GLUT to use the method "keyUp" for key up events  
	//glutSpecialFunc(keySpecial); // Tell GLUT to use the method "keySpecial" for special key presses  
	//glutSpecialUpFunc(keySpecialUp);
	initialize();
	glutMainLoop();
	//Fizyka 
	return 0;
}

