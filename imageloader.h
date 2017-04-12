#pragma once

#ifndef IMAGE_LOADER_H_INCLUDED
#define IMAGE_LOADER_H_INCLUDED

#include <GL/gl.h>	

//Represents an image

class Image {

public:

	Image(char* ps, int w, int h);

	~Image();

	char* pixels;

	int width;

	int height;

};



//Reads a bitmap image from file.

Image* loadBMP(const char* filename);

//Extracts texture from Image.
GLuint loadTextureFromImage(Image* image);



#endif
