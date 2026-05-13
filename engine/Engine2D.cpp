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






		float vertices[] = {
		  -0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.0f,  0.5f, 0.0f
		};  

		unsigned int VBO;
		glGenBuffers(1, &VBO);

		const char *vertexShaderSource = "#version 330 core\n"
			"layout (location = 0) in vec3 aPos;\n"
    	"void main()\n"
    	"{\n"
    	"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    	"}\0";

		const char *fragmentShaderSource = "#version 330 core\n"
			"out vec4 FragColor;\n"
    	"void main()\n"
    	"{\n"
    	"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    	"}\0";


		unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
		glCompileShader(vertexShader);


		int  success;
		char infoLog[512];
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

		if(!success)
		{
		    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		}

		unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

		if(!success)
		{
		    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		}

		this->shaderProgram = glCreateProgram();
		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glLinkProgram(shaderProgram);


		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
		if(!success) {
		    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		    std::cout << "Shader program failed\n" << infoLog << std::endl;
		}

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		glGenVertexArrays(1, &this->VAO);

		glBindVertexArray(this->VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);


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


				glUseProgram(this->shaderProgram);
				glBindVertexArray(this->VAO);
				glDrawArrays(GL_TRIANGLES, 0, 3);





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
