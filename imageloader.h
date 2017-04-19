#pragma once

#ifndef IMAGE_LOADER_H_INCLUDED
#define IMAGE_LOADER_H_INCLUDED

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

#endif
