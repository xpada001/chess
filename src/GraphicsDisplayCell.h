#ifndef _GRAPHICSDISPLAYCELL_H_
#define _GRAPHICSDISPLAYCELL_H_

#include <iostream>
#include "Observer.h"
#include "Cell.h"
#include "window.h"

class GraphicsDisplayCell {
	char _char;
	int cellSize;
	Xwindow *w;
	Cell *cell;
	int row;
	int col;
	char lastState;
public:
	GraphicsDisplayCell(int cellSize, Xwindow *w, Cell *c, int row, int col);
	virtual ~GraphicsDisplayCell();
	void refresh();
	void setCell(Cell *c);
	void setPosition(int r, int c);
	int getXOffset();
	int getYOffset();
	CellColor getColor();
	void drawCell();
	void drawState();
	int getPixelSize();
	void drawPixel(int v, int h, int color);
	void drawQueen(int color);
	void drawKing(int color);
	void drawKnight(int color);
	void drawPawn(int color);
	void drawRook(int color);
	void drawBishop(int color);
	char getLastState();
};

#endif
