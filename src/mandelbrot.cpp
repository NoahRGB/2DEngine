#include "../engine/Engine2D.h"
#include "../engine/Colour.h"

#include <iostream>

int main() {

	int WIDTH = 1000, HEIGHT = 1000;
	Colour bg(0, 0, 0, 1);

	Engine2D engine(WIDTH, HEIGHT);
	engine.init();

	Shader mandelbrotShader = Shader("../engine/shaders/common.vs", "../engine/shaders/mandelbrot.fs");

	double zoom = 1.0;
	float automaticZoomSpeed = 1.0;

	// glm::dvec2 position(-0.743643887037151, 0.131825904205330);
	glm::dvec2 position(-0.77568377, 0.13646737);
	// glm::dvec2 position(0.0, 1.0);

	glm::dvec2 lastMousePos(0.0, 0.0);
	bool isClicking = false;
	
	engine.update = [&](float deltaTime) {
		glm::dvec2 mousePos = (glm::dvec2)engine.mousePos() / glm::dvec2(WIDTH, HEIGHT);

		// zoom using scroll wheel and slowly zoom in automatically
		zoom *= std::pow(1.1, engine.scroll());
		zoom *= std::exp(automaticZoomSpeed * deltaTime);

		// clicking+dragging
		bool click = engine.isLeftClicking();
		if (click && isClicking) {
			position += (lastMousePos - mousePos) * 3.0 / zoom;
		}
		
		lastMousePos = mousePos;
		isClicking = click;

		// send current zoom/pos/time to fradment shader
		mandelbrotShader.enable();
		mandelbrotShader.setDouble("uZoom", zoom);
		mandelbrotShader.setVec2d("uPos", position);
		mandelbrotShader.setFloat("uTime", (float)engine.time());
	};

	engine.render = [&]() {
		engine.clearScreen();

		// draw full size rect with mandelbrot shader
		engine.drawRect(0, 0, WIDTH, HEIGHT, {0, 0, 0, 1}, &mandelbrotShader);

		engine.background(bg);
	};

	engine.run();

	return 0;
}
