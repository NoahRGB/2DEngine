#pragma once

#include <glad/glad.h> // include glad first
#include <GLFW/glfw3.h>
#include <functional>

#include "Colour.h"

class Engine2D {

public:
	Engine2D();
    Engine2D(int windowWidth, int windowHeight);

    std::function<void(float)> update;
    std::function<void()> render;

    int init();
    void run();

	void clearScreen();
	void background(const Colour& colour);

private:
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    static void processInput(GLFWwindow* window);
    
    void close();

    GLFWwindow* window;
    int windowWidth, windowHeight;
};