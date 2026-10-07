#pragma once

#include <glad/glad.h> // include glad first
#include <GLFW/glfw3.h>
#include <functional>

#include "Colour.h"
#include "Shader.h"
#include "Rect.h"

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

	void drawRect(float x, float y, float width, float height, const Colour& colour, Shader* shader = nullptr);

    Rect rectShape;
    Shader commonShader;

    glm::mat4 projection;
    void updateProjection();

private:
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    static void processInput(GLFWwindow* window);

	void setupGeometry();
    void close();

    GLFWwindow* window;
    int windowWidth, windowHeight;
};
