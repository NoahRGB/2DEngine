#pragma once

#include <glad/glad.h> // include glad first
#include <GLFW/glfw3.h>

class Texture {

public:
    Texture(const char* path);
    Texture(int width, int height);

    void setTexture(const unsigned char* pixels);

    int width, height;
    unsigned int textureId;

private:


};