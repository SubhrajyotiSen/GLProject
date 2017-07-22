#include "solarsystem.h"

SolarSystem::SolarSystem() {

}

// calculate the positions of all the planets in the solar system
void SolarSystem::calculatePositions(float time) {
	for (int i = 0; i < planets.size(); i++)
		planets[i].calculatePosition(time);
}

// add a planet to the solar system
void SolarSystem::addPlanet(float distanceFromSun, float orbitTime, float rotationTime, float radius, GLuint textureHandle) {
	planets.push_back(Planet(distanceFromSun, orbitTime, rotationTime, radius, textureHandle));
}

// add a moon to the given index
void SolarSystem::addMoon(int planetIndex, float distanceFromPlanet, float orbitTime, float rotationTime, float radius, GLuint textureHandle) {
	planets[planetIndex].addMoon(distanceFromPlanet, orbitTime, rotationTime, radius, textureHandle);
}

// render the planets and their orbits
void SolarSystem::render(float sunRadius) {
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_LIGHTING);
	planets[0].render();
	glDisable(GL_LIGHTING);

	for (int i = 1; i < planets.size(); i++)
	{
		if (planets[i].getScaledDistanceFromSun() > sunRadius) {
			glEnable(GL_LIGHTING);
			planets[i].render();
			glDisable(GL_LIGHTING);
			planets[i].renderOrbit();
		}
	}

	glDisable(GL_DEPTH_TEST);

}


// get the current location of planet at given index
void SolarSystem::getPlanetLocation(int index, float* vec) {
	planets[index].getPosition(vec);
}

// get radius of planet at given index
float SolarSystem::getPlanetRadius(int index) {
	return planets[index].getRadius();
}

// initiates the creation of a black hole
void SolarSystem::startBlackHole(GLuint textureHandle) {
	planets[0].setTexture(textureHandle);
	planets[0].increaseRadius();
}

// return the radius of the planet scaled according to the current system
float SolarSystem::getPlanetRadiusScaled(int index) {
	return planets[0].getRadiusScaled();
}