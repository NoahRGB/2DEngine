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

Colour::Colour(int r, int g, int b, float a) {
	this->r = r / 255.0f;
	this->g = g / 255.0f;
	this->b = b / 255.0f;
	this->a = a;
}