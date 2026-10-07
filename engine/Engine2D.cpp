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

void Engine2D::setupGeometry() {
    this->rectShape.setupGeometry();
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

    this->commonShader.initialise("../engine/shaders/basic_shader.vs", "../engine/shaders/basic_shader.fs");
    this->setupGeometry();

    this->updateProjection();

    return 0;
}

void Engine2D::drawRect(float x, float y, float width, float height, const Colour& colour, Shader* shader) {
    Shader* s = shader ? shader : &this->commonShader;

    glm::mat4 transformation = glm::mat4(1.0f);
    // shifted by half width/height so that x/y refer to the top left corner of the rect
    transformation = glm::translate(transformation, glm::vec3(x + (width/2.0f), y + (height/2.0f), 0.0f));
    transformation = glm::scale(transformation, glm::vec3(width, height, 1.0f));

    this->rectShape.draw(s, transformation, this->projection, colour.glm());
}

void Engine2D::updateProjection() {
    this->projection = glm::ortho(0.0f, (float)this->windowWidth, (float)this->windowHeight, 0.0f);
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

void Engine2D::close() {
    glfwTerminate();
}