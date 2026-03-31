#include "../engine/Engine2D.h"
#include "../engine/Colour.h"

#include <iostream>

int main() {

	int WIDTH = 500, HEIGHT = 500;
	Colour bg(255, 0, 0, 1.0f);

	Engine2D engine(WIDTH, HEIGHT);
	engine.init();
	
	engine.update = [&](float deltaTime) {
		
	};

	engine.render = [&]() {
		engine.clearScreen();
		engine.background(bg);
	};

	engine.run();

	return 0;
}