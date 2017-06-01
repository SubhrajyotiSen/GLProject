#include <GL/gl.h>

// classs to represent a moon
class Moon
{
	private:

		float distanceFromPlanet;

		float orbitTime;

		float rotationTime;

		float radius;

		GLuint textureHandle;

		float position[3];
		float rotation;

	public:
		//constructor
		Moon(float distanceFromPlanet, float orbitTime, float rotationTime, float radius, GLuint textureHandle);

		// calculate postion of moon
		void calculatePosition(float time);

		// render the moon
		void render(void);

		// render the moon's orbit
		void renderOrbit(void);
};

