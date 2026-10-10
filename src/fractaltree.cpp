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

        engine.drawLine(0, 0, WIDTH-400, HEIGHT-100, {255, 0, 0, 1});

		
		engine.background(bg);
	};

	engine.run();

	return 0;
}
