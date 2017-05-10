#include <GL/gl.h>	

//Represents an image
class Image {

private:

	GLuint textureId;

public:

	Image(char* path);

	//Extracts texture from Image.
	GLuint getTextureID();

};
