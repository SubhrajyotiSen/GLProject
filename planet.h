#include <GL/gl.h>
#include <vector>
#include <GL/glut.h>


class Planet {

private:

	float radius;

	float distance;

	float rotationTime;

	float revolutionTime;

	float rotationAngle;

	float positionInSpace[3];

	GLuint textureId;

	GLUquadricObj *sphere;

public: 

	Planet(float distance, float revolutionTime, float rotationTime, float radius, GLuint textureId);

	void render();

	void getPosition(float *pos);

	void calculatePosition(float time);

	int getRadius();

};