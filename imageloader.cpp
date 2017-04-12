#include <fstream>
#include "imageloader.h"
#include <GL/glut.h>

Image::Image(char* ps, int w, int h) : pixels(ps), width(w), height(h) {

}

Image::~Image() {

}


Image* loadBMP(const char* filename) {
    int i;
    FILE* f = fopen(filename, "rb");
    char info[54];

    fread(info, sizeof(char), 54, f);  //read 54-byte header

    // extract image height and width from header
    int width = *(int*)&info[18];
    int height = *(int*)&info[22];

    int size = 3 * width * height;
    char* data = new char[size]; // allocate 3 bytes per pixel
    fread(data, sizeof(char), size, f); // read the rest of the data at once
    fclose(f);

    for(i = 0; i < size; i += 3)
    {
            char tmp = data[i];
            data[i] = data[i+2];
            data[i+2] = tmp;
    }

    return new Image(data, width, height); //return Image object
}

GLuint loadTextureFromImage(Image* image) {
	GLuint textureId;
	glGenTextures(1, &textureId); 
	glBindTexture(GL_TEXTURE_2D, textureId);

	//Map the image to the texture
	glTexImage2D(GL_TEXTURE_2D,
		0,
		GL_RGB,
		image->width, image->height,
		0,
		GL_RGB,
		GL_UNSIGNED_BYTE,
		image->pixels);
	return textureId;
}

