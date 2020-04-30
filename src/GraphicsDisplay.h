#ifndef _GRAPHICSDISPLAY_H_
#define _GRAPHICSDISPLAY_H_

#include <vector>
#include "GraphicsDisplayCell.h"
#include "window.h"

class GraphicsDisplay {
	int size;
	int cellSize;
	std::vector<std::vector<GraphicsDisplayCell>> gridDisplay;
	Xwindow *w;
public:
	GraphicsDisplay(int size, std::vector<std::vector<Cell>> *grid, int gridSize);
	~GraphicsDisplay();
	void refresh();
};

#endif
