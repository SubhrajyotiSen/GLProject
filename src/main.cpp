#include <cmath>
#include <cstdlib>
#include <GL/glut.h>
#include <stdlib.h>
#include <string.h>

#include "solarsystem.h"
#include "camera.h"
#include "imageloader.h"

int screenWidth, screenHeight;

Image *stars, * moon, *sunInfo, *mercuryInfo, *venusInfo, *earthInfo, *marsInfo, *jupiterInfo,
	*saturnInfo, *uranusInfo, *neptuneInfo;

bool showPlanetInfo = false;

bool showOrbits = true;

int planetSelected = 1;

bool blackHole = false;

SolarSystem solarSystem;

Camera camera;

double time;
double timeSpeed;

int flag;

bool isPlaying = false;

char str[100];

struct ControlStates {
	bool forward, backward, left, right, turnLeft, turnRight, lookUp,
		lookDown, tiltLeft, tiltRight;
} controls;

void timer(int) {
	if (blackHole) {
		solarSystem.startBlackHole(stars->getTextureID());
	}
	glutPostRedisplay(); 
	glutTimerFunc(10, timer, 0); 
}


float random(float max) {
	return (float)(std::rand() % 1000) * max * 0.001;
}


void addMoon() {
	solarSystem.addMoon(planetSelected,
		(500 + random(1500)) * solarSystem.getPlanetRadius(planetSelected),
		10 + random(100), 0.5 + random(20),
		solarSystem.getPlanetRadius(planetSelected) * (0.05f + random(0.2f)), moon->getTextureID());
}

void init(void) {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_TEXTURE_2D);

	glEnable(GL_LIGHTING);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	GLfloat matSpecular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat matAmbience[] = { 0.3, 0.3, 0.3, 1.0 };
	GLfloat matShininess[] = { 20.0 };
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glShadeModel (GL_SMOOTH);

	glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
	glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);
	glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbience);

	GLfloat lightAmbient[] = { 0.3, 0.3, 0.3, 1.0 };
	GLfloat lightDiffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat lightSpecular[] = { 1.0, 1.0, 1.0, 1.0 };

	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glDisable(GL_LIGHTING);

	sunInfo = new Image("../images/Sun.bmp");
	mercuryInfo = new Image("../images/Mercury.bmp");
	venusInfo = new Image("../images/Venus.bmp");
	earthInfo = new Image("../images/Earth.bmp");
	marsInfo = new Image("../images/Mars.bmp");
	jupiterInfo = new Image("../images/Jupiter.bmp");
	saturnInfo = new Image("../images/Saturn.bmp");
	uranusInfo = new Image("../images/Uranus.bmp");
	neptuneInfo = new Image("../images/Neptune.bmp");

	stars = new Image("../images/stars.bmp");
	moon = new Image("../images/moon.bmp");

	Image* sun = new Image("../images/sun.bmp");
	Image* mercury = new Image("../images/mercury.bmp");
	Image* venus = new Image("../images/venus.bmp");
	Image* earth = new Image("../images/earth.bmp");
	Image* mars = new Image("../images/mars.bmp");
	Image* jupiter = new Image("../images/jupiter.bmp");
	Image* saturn = new Image("../images/saturn.bmp");
	Image* uranus = new Image("../images/uranus.bmp");
	Image* neptune = new Image("../images/neptune.bmp");
	Image* pluto = new Image("../images/pluto.bmp");

	solarSystem.addPlanet(0, 1, 500, 695500, sun->getTextureID()); 
	solarSystem.addPlanet(57910000, 88, 58.6, 2440, mercury->getTextureID()); 
	solarSystem.addPlanet(108200000, 224.65, 243, 6052, venus->getTextureID()); 
	solarSystem.addPlanet(149600000, 365, 1, 6371, earth->getTextureID()); 
	solarSystem.addPlanet(227939100, 686, 1.03f, 3389, mars->getTextureID()); 
	solarSystem.addPlanet(778500000, 4332, 0.4139, 69911, jupiter->getTextureID()); 
	solarSystem.addPlanet(1433000000, 10759, 0.44375, 58232, saturn->getTextureID()); 
	solarSystem.addPlanet(2877000000, 30685, 0.718056, 25362, uranus->getTextureID()); 
	solarSystem.addPlanet(4503000000, 60188, 0.6713, 24622, neptune->getTextureID()); 
	solarSystem.addPlanet(5906380000, 90616, 6.39, 1137, pluto->getTextureID()); 

	solarSystem.addMoon(3, 7000000, 27.3, 27.3, 1738, moon->getTextureID()); 

	time = 2.552f;
	timeSpeed = 0.1f;
	
	controls.forward = false;
	controls.backward = false;
	controls.left = false;
	controls.right = false;
	controls.tiltRight = false;
	controls.tiltLeft = false;
	controls.lookDown = false;
	controls.lookUp = false;
	controls.turnLeft = false;
	controls.turnRight = false;

	timer(0);
}

void drawStarBox(void) {
	glBegin(GL_QUADS);
	
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f);	glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f);	glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f);	glVertex3f(-1.0f, 1.0f, 1.0f);
	
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f);	glVertex3f(1.0f, 1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f);	glVertex3f(1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f);	glVertex3f(1.0f, -1.0f, 1.0f);
	
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(1.0f, 1.0f, -1.0f);
	glTexCoord2f(1.0f, 0.0f);	glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f);	glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f);	glVertex3f(1.0f, -1.0f, -1.0f);
	
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 0.0f);	glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f);	glVertex3f(-1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f);	glVertex3f(-1.0f, 1.0f, -1.0f);
	
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2f(1.0f, 0.0f);	glVertex3f(1.0f, 1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f);	glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f);	glVertex3f(-1.0f, 1.0f, 1.0f);
	
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 0.0f);	glVertex3f(1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f);	glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f);	glVertex3f(-1.0f, -1.0f, 1.0f);

	glEnd();
}


void selectPlanet() {
	switch(planetSelected) {
		case 0: glBindTexture(GL_TEXTURE_2D, sunInfo->getTextureID());
				strcpy(str,"aplay ../audio/sun.wav &           ");
		break;
		case 1: glBindTexture(GL_TEXTURE_2D, mercuryInfo->getTextureID());
				strcpy(str,"aplay ../audio/mercury.wav &           ");
		break;
		case 2: glBindTexture(GL_TEXTURE_2D, venusInfo->getTextureID());
				strcpy(str,"aplay ../audio/venus.wav &           ");
		break;
		case 3: glBindTexture(GL_TEXTURE_2D, earthInfo->getTextureID());
				strcpy(str,"aplay ../audio/earth.wav &           ");
		break;
		case 4: glBindTexture(GL_TEXTURE_2D, marsInfo->getTextureID());
				strcpy(str,"aplay ../audio/mars.wav &           ");
		break;
		case 5: glBindTexture(GL_TEXTURE_2D, jupiterInfo->getTextureID());
				strcpy(str,"aplay ../audio/jupiter.wav &           ");
		break;
		case 6: glBindTexture(GL_TEXTURE_2D, saturnInfo->getTextureID());
				strcpy(str,"aplay ../audio/saturn.wav &           ");
		break;
		case 7: glBindTexture(GL_TEXTURE_2D, uranusInfo->getTextureID());
				strcpy(str,"aplay ../audio/uranus.wav &           ");
		break;
		case 8: glBindTexture(GL_TEXTURE_2D, neptuneInfo->getTextureID());
				strcpy(str,"aplay ../audio/neptune.wav &           ");
		break;

	}
}

void display() {
	
	time += timeSpeed;
	solarSystem.calculatePositions(time);

	if (controls.forward) camera.forward();		if (controls.backward) camera.backward();
	if (controls.left) camera.left();			if (controls.right) camera.right();
	if (controls.turnLeft) camera.turnLeft();		if (controls.turnRight) camera.turnRight();
	if (controls.tiltLeft) camera.tiltLeft();	if (controls.tiltRight) camera.tiltRight();
	if (controls.lookUp) camera.lookUp();		if (controls.lookDown) camera.lookDown();

	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);


	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(70.0f, (float)screenWidth / (float)screenHeight, 0.001f, 500.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	camera.setPosition();

	glBindTexture(GL_TEXTURE_2D, stars->getTextureID());
	drawStarBox();
	
	camera.translate();

	GLfloat lightPosition[] = { 0.0, 0.0, 0.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

	glEnable(GL_DEPTH_TEST);

	solarSystem.render();

	glDisable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (GLdouble) screenWidth, (GLdouble) screenHeight, 0.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	
	if (showPlanetInfo)
	{
		selectPlanet();
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 1.0f);	glVertex2f(400.0f, 200.0f);
			glTexCoord2f(0.0f, 0.0f);	glVertex2f(400.0f, 712.0f);
			glTexCoord2f(1.0f, 0.0f);	glVertex2f(912.0f, 712.0f);
			glTexCoord2f(1.0f, 1.0f);	glVertex2f(912.0f, 200.0f);
		glEnd();
		if(flag++==1) {
			system("pkill aplay");
			system(str);
			isPlaying = true;
		}
	}
	else {
		if(isPlaying){
			system("pkill aplay");
			isPlaying = false;
		}
	}	

	glFlush();
	glutSwapBuffers();
}

void keyDown(unsigned char key, int x, int y) {
	
	if (key > '0' && key <= '8')
	{
		float vec[3];
		solarSystem.getPlanetLocation(key - '0', vec);
		camera.pointAt(vec);

		planetSelected = key - '0';
		showPlanetInfo = !showPlanetInfo;
		if(!showPlanetInfo)
			flag = 0;
	}
	switch (key)
	{
	case '-':
		timeSpeed /= 2.0f; 
		break;
	case '=':
		timeSpeed *= 2.0f; 
		break;
	case ',':
		camera.slowDown(); 
		break;
	case '.':
		camera.speedUp(); 
		break;
	case 'w':
		controls.forward = true;
		break;
	case 's':
		controls.backward = true;
		break;
	case 'a':
		controls.left = true;
		break;
	case 'd':
		controls.right = true;
		break;
	case 'l':
		controls.tiltRight = true;
		break;
	case 'j':
		controls.tiltLeft = true;
		break;
	case 'i':
		controls.lookDown = true;
		break;
	case 'k':
		controls.lookUp = true;
		break;
	case 'q':
		controls.turnLeft = true;
		break;
	case 'e':
		controls.turnRight = true;
		break;
	case 27:
		exit(0);
		break;
	case 'b':
		blackHole = true;
		for (int i = 0; i < 7; ++i)
			camera.speedUp();
		
		for (int i=0; i< 200; i++)
			camera.backward();
		break;
	}

}

void keyUp(unsigned char key, int x, int y) {
	switch (key)
	{
	case 'w':
		controls.forward = false;
		break;
	case 's':
		controls.backward = false;
		break;
	case 'a':
		controls.left = false;
		break;
	case 'd':
		controls.right = false;
		break;
	case 'l':
		controls.tiltRight = false;
		break;
	case 'j':
		controls.tiltLeft = false;
		break;
	case 'i':
		controls.lookDown = false;
		break;
	case 'k':
		controls.lookUp = false;
		break;
	case 'q':
		controls.turnLeft = false;
		break;
	case 'e':
		controls.turnRight = false;
		break;
	}
}

void reshape(int w, int h) {
	screenWidth = w;
	screenHeight = h;
	glViewport (0, 0, (GLsizei) w, (GLsizei) h);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
	glutInitWindowSize(1200, 700);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyDown);
	glutKeyboardUpFunc(keyUp);
	glutFullScreen();
	glutMainLoop();
	return 0;
}
