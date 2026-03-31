#include "Engine2D.h"
#include <iostream>

#include "Colour.h"

Engine2D::Engine2D() {
    this->windowWidth = 500;
	this->windowHeight = 500;
}

Engine2D::Engine2D(int windowWidth, int windowHeight) {
    this->windowWidth = windowWidth;
	this->windowHeight = windowHeight;
}

void Engine2D::processInput(GLFWwindow * window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

void Engine2D::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

int Engine2D::init() {
    glfwInit();

    this->window = glfwCreateWindow(this->windowWidth, this->windowHeight, "Window", NULL, NULL);
    if (this->window == NULL) {
        std::cout << "Window creation failed" << std::endl;
        this->close();
        return -1;
    }
    glfwMakeContextCurrent(this->window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "GLFW initialisation failed" << std::endl;
        this->close();
        return -1;
    }

    glViewport(0, 0, this->windowWidth, this->windowHeight);
    glfwSetFramebufferSizeCallback(window, Engine2D::framebuffer_size_callback);

    return 0;
}

void Engine2D::close() {
    glfwTerminate();
}

void Engine2D::run() {

    while (!glfwWindowShouldClose(this->window)) {
        this->processInput(this->window);

        this->update(0.0);

        this->render();

        glfwSwapBuffers(this->window);
        glfwPollEvents();
    }

    this->close();
}

void Engine2D::clearScreen() {
    glClear(GL_COLOR_BUFFER_BIT);
}

void Engine2D::background(const Colour& colour) {
    glClearColor(colour.r, colour.g, colour.b, colour.a);
}