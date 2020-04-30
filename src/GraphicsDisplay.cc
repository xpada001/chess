#include <vector>
#include <iostream>
#include <sstream>
#include "GraphicsDisplay.h"
#include "Cell.h"

using namespace std;

GraphicsDisplay::GraphicsDisplay(int size, vector<vector<Cell>> *grid, int cellSize):
		size{size}, cellSize{cellSize}, w{new Xwindow(cellSize * size, cellSize * size)}
		{	gridDisplay = vector<vector<GraphicsDisplayCell>>();
			for (int i = 0; i < this->size; ++i) {
				this->gridDisplay.emplace_back(vector<GraphicsDisplayCell>());
				for (int j = 0; j < this->size; ++j) {
					gridDisplay[i].emplace_back(GraphicsDisplayCell(cellSize, w, &((*grid)[this->size-1-i][j]) , i, j));
				}
			}
		}

GraphicsDisplay::~GraphicsDisplay() {
	delete this->w;
}

void GraphicsDisplay::refresh() {
	for (auto &row: this->gridDisplay) {
		for (auto &cell: row) {
			cell.refresh();
		}
	}
}
