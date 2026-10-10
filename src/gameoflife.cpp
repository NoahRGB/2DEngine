#include "../engine/Engine2D.h"
#include "../engine/Colour.h"
#include "../engine/Texture.h"

#include <random>
#include <iostream>
#include <vector>

int main() {

	int WIDTH = 500, HEIGHT = 500;
	Colour bg(0, 0, 0, 1);

	Engine2D engine(WIDTH, HEIGHT);
	engine.init();

	int cellSize = 5;
	int numCols = WIDTH/cellSize, numRows = HEIGHT/cellSize;
	bool savedIsClicking = false;

	Texture grid = Texture(numCols, numRows, 4);

	// 1D array so it can be fed into a texturee
	std::vector<unsigned char> currentGeneration(numRows * numCols);
	std::vector<unsigned char> nextGeneration(numRows * numCols);
	std::vector<unsigned char> pixels(numRows * numCols * 4); // stores rgba

	std::vector<int> aliveCounter(numRows * numCols);
	for (int row = 0; row < numRows; row++) {
		for (int col = 0; col < numCols; col++) {
			aliveCounter[col + row * numCols] = 0;
		}
	}

	std::mt19937 rng(std::random_device{}());
	std::bernoulli_distribution alive(0.5);

	int steps = 0;

	// initialise first generation randomly
	for (int row = 0; row < numRows; row++) {
		for (int col = 0; col < numCols; col++) {
			currentGeneration[col + row * numCols] = alive(rng) ? 255 : 0;
		}
	}

	engine.update = [&](float deltaTime) {
		steps += 1;
		if (steps % 5 == 0) {
			for (int row = 0; row < numRows; row++) {
				for (int col = 0; col < numCols; col++) {

					bool currentCellAlive = currentGeneration[col + row * numCols];

					int aliveNeighbours = 0;
					// check all 8 neighoburs (with wrap around)
					aliveNeighbours += currentGeneration[col + ((row+1)%numRows) * numCols] ? 1 : 0;
					aliveNeighbours += currentGeneration[col + ((row-1+numRows)%numRows) * numCols] ? 1 : 0;
					aliveNeighbours += currentGeneration[((col+1)%numCols) + row * numCols] ? 1 : 0;
					aliveNeighbours += currentGeneration[((col-1+numCols)%numCols) + row * numCols] ? 1 : 0;
					aliveNeighbours += currentGeneration[((col+1)%numCols) + ((row+1)%numRows) * numCols] ? 1 : 0;
					aliveNeighbours += currentGeneration[((col-1+numCols)%numCols) + ((row-1+numRows)%numRows) * numCols] ? 1 : 0;
					aliveNeighbours += currentGeneration[((col-1+numCols)%numCols) + ((row+1)%numRows) * numCols] ? 1 : 0;
					aliveNeighbours += currentGeneration[((col+1)%numCols) +  ((row-1+numRows)%numRows) * numCols] ? 1 : 0;

					// update using game of life rules, increment alive counter
					nextGeneration[col + row * numCols] = (aliveNeighbours == 3 || (currentCellAlive && aliveNeighbours == 2)) ? 255 : 0;
					aliveCounter[col + row * numCols] = nextGeneration[col + row * numCols] ? aliveCounter[col + row * numCols] + 1 : 0;
				}
			}
			
			std::swap(currentGeneration, nextGeneration);
		}

		bool isClicking = engine.isLeftClicking();
		if (isClicking && savedIsClicking) {
			// must be dragging
			glm::dvec2 mousePos = engine.mousePos();
			int col = mousePos.x / cellSize, row = mousePos.y / cellSize;
			currentGeneration[col + row * numCols] = 255;
			currentGeneration[col + ((row+1)%numRows) * numCols] = 255;
			currentGeneration[col + ((row-1+numRows)%numRows) * numCols] = 255;
			currentGeneration[((col+1)%numCols) + row * numCols] = 255;
			currentGeneration[((col-1+numCols)%numCols) + row * numCols] = 255;
			currentGeneration[((col+1)%numCols) + ((row+1)%numRows) * numCols] = 255;
			currentGeneration[((col-1+numCols)%numCols) + ((row-1+numRows)%numRows) * numCols] = 255;
			currentGeneration[((col-1+numCols)%numCols) + ((row+1)%numRows) * numCols] = 255;
			currentGeneration[((col+1)%numCols) +  ((row-1+numRows)%numRows) * numCols] = 255;
		}
		savedIsClicking = isClicking;
	};

	engine.render = [&]() {
		engine.clearScreen();

		// copy over generation states into pixels buffer
		for (int i = 0; i < numRows * numCols; i++) {
			bool isCellAlive = currentGeneration[i];
			int aliveLength = aliveCounter[i];

			// animate colour using HSV
			float t = 1.0f - std::exp(-aliveLength / 15.0f);
			float v = 1.0f - t * 0.8f;
			Colour cellColour = Colour(v*360.0f, v, v);

			// RGBA
			pixels[i*4 + 0] = isCellAlive ? cellColour.r*255 : 0;
			pixels[i*4 + 1] = isCellAlive ? cellColour.g*255 : 0;
			pixels[i*4 + 2] = isCellAlive ? cellColour.b*255 : 0;
			pixels[i*4 + 3] = 255;
		}

		grid.setTexture(pixels.data());
		engine.drawTexture(0, 0, WIDTH, HEIGHT, grid, {255, 255, 255, 1});


		engine.background(bg);
	};

	engine.run();

	return 0;
}
