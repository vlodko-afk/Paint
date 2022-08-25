#pragma once
#ifndef GRID_H
#define GRID_H

#include <SFML/Graphics.hpp>
using namespace sf;

class Grid
{
	
public:
	int cols{}, rows{};
	Vector2f cellSize{};
	RectangleShape** grid{};
	Color color_grid{};
	Color color_line{};
	float Thickness{};
	void draw_grid(RenderWindow& window, View& view);
	virtual void create_grid();

protected:
	Grid(int col, int row, Vector2f cellsize, Color colorgrid, Color colorline, double thickness);
	~Grid();
};

#endif