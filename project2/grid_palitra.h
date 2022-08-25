#pragma once
#ifndef GRID_PALITRA_H
#define GRID_PALITRA_H

#include "grid.h"
#include <SFML/Graphics.hpp>

using namespace sf;

class Grid_palitra : public Grid
{
	/*RectangleShape** grid_palitra;
	int cols, rows;
	Vector2f cellSize;
	Color color_grid;
	Color color_line;
	double Thickness;*/
public:
	Grid_palitra(int cols, int rows, Vector2f cellSize, Color color_grid, Color color_line, double Thickness);
	void view_palitra() const;
	void create_grid() override;
	~Grid_palitra();
};

#endif