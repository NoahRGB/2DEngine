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
    void drawCircle(float x, float y, float radius, const Colour& colour, Shader* shader = nullptr);
    void drawTexture(float x, float y, float width, float height, Texture& texture, const Colour& tint);

    glm::vec2 mousePos() const;
    float scroll() const;
    float isLeftClicking() const;
    double time() const;

    Rect rectShape;
    Shader commonShader, circleShader, textureShader;

    glm::mat4 projection;
    void updateProjection();

private:
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
    static void processInput(GLFWwindow* window);

	void setupGeometry();
    void close();

    GLFWwindow* window;
    int windowWidth, windowHeight;

    float scrollDelta = 0.0f;
};
