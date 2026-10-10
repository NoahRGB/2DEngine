#include "Colour.h"

Colour::Colour() {
	this->r = 0.0f;
	this->g = 0.0f;
	this->b = 0.0f;
	this->a = 1.0f;
}

Colour::Colour(float r, float g, float b, float a) {
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}

Colour::Colour(float H, float S, float V) {
	float C = V * S;
	float X = C * (1 - abs(fmod(H / 60.0, 2.0) - 1.0));
	float m = V - C;

	float rPrime = 0.0, gPrime = 0.0, bPrime = 0.0;
	if (H < 360.0 && H >= 300.0) rPrime = C, gPrime = 0.0, bPrime = X;
	else if (H >= 240.0) rPrime = X, gPrime = 0.0, bPrime = C;
	else if (H >= 180.0) rPrime = 0.0, gPrime = X, bPrime = C;
	else if (H >= 120.0) rPrime = 0.0, gPrime = C, bPrime = X;
	else if (H >= 60.0) rPrime = X, gPrime = C, bPrime = 0.0;
	else rPrime = C, gPrime = X, bPrime = 0.0;

	this->r = rPrime + m;
	this->g = gPrime + m;
	this->b = bPrime + m;
	this->a = 1.0;
}

Colour::Colour(int r, int g, int b, float a) {
	this->r = r / 255.0f;
	this->g = g / 255.0f;
	this->b = b / 255.0f;
	this->a = a;
}

glm::vec4 Colour::glm() const {
	return glm::vec4(this->r, this->g, this->b, this->a);
}