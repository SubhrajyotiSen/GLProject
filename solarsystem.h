#include <GL/gl.h>
#include <vector>
#include "planet.h"

class SolarSystem {
private:
	std::vector<Planet> planets;

public:
	SolarSystem();

	void addPlanet(float distance, float revolutionTime, float rotationTime, float radius, GLuint textureId);

	void calculatePositions(float time);

	void render();

	void getPlanetPosition(int position, float *pos);

	int getPlanetRadius(int position);

};