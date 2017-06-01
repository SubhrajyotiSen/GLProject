#include <GL/gl.h>
#include <vector>

#include "moon.h"

// class to represent a planet
class Planet
{
	private:

		float distanceFromSun;

		float orbitTime;

		float rotationTime;

		float radius;

		GLuint textureHandle;

		float position[3];
		float rotation;

		std::vector<Moon> moons;

		float i;

		int n;

	public:
		// constructor
		Planet(float distanceFromSun, float orbitTime, float rotationTime, float radius, GLuint textureHandle);

		// calculate the position of given planet
		void calculatePosition(float time);

		// render a single planet
		void render(void);

		// render orbit of given planet
		void renderOrbit(void);

		// get position of a planet
		void getPosition(float* vec);

		// get radius of given planet
		float getRadius(void);

		// add a moon to selected planet
		void addMoon(float distanceFromPlanet, float orbitTime, float rotationTime, float radius, GLuint textureHandle);

		// increase radius of planet. Used for black hole case
		void increaseRadius();

		// set texture of given planet at runtime
		void setTexture(GLuint textureHandle);
};

