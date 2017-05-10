#include "solarsystem.h"

SolarSystem::SolarSystem() {
	// empty constructor
}

void SolarSystem::addPlanet(float distance, float revolutionTime, float rotationTime, float radius, GLuint textureId) {

	planets.push_back(Planet(distance, revolutionTime, rotationTime, radius, textureId));

}

void SolarSystem::calculatePositions(float time) {
	
	for (int i = 0; i < planets.size(); i++) 
		planets[i].calculatePosition(time);

}

void SolarSystem::render() {

	for (int i = 0; i < planets.size(); i++) 
		planets[i].render();

}

void SolarSystem::getPlanetPosition(int position, float *pos) {

	planets[position].getPosition(pos);

}

int SolarSystem::getPlanetRadius(int position) {

	return planets[position].getRadius();

}