#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

class Shader {

public:
	Shader();
	Shader(const char* vertex, const char* fragment);

	void enable();
	bool initialise(const char* vertex, const char* fragment);

	void setBool(const std::string &name, bool val) const;
	void setInt(const std::string &name, int val) const;
	void setFloat(const std::string &name, float val) const;
	void setMat4f(const std::string &name, glm::mat4 val) const;
	void setVec4f(const std::string &name, glm::vec4 val) const;

	unsigned int ID;

private:

	std::string readFile(const char* path);
	bool getShaderSuccess(unsigned int shader, char* infoLog);
	bool getProgramSuccess(unsigned int program, char* infoLog);

};