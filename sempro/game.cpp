#include <cstdio>
#include <cstdlib>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#include "game.h"

Game::Game(int size, int cellSize) {
	this->size = size;
	this->cellSize = cellSize;
	cells = (bool **)malloc(sizeof(bool*)*size);
	updatedCells = (bool **)malloc(sizeof(bool*)*size);

	for (int i = 0; i < size; i++) {
		cells[i] = (bool *)malloc(sizeof(bool)*size);
		updatedCells[i] = (bool *)malloc(sizeof(bool)*size);
	}

	fillCells();
}

Game::~Game() {
	for (int i = 0; i < size; i++) {
		free(cells[i]);
		free(updatedCells[i]);
	}
	
	free(cells);
	free(updatedCells);
}

void Game::fillCells() {
	FILE * file;
	fopen_s(&file, "data.txt", "r");
	
	if (!file) {
		randomizeCells();
		return;
	}
	char c = fgetc(file);
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (c == EOF) goto endloop;
			else if (c == 48) cells[i][j] = 0;
			else if (c == 49) cells[i][j] = 1;
			c = fgetc(file);
		}
		c = fgetc(file);
	}
	endloop:
	fclose(file);
}

void Game::randomizeCells() {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			cells[i][j] = rand() % 2;
		}
	}
}

bool Game::inCells(int i, int j) {
	bool returnment = (i >= 0 && i < size && j >= 0 && j < size);
	return returnment;
}

int Game::calculateNeighbours(int i, int j) {
	int alive = 0;
	int up = i - 1;
	int right = j + 1;
	int down = i + 1;
	int left = j - 1;

	alive += inCells(up, left) ? cells[up][left]: 0;
	alive += inCells(up, j) ? cells[up][j]: 0;
	alive += inCells(up, right) ? cells[up][right]: 0;
	alive += inCells(i, left) ? cells[i][left]: 0;
	alive += inCells(i, right) ? cells[i][right]: 0;
	alive += inCells(down, left) ? cells[down][left]: 0;
	alive += inCells(down, j) ? cells[down][j]: 0;
	alive += inCells(down, right) ? cells[down][right]: 0;
	return alive;
}

void Game::update() {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			int neighbours = calculateNeighbours(i, j);

			if (cells[i][j] && (neighbours < 2 || neighbours > 3))
				updatedCells[i][j] = false;
			else if (!cells[i][j] && neighbours == 3)
				updatedCells[i][j] = true;
			else
				updatedCells[i][j] = cells[i][j];
		}
	}

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			cells[i][j] = updatedCells[i][j];
		}
	}
}

void Game::display() {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (!cells[i][j]) continue;
			al_draw_filled_rectangle(j * cellSize, i * cellSize, (j + 1) * cellSize, (i + 1) * cellSize, al_map_rgb(0, 0, 0));
		}
	}
}