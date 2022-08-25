#include "grid_palitra.h"
#include <SFML/Graphics.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
using namespace sf;
using namespace cv;
using namespace std;

Grid_palitra::Grid_palitra(int cols, int rows, Vector2f cellSize, Color color_grid, Color color_line, double Thickness)
	: Grid(cols, rows, cellSize, color_grid, color_line, Thickness)
{
	cout << "Grid_palitra()"<< endl;
}

void Grid_palitra::view_palitra() const
{
	Mat colors_pallete = imread("images\\color palette.png");
	float palitra_row = 0;
	for (int i = 0; i < rows; i++)
	{
		float palitra_col = 0;
		for (int j = 0; j < cols; j++)
		{
			vector<int> arr;
			for (int K = 0; K < 3; K++)
			{
				if (palitra_row <= colors_pallete.rows && palitra_col <= colors_pallete.cols)
				{
					arr.push_back(static_cast<int>(colors_pallete.at<Vec3b>(palitra_row, palitra_col)[K]));
				}
				else {
					if (palitra_row > colors_pallete.rows && palitra_col <= colors_pallete.cols)
					{
						arr.push_back(static_cast<int>(colors_pallete.at<Vec3b>(colors_pallete.rows, palitra_col)[K]));
					}
					else if (palitra_col > colors_pallete.cols && palitra_row <= colors_pallete.rows)
					{
						arr.push_back(static_cast<int>(colors_pallete.at<Vec3b>(palitra_row, colors_pallete.cols)[K]));
					}
					else
					{
						arr.push_back(static_cast<int>(colors_pallete.at<Vec3b>(colors_pallete.rows, colors_pallete.cols)[K]));
					}
				}
			}
			grid[i][j].setFillColor(Color(arr[2], arr[1], arr[0]));
			palitra_col += 36;
		}
		palitra_row += 27;
	}
}

void Grid_palitra::create_grid() 
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

Grid_palitra::~Grid_palitra()
{
	cout << "~Grid_palitra()" << endl;
}