#include <GL/gl.h>	

//Represents an image
class Image {

private:
	// holds the id of the image texture
	GLuint textureId;

public:
	//constructor
	Image(char* path);

	// returns the id of the generated texture
	GLuint getTextureID();

};
