#include "../engine/Engine2D.h"
#include "../engine/Colour.h"

#include <iostream>

int main() {

	int WIDTH = 500, HEIGHT = 500;
	Colour bg(0, 0, 0, 1);

	Engine2D engine(WIDTH, HEIGHT);
	engine.init();
	
	engine.update = [&](float deltaTime) {
		
	};

	engine.render = [&]() {
		engine.clearScreen();
		engine.drawRect(250, 250, 100, 100, {255, 255, 100, 1});
		engine.drawRect(10, 10, 100, 100, {255, 100, 100, 1});

		engine.background(bg);
	};

	engine.run();

	return 0;
}
