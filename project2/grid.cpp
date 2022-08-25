#include "grid.h"
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
using namespace std;

Grid::Grid(int col, int row, Vector2f cellsize, Color colorgrid, Color colorline, double thickness)
	: cols(col), rows(row), cellSize(cellsize), color_grid(colorgrid), color_line(colorline), Thickness(thickness)
{
	cout << "Grid()" << endl;
	grid = new RectangleShape * [col];
}
void Grid::draw_grid(RenderWindow& window, View& view)
{
	window.setView(view);
	for (int i = 0; i < cols; i++) {
		for (int j = 0; j < rows; j++) {
			window.draw(grid[i][j]);
		}
	}
}
void Grid::create_grid() 
{
	for (int i = 0; i < cols; i++) {
		grid[i] = new RectangleShape[rows];
		for (int j = 0; j < rows; j++) {
			grid[i][j].setSize(cellSize);
			grid[i][j].setFillColor(color_grid);
			grid[i][j].setOutlineColor(color_line);
			grid[i][j].setOutlineThickness(Thickness);
			grid[i][j].setPosition(i * cellSize.x + 1, j * cellSize.y + 1);
		}
	}
}
Grid::~Grid()
{
	cout << "~Grid()" << endl;
	for (int i = 0; i < cols; i++)
	{
		delete[] grid[i];
	}
	delete[] grid;
}