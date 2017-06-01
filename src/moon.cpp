#include <cmath>
#include <GL/glut.h>

#include "moon.h"
#include "constants.h"

// constructor for the moon
Moon::Moon(float distanceFromPlanet, float orbitTime, float rotationTime, float radius, GLuint textureHandle) {
	this->distanceFromPlanet = distanceFromPlanet;
	this->orbitTime = orbitTime;
	this->rotationTime = rotationTime;
	this->radius = radius;
	this->textureHandle = textureHandle;
}

// calculate the position of the moon
void Moon::calculatePosition(float time) {
	float angle = time * 3.1419f / orbitTime;

	position[0] = sin(angle) * distanceFromPlanet;
	position[1] = cos(angle) * distanceFromPlanet;
	position[2] = 0;

	rotation = time * 360 / rotationTime;
}

// render the moon
void Moon::render(void) {
	glPushMatrix();

	glBindTexture(GL_TEXTURE_2D, textureHandle);

	glTranslatef(position[0] * orbitScale, position[1] * orbitScale, position[2] * orbitScale);
	glRotatef(-rotation, 0.0f, 0.0f, 1.0f);

	GLUquadricObj* quadric = gluNewQuadric();
	gluQuadricTexture(quadric, true);
	gluQuadricNormals(quadric, GLU_SMOOTH);

	gluSphere(quadric, radius * radiusScale, 30, 30);

	glPopMatrix();
}

// render the orbit of the moon
void Moon::renderOrbit(void) {
	glBegin(GL_LINE_STRIP);

	for (float angle = 0.0f; angle < 6.283185307f; angle += 0.1f)
		glVertex3f(sin(angle) * distanceFromPlanet * orbitScale, cos(angle) * distanceFromPlanet * orbitScale, 0.0f);

	glVertex3f(0.0f, distanceFromPlanet * orbitScale, 0.0f);

	glEnd();
}
