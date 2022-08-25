#pragma once
#ifndef GRID_FON_H
#define GRID_FON_H

#include "Grid.h"
#include <SFML/Graphics.hpp>
using namespace sf;

class Grid_fon: public Grid
{
	/*RectangleShape** grid_palitra;
	int cols, rows;
	Vector2f cellSize;
	Color color_grid;
	Color color_line;
	double Thickness;*/
public:
	Grid_fon(int cols, int rows, Vector2f cellSize, Color color_grid, Color color_line, float Thickness);
	void find_cell(int col, int row, RenderWindow& window, Color& color, Color& color_change);
	~Grid_fon();
};

#endif