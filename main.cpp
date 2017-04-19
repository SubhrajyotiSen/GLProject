#include <iostream>
#include <stdlib.h>
#include "imageloader.h"
#include <cmath>

#include <GL/glut.h>

using namespace std;

#define DEG2RAD 3.14/180

const float size = 10.0f;
#define M_PI	(3.14159265)
GLUquadricObj *sphere = NULL;

float angle = 0;

int counterForEarth = 0;

Image* earth;

void initRendering() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);


	glEnable(GL_COLOR_MATERIAL);

	earth = new Image("Images/earth.bmp");
	sphere = gluNewQuadric();
}

void handleResize(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (float)w / (float)h, 1.0, 200.0);
}

void drawScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Revolution
	glBegin(GL_POINTS); 
	for (int i=0; i < 360; i++) 
	{ 
		float degInRad = i*DEG2RAD; 
		glVertex3f(cos(degInRad)*6.0, sin(degInRad)*2.3,0.0f);
	} 
	glEnd(); 
	if(counterForEarth>359) 
	counterForEarth = 0;
	else counterForEarth++;
	float xForEarth = cos(counterForEarth*DEG2RAD)*6.0f;
	float yForEarth = sin(counterForEarth*DEG2RAD)*2.3f;
	glPushMatrix(); 
	glTranslatef(xForEarth,yForEarth,-16.0f);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, earth->getTextureID());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Rotation
	glRotatef(90,1.0f,0.0f,0.0f);
	glRotatef(angle,0.0f,0.0f,1.0f);
	gluQuadricTexture(sphere,1);
	gluSphere(sphere,4,20,20);

	// Swap buffers since double buffers are used
	glutSwapBuffers();
}

void update(int value) {
	angle += 1.5f;
	if (angle > 360) {
		angle -= 360;
	}

	glutPostRedisplay();
	glutTimerFunc(25, update, 0);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(400, 400);

	glutCreateWindow("Solar System");
	initRendering();

	glutDisplayFunc(drawScene);
	glutReshapeFunc(handleResize);
	glutTimerFunc(25, update, 0);

	glutMainLoop();
	return 0;
}

