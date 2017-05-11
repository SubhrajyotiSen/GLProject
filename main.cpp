#include <iostream>
#include <stdlib.h>
#include "imageloader.h"
#include "solarsystem.h"
#include <cmath>

#include <GL/glut.h>

using namespace std;

#define DEG2RAD 3.14/180

const float size = 10.0f;
GLUquadricObj *sphere = NULL;

float angle = 0;

int counterForEarth = 0;

SolarSystem solarSystem;

double pTime;
double timeSpeed;

void initRendering() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);


	glEnable(GL_COLOR_MATERIAL);

	Image* earth = new Image("Images/earth.bmp");
	Image* sun = new Image("Images/sun.bmp");
	Image* mercury = new Image("Images/mercury.bmp");
	Image* venus = new Image("Images/venus.bmp");
	Image* mars = new Image("Images/mars.bmp");
	

	solarSystem.addPlanet(0, 1, 500, 695500, sun->getTextureID()); // sun
	solarSystem.addPlanet(57910000, 88, 58.6, 2440, mercury->getTextureID()); // mercury
	solarSystem.addPlanet(108200000, 224.65, 243, 6052, venus->getTextureID()); // venus
	solarSystem.addPlanet(179600000, 365, 1, 6371, earth->getTextureID()); // earth
	solarSystem.addPlanet(227939100, 686, 1.03f, 3389, mars->getTextureID()); // mars

	pTime = 2.552f;
	timeSpeed = 0.1f;

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

	pTime += timeSpeed;

	solarSystem.calculatePositions(pTime);
	
	solarSystem.render();

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
	glutInitWindowSize(1280, 1080);

	glutCreateWindow("Solar System");
	initRendering();

	glutDisplayFunc(drawScene);
	glutReshapeFunc(handleResize);
	glutTimerFunc(25, update, 0);

	glutMainLoop();
	return 0;
}

