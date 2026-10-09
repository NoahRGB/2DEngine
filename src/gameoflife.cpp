#include "../engine/Engine2D.h"
#include "../engine/Colour.h"
#include "../engine/Texture.h"

#include <random>
#include <iostream>
#include <vector>

std::vector<std::pair<int, int>> get_neighbours(int row, int col, int numRows, int numCols) {
	std::vector<std::pair<int, int>> neighbours;
	neighbours.push_back(std::pair<int, int>((row+1)%numRows, col));
	neighbours.push_back(std::pair<int, int>((row-1+numRows)%numRows, col));
	neighbours.push_back(std::pair<int, int>(row, (col+1)%numCols));
	neighbours.push_back(std::pair<int, int>(row, (col-1+numCols)%numCols));
	neighbours.push_back(std::pair<int, int>((row+1)%numRows, (col+1)%numCols));
	neighbours.push_back(std::pair<int, int>((row-1+numRows)%numRows, (col-1+numCols)%numCols));
	neighbours.push_back(std::pair<int, int>((row+1)%numRows, (col-1+numCols)%numCols));
	neighbours.push_back(std::pair<int, int>((row-1+numRows)%numRows, (col+1)%numCols));
	return neighbours;
}

int main() {

	int WIDTH = 800, HEIGHT = 800;
	Colour bg(0, 0, 0, 1);

	Engine2D engine(WIDTH, HEIGHT);
	engine.init();

	int cellSize = 3;
	int numCols = WIDTH/cellSize, numRows = HEIGHT/cellSize;

	Texture grid = Texture(numCols, numRows);

	// std::vector<std::vector<bool>> currentGeneration(numRows, std::vector<bool>(numCols, false));
	std::vector<unsigned char> currentGeneration(numRows * numCols);
	
	std::mt19937 rng(std::random_device{}());
	std::bernoulli_distribution alive(0.25);

	for (int row = 0; row < numRows; row++)
		for (int col = 0; col < numCols; col++)
			currentGeneration[col + row * numCols] = alive(rng) ? 255 : 0;

	engine.update = [&](float deltaTime) {
	
	};

	engine.render = [&]() {
		engine.clearScreen();

		std::vector<unsigned char> nextGeneration = currentGeneration;

		for (int row = 0; row < numRows; row++) {
			for (int col = 0; col < numCols; col++) {

				bool currentCellAlive = currentGeneration[col + row * numCols];

				// Colour cellCol = currentCellAlive ? Colour(255, 255, 255, 1) : Colour(0, 0, 0, 1);
				// if (currentCellAlive)
				// 	engine.drawRect(col * cellSize, row * cellSize, cellSize, cellSize, cellCol);

				std::vector<std::pair<int, int>> neighbours = get_neighbours(row, col, numRows, numCols);
				int aliveNeighbours = 0;
				for (std::pair<int, int> neighbour : neighbours) {
					aliveNeighbours += currentGeneration[neighbour.second + neighbour.first * numCols] ? 1 : 0;
				}

				if (currentCellAlive && aliveNeighbours < 2 || currentCellAlive && aliveNeighbours > 3) {
					nextGeneration[col + row * numCols] = 0;
				}
				if (!currentCellAlive && aliveNeighbours == 3) {
					nextGeneration[col + row * numCols] = 255;
				}

			}
		}

		currentGeneration = nextGeneration;
		grid.setTexture(currentGeneration.data());
		engine.drawTexture(0, 0, WIDTH, HEIGHT, grid, {255, 255, 255, 1});


		engine.background(bg);
	};

	engine.run();

	return 0;
}
