#include <fstream>
#include <GL/glut.h>

#include "imageloader.h"

// class to represent an Image
Image::Image(char* path) {

    int i;
    FILE* f = fopen(path, "rb");
    char info[54];

    fread(info, sizeof(char), 54, f);  //read 54-byte header

    // extract image height and width from header
    int width = *(int*)&info[18];
    int height = *(int*)&info[22];

    int size = 3 * width * height;
    char* data = new char[size]; // allocate 3 bytes per pixel
    fread(data, sizeof(char), size, f); // read the rest of the data at once
    fclose(f); // remember to close the file pointer

    for(i = 0; i < size; i += 3) {
            char tmp = data[i];
            data[i] = data[i+2];
            data[i+2] = tmp;
    }

    glGenTextures(1, &textureId); // generate the texture

    //bind the texture 
    glBindTexture(GL_TEXTURE_2D, textureId);
    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                     GL_LINEAR_MIPMAP_NEAREST );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    gluBuild2DMipmaps( GL_TEXTURE_2D, 3, width, height,
                   GL_RGB, GL_UNSIGNED_BYTE, data);
}

// returns the id of the generated texture
GLuint Image::getTextureID() {
    
    return textureId;
}
