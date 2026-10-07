#pragma once
#include <glm/glm.hpp>

class Colour {

public:
	Colour();
	Colour(float r, float g, float b, float a);
	Colour(int r, int g, int b, float a);

	glm::vec4 glm() const;
	
	float r, g, b, a;

private:

};