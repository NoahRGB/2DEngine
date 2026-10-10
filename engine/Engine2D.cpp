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
    auto* engine = static_cast<Engine2D*>(glfwGetWindowUserPointer(window));
    engine->updateProjection();
}

void Engine2D::scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    auto* engine = static_cast<Engine2D*>(glfwGetWindowUserPointer(window));
    engine->scrollDelta += (float)yoffset;
}

void Engine2D::setupGeometry() {
    this->rectShape.setupGeometry();
}

int Engine2D::init() {
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

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
    
    glfwSwapInterval(1);
    glViewport(0, 0, this->windowWidth, this->windowHeight);
    glfwSetWindowUserPointer(this->window, this);
    glfwSetFramebufferSizeCallback(this->window, Engine2D::framebuffer_size_callback);
    glfwSetScrollCallback(this->window, Engine2D::scroll_callback);

    // enable alpha/blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    this->commonShader.initialise("../engine/shaders/common.vs", "../engine/shaders/common.fs");
    this->circleShader.initialise("../engine/shaders/common.vs", "../engine/shaders/circle.fs");
    this->textureShader.initialise("../engine/shaders/common.vs", "../engine/shaders/texture.fs");

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

void Engine2D::drawCircle(float x, float y, float radius, const Colour& colour, Shader* shader) {
    Shader* s = shader ? shader : &this->circleShader;

    // cricles are drawn using the rect geometry and use a differenty frag shader
    // to define the circle shape

    glm::mat4 transformation = glm::mat4(1.0f);
    transformation = glm::translate(transformation, glm::vec3(x, y, 0.0f));
    // the unit quad spans -0.5to 0.5 so scaling by the diameter gives the radius
    transformation = glm::scale(transformation, glm::vec3(radius * 2.0f, radius * 2.0f, 1.0f));

    this->rectShape.draw(s, transformation, this->projection, colour.glm());
}

void Engine2D::drawTexture(float x, float y, float width, float height, Texture& texture, const Colour& tint) {
    glm::mat4 transformation = glm::mat4(1.0f);
    // shifted by half width/height so that x/y refer to the top left corner of the rect
    transformation = glm::translate(transformation, glm::vec3(x + (width/2.0f), y + (height/2.0f), 0.0f));
    transformation = glm::scale(transformation, glm::vec3(width, height, 1.0f));

    this->rectShape.draw(&this->textureShader, transformation, this->projection, tint.glm(), &texture);
}


glm::vec2 Engine2D::mousePos() const {
    double x, y;
    glfwGetCursorPos(this->window, &x, &y);
    return glm::vec2((float)x, (float)y);
}

float Engine2D::scroll() const {
    return this->scrollDelta;
}

float Engine2D::isLeftClicking() const {
    return glfwGetMouseButton(this->window, GLFW_MOUSE_BUTTON_LEFT);
}

double Engine2D::time() const {
    return glfwGetTime();
}


void Engine2D::updateProjection() {
    this->projection = glm::ortho(0.0f, (float)this->windowWidth, (float)this->windowHeight, 0.0f);
}

void Engine2D::run() {

    double savedTime = glfwGetTime();

    while (!glfwWindowShouldClose(this->window)) {
        double currentTime = glfwGetTime();
        float deltaTime = (float)(currentTime - savedTime);
        savedTime = currentTime;

        this->processInput(this->window);

        this->update(deltaTime); 

        this->render();

        glfwSwapBuffers(this->window);
        this->scrollDelta = 0.0f;
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