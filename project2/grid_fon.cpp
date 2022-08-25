#include "grid_fon.h"
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

Grid_fon::Grid_fon(int cols, int rows, Vector2f cellSize, Color color_grid, Color color_line, float Thickness)
	: Grid(cols, rows, cellSize, color_grid, color_line, Thickness)
{
	cout << "Grid_fon" << endl;
}
void Grid_fon::find_cell(int col, int row, RenderWindow& window, Color& color, Color& color_change)
{
	color_change = grid[col][row].getFillColor();
	grid[col][row].setFillColor(color);
	window.draw(grid[col][row]);
}
Grid_fon::~Grid_fon()
{
	cout << "~Grid_fon" << endl;
}