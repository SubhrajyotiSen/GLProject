#include <fstream>
#include "imageloader.h"
#include <GL/glut.h>

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
    fclose(f);

    for(i = 0; i < size; i += 3)
    {
            char tmp = data[i];
            data[i] = data[i+2];
            data[i+2] = tmp;
    }

    glGenTextures(1, &textureId); 
    glBindTexture(GL_TEXTURE_2D, textureId);

    //Map the image to the texture
    glTexImage2D(GL_TEXTURE_2D,
        0,
        GL_RGB,
        width, height,
        0,
        GL_RGB,
        GL_UNSIGNED_BYTE,
        data);
}

GLuint Image::getTextureID() {
    
    return textureId;
}
