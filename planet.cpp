#include "planet.h"
#include "constants.h"

#include <GL/glut.h>
#include <cmath>

#include <stdio.h>

#define DEG2RAD 3.14/180


Planet::Planet(float distance, float revolutionTime, float rotationTime, float radius, GLuint textureId) {

	this->radius = radius;
	this->distance = distance;
	this->rotationTime = rotationTime;
	this->revolutionTime = revolutionTime;
	this->textureId = textureId;
}


int Planet::getRadius() {
	return radius;
}

void Planet::calculatePosition(float time) {

	float angle = time * M_PI / revolutionTime;

	positionInSpace[0] = sin(angle) * distance;
	positionInSpace[1] = cos(angle) * distance;
	positionInSpace[2] = 0;

	rotationAngle = time * 360 / rotationTime;

}

void Planet::getPosition(float *pos) {

	pos[0] = positionInSpace[0] * orbitScale;
	pos[1] = positionInSpace[1] * orbitScale;
	pos[2] = positionInSpace[2] * orbitScale;
}

void Planet::render() {
	glPushMatrix();

	glTranslatef(positionInSpace[0] * orbitScale, positionInSpace[1] * orbitScale, -10.0f);

	glRotatef(rotationAngle/10, 0.0f, 0.0f, 1.0f);

	// glBindTexture(GL_TEXTURE_2D, textureId);
	
	 GLUquadricObj* quadric = gluNewQuadric();
	// gluQuadricTexture(quadric, true);
	// gluQuadricNormals(quadric, GLU_SMOOTH);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	gluQuadricTexture(quadric,1);


	if (distance < 0.001f) {
		float radiusScaled = radius * radiusScale;
		if (radiusScaled > 0.5f) radiusScaled = 0.5f;

		//glDisable(GL_LIGHTING);
		gluSphere(quadric, radiusScaled, 30, 30);
		//glEnable(GL_LIGHTING);
	}
	else {
		gluSphere(quadric, radius * radiusScale, 30, 30);
	}


	glPopMatrix();

}
