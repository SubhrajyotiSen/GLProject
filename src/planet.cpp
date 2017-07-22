#include <cmath>
#include <GL/glut.h>

#include "planet.h"
#include "constants.h"

// constructor
Planet::Planet(float distanceFromSun, float orbitTime, float rotationTime, float radius, GLuint textureHandle) {
	this->distanceFromSun = distanceFromSun;
	this->orbitTime = orbitTime;
	this->rotationTime = rotationTime;
	this->radius = radius;
	this->textureHandle = textureHandle;
	this->n = 0;
	this->i = 0.05;
}

// calculate the position of given planet
void Planet::calculatePosition(float time) {
	float angle = time * 3.1419f / orbitTime;

	position[0] = sin(angle) * distanceFromSun;
	position[1] = cos(angle) * distanceFromSun;
	position[2] = 0;

	rotation = time * 360 / rotationTime;

	for (int i = 0; i < moons.size(); i++)
		moons[i].calculatePosition(time);
}

// render a single planet
void Planet::render(void) {
	glPushMatrix();

	glTranslatef(position[0] * orbitScale, position[1] * orbitScale, position[2] * orbitScale);

	for (int i = 0; i < moons.size(); i++)
		moons[i].render();

	glRotatef(rotation, 0.0f, 0.0f, 1.0f);

	glBindTexture(GL_TEXTURE_2D, textureHandle);

	GLUquadricObj* quadric = gluNewQuadric();
	gluQuadricTexture(quadric, true);
	gluQuadricNormals(quadric, GLU_SMOOTH);

	if (distanceFromSun < 0.001f) 	{
		radiusScaled = radius * radiusScale;
		if (radiusScaled > 0.5f) 
			radiusScaled = 0.5f;
		radiusScaled = radiusScaled + n*i;

		glDisable(GL_LIGHTING);
		gluSphere(quadric, radiusScaled, 30, 30);
		glEnable(GL_LIGHTING);
	}
	else
		gluSphere(quadric, radius * radiusScale, 30, 30);

	glPopMatrix();
}

// render orbit of given planet
void Planet::renderOrbit(void) {
	glBegin(GL_LINE_STRIP);

	for (float angle = 0.0f; angle < 6.283185307f; angle += 0.05f)
		glVertex3f(sin(angle) * distanceFromSun * orbitScale, cos(angle) * distanceFromSun * orbitScale, 0.0f);

	glVertex3f(0.0f, distanceFromSun * orbitScale, 0.0f);

	glEnd();

	glPushMatrix();
	glTranslatef(position[0] * orbitScale, position[1] * orbitScale, position[2] * orbitScale);
	for (int i = 0; i < moons.size(); i++)
		moons[i].renderOrbit();

	glPopMatrix();

}

// get position of a planet
void Planet::getPosition(float* vec) {
	vec[0] = position[0] * orbitScale;
	vec[1] = position[1] * orbitScale;
	vec[2] = position[2] * orbitScale;
}

// get radius of given planet
float Planet::getRadius(void) {
	return radius;
}

// add a moon to selected planet
void Planet::addMoon(float distanceFromPlanet, float orbitTime, float rotationTime, float radius, GLuint textureHandle) {
	moons.push_back(Moon(distanceFromPlanet, orbitTime, rotationTime, radius, textureHandle));
}

// increase radius of planet. Used for black hole case
void Planet::increaseRadius() {
	n++;
}

// set texture of given planet at runtime
void Planet::setTexture(GLuint textureHandle)  {
	 this->textureHandle = textureHandle;
}

// get distance of a particular planet from the sun
float Planet::getScaledDistanceFromSun(void) {
	return distanceFromSun * orbitScale;
}

// get the radius after scaling to the current system
float Planet::getRadiusScaled(void) {
	return radiusScaled;
}