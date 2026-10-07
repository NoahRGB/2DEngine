#include "Shader.h"

Shader::Shader() {

}

Shader::Shader(const char* vertex, const char* fragment) {
	this->initialise(vertex, fragment);
}

bool Shader::initialise(const char* vertex, const char* fragment) {
	int success;
	char infoLog[512];

	// read vertex/fragment shader
	std::string vertexSourceStr = this->readFile(vertex);
	std::string fragmentSourceStr = this->readFile(fragment);

	const char* vertexSource = vertexSourceStr.c_str();
	const char* fragmentSource = fragmentSourceStr.c_str();

	// compile vertex/fragment shader, check for errors	
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);

	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);

	bool vertexSuccess = this->getShaderSuccess(vertexShader, infoLog);
	bool fragmentSuccess = this->getShaderSuccess(fragmentShader, infoLog);
	if (vertexSuccess && fragmentSuccess) {

		// create shader program, link shaders, check for errors
		this->ID = glCreateProgram();
		glAttachShader(this->ID, vertexShader);
		glAttachShader(this->ID, fragmentShader);
		glLinkProgram(this->ID);

		bool programSuccess = this->getProgramSuccess(this->ID, infoLog);

		if (programSuccess) {
			// delete vertex/fragment shader (not needed)
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);
		}

		else {
			std::cout << "Failed to link shader program" << std::endl;
			return false;
		}
	}

	else {
		std::cout << "Failed to compile vertex or fragment shader" << std::endl;
		return false;
	}

	return true;
}

void Shader::enable() {
	glUseProgram(this->ID);
}

std::string Shader::readFile(const char* path) {

	std::ifstream file;
	// ensure ifstream objects can throw exceptions:
	file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try {
		file.open(path);
		std::stringstream stream;
		stream << file.rdbuf();
		file.close();
		return stream.str();

	} catch (std::ifstream::failure e) {
		std::cout << "Failed to read shader file: " << path << std::endl;
	}

	return "";
}

bool Shader::getShaderSuccess(unsigned int shader, char* infoLog) {
	int success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	glGetShaderInfoLog(shader, 512, NULL, infoLog);
	return success;
}

bool Shader::getProgramSuccess(unsigned int program, char* infoLog) {
	int success;
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	glGetShaderInfoLog(program, 512, NULL, infoLog);
	return success;
}

void Shader::setBool(const std::string &name, bool val) const {
	glUniform1i(glGetUniformLocation(this->ID, name.c_str()), (int)val);
}

void Shader::setInt(const std::string &name, int val) const {
	glUniform1i(glGetUniformLocation(this->ID, name.c_str()), val);
}

void Shader::setFloat(const std::string &name, float val) const {
	glUniform1f(glGetUniformLocation(this->ID, name.c_str()), val);
}

void Shader::setMat4f(const std::string &name, glm::mat4 val) const {
	glUniformMatrix4fv(glGetUniformLocation(this->ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(val));
}

void Shader::setVec4f(const std::string &name, glm::vec4 val) const {
	glUniform4fv(glGetUniformLocation(this->ID, name.c_str()), 1, glm::value_ptr(val));
}