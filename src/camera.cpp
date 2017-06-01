#include <GL/glut.h>
#include <cmath>

#include "camera.h"

// set elements of a 3D vector
void vectorSet(float* vec, float x, float y, float z) {
	vec[0] = x;
	vec[1] = y;
	vec[2] = z;
}

// add two 3D vectors
void vectorAdd(float* v1, float* v2) {
	v1[0] += v2[0];
	v1[1] += v2[1];
	v1[2] += v2[2];
}

// copy a 3D vector into another
void vectorCopy(float* v1, float* v2) {
	v1[0] = v2[0];
	v1[1] = v2[1];
	v1[2] = v2[2];
}

// multiply a 3D vector by a scalar
void vectorMul(float* vec, float scalar) {
	vec[0] *= scalar;
	vec[1] *= scalar;
	vec[2] *= scalar;
}

// compute length of a vector
float lengthOfVec(float* vec) {
	return sqrtf(vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2]);
}

// normalise a 3D vector
void normaliseVec(float* vec) {
	vectorMul(vec, 1 / lengthOfVec(vec));
}

// create a rotation matrix using angle and axis
void rotationMatrix(float* matrix, float* axis, float angle) {
	float cos1 = cos(angle);
	float cos2 = 1 - cos1;
	float sin1 = sin(angle);

	matrix[0] = cos1 + axis[0]*axis[0]*cos2;
	matrix[1] = axis[0] * axis[1] * cos2 - axis[2]*sin1;
	matrix[2] = axis[0] * axis[2] * cos2 + axis[1]*sin1;

	matrix[3] = axis[1] * axis[0] * cos2 + axis[2]*sin1;
	matrix[4] = cos1 + axis[1] * axis[1] * cos2;
	matrix[5] = axis[1] * axis[2] * cos2 - axis[0] * sin1;

	matrix[6] = axis[2] * axis[0] * cos2 - axis[1] * sin1;
	matrix[7] = axis[2] * axis[1] * cos2 + axis[0] * sin1;
	matrix[8] = cos1 + axis[2] * axis[2] * cos2;
}

// multiply a vector with a matrix
void mulVecBy(float* v1, float* matrix, float* v2) {
	v2[0] = v1[0] * matrix[0] + v1[1] * matrix[1] + v1[2] * matrix[2];
	v2[1] = v1[0] * matrix[3] + v1[1] * matrix[4] + v1[2] * matrix[5];
	v2[2] = v1[0] * matrix[6] + v1[1] * matrix[7] + v1[2] * matrix[8];
}

// used to turn left or right with respect to a location in space
void rotateAroundVec(float* v1, float* v2, float angle, float* v3) {
	float matrix[16];
	rotationMatrix(matrix, v2, angle);

	mulVecBy(v1, matrix, v3);
}

// constructor
Camera::Camera() {
	cameraSpeed = 0.005f;
	cameraTurnSpeed = 0.01f;

	vectorSet(position, 1.5f,-2.5f,1.5f);
	vectorSet(forwardVec, -0.4f, 0.8f, -0.5f);
	vectorSet(rightVec, 0.9f, 0.5f, 0.0f);
	vectorSet(upVec, -0.2f, 0.5f, 0.9f);
}

// set view of camera to a specific postion
void Camera::setPosition() {
	gluLookAt(0, 0, 0, forwardVec[0], forwardVec[1], forwardVec[2], upVec[0], upVec[1], upVec[2]);
}

// move camera
void Camera::translate() {
	glTranslatef(-position[0], -position[1], -position[2]);
}

// make camera point in the direction of a particular plamet
void Camera::pointAt(float* targetVec) {
	float tempVec[3];
	float up[3] = { 0.0f, 0.0f, 1.0f };

	forwardVec[0] = targetVec[0] - position[0];
	forwardVec[1] = targetVec[1] - position[1];
	forwardVec[2] = targetVec[2] - position[2];
	normaliseVec(forwardVec);

	rotateAroundVec(forwardVec, up, -1.57f, tempVec);
	tempVec[2] = 0;
	normaliseVec(tempVec);
	vectorCopy(rightVec, tempVec);

	rotateAroundVec(forwardVec, rightVec, 1.57f, tempVec);
	vectorCopy(upVec, tempVec);
}

// increase speed of camera movement
void Camera::speedUp() {
	if (cameraSpeed < 1.0f)
		cameraSpeed *= 2;
}

// decrease speed of camera movement
void Camera::slowDown() {
	if (cameraSpeed > 0.000001f)
		cameraSpeed /= 2;
}

// move forward
void Camera::forward() {
	float vec[3];
	vectorCopy(vec, forwardVec);
	vectorMul(vec, cameraSpeed);

	vectorAdd(position, vec);
}

// move left
void Camera::left() {
	float vec[3];
	vectorCopy(vec, rightVec);
	vectorMul(vec, -cameraSpeed); 
	vectorAdd(position, vec);
}

// move right
void Camera::right() {
	float vec[3];
	vectorCopy(vec, rightVec);
	vectorMul(vec, cameraSpeed);

	vectorAdd(position, vec);
}

// move backward
void Camera::backward() {
	float vec[3];
	vectorCopy(vec, forwardVec);
	vectorMul(vec, -cameraSpeed); 
	vectorAdd(position, vec);
}

// tilt camera right
void Camera::tiltRight() {
	float tempVec[3];
	rotateAroundVec(upVec, forwardVec, cameraTurnSpeed, tempVec);
	vectorCopy(upVec, tempVec);

	rotateAroundVec(rightVec, forwardVec, cameraTurnSpeed, tempVec);
	vectorCopy(rightVec, tempVec);
}

// tilt camera left
void Camera::tiltLeft() {
	float tempVec[3];
	rotateAroundVec(upVec, forwardVec, -cameraTurnSpeed, tempVec);
	vectorCopy(upVec, tempVec);

	rotateAroundVec(rightVec, forwardVec, -cameraTurnSpeed, tempVec);
	vectorCopy(rightVec, tempVec);
}

// look up
void Camera::lookUp() {
	float tempVec[3];
	rotateAroundVec(forwardVec, rightVec, cameraTurnSpeed, tempVec);
	vectorCopy(forwardVec, tempVec);

	rotateAroundVec(upVec, rightVec, cameraTurnSpeed, tempVec);
	vectorCopy(upVec, tempVec);
}

// look down
void Camera::lookDown() {
	float tempVec[3];
	rotateAroundVec(forwardVec, rightVec, -cameraTurnSpeed, tempVec);
	vectorCopy(forwardVec, tempVec);

	rotateAroundVec(upVec, rightVec, -cameraTurnSpeed, tempVec);
	vectorCopy(upVec, tempVec);
}

// turn left
void Camera::turnLeft() {
	float tempVec[3];
	rotateAroundVec(forwardVec, upVec, cameraTurnSpeed, tempVec);
	vectorCopy(forwardVec, tempVec);

	rotateAroundVec(rightVec, upVec, cameraTurnSpeed, tempVec);
	vectorCopy(rightVec, tempVec);
}

// turn right
void Camera::turnRight() {
	float tempVec[3];
	rotateAroundVec(forwardVec, upVec, -cameraTurnSpeed, tempVec);
	vectorCopy(forwardVec, tempVec);

	rotateAroundVec(rightVec, upVec, -cameraTurnSpeed, tempVec);
	vectorCopy(rightVec, tempVec);
}
