// class to represent a camera
class Camera
{
	private:
		// vector to represent the forward direction
		float forwardVec[3];

		// vector to represent the right side of the camera
		float rightVec[3];

		// vector ro represet the upward side of the camera to enable proper orientation
		float upVec[3];

		// positon in 3D space
		float position[3];

		// camera movement speed
		float cameraSpeed;

		// camera tilting speed
		float cameraTurnSpeed;

	public:
		
		// constructor
		Camera(void);

		// set view of camera to a specific postion
		void setPosition(void);

		// move camera
		void translate(void);

		// make camera point in the direction of a particular plamet
		void pointAt(float* targetVec);

		// increase speed of camera movement
		void speedUp(void);

		// decrease speed of camera movement
		void slowDown(void);

		// move forward
		void forward(void);

		// move left
		void left(void);

		// move right
		void right(void);

		// move backward
		void backward(void);

		// tilt camera right
		void tiltRight(void);

		// tilt camera left
		void tiltLeft(void);

		// look up
		void lookUp(void);

		// look down
		void lookDown(void);

		// turn left
		void turnLeft(void);

		// turn right
		void turnRight(void);
};
