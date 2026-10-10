#pragma once

#include <glad/glad.h> // include glad first
#include <GLFW/glfw3.h>

class Texture {

public:
    Texture(const char* path);
    Texture(int width, int height, int channels);

    void setTexture(const unsigned char* pixels);

    int width, height, channels;
    unsigned int textureId;

private:


};