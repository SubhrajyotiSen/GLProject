#include <GL/gl.h>
#include <vector>

#include "planet.h"

// class to represent the solar system
class SolarSystem
{
	private:

		// use a vector so that planets can be added dynamically
		std::vector<Planet> planets;

	public:
		//constructor
		SolarSystem();

		// calculate the positions of all the planets in the solar system
		void calculatePositions(float time);

		// add a planet to the solar system
		void addPlanet(float distanceFromSun, float orbitTime, float rotationTime, float radius, GLuint textureHandle);

		// add a moon to the given index
		void addMoon(int planetIndex, float distanceFromPlanet, float orbitTime, float rotationTime, float radius, GLuint textureHandle);

		// render the planets and their orbits
		void render();

		// get the current location of planet at given index
		void getPlanetLocation(int index, float* vec);

		// get radius of planet at given index
		float getPlanetRadius(int index);

		// initiates the creation of a black hole
		void startBlackHole(GLuint textureHandle);
};

