#pragma once
#ifndef MAINLOOP_H
#define MAINLOOP_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include "grid.h"
#include "grid_fon.h"
#include "grid_palitra.h"
#include "button.h"
#include "SetStruct.h"
using namespace sf;
using namespace std;

namespace MAINLOOP
{
	void MAINLOOP()
	{
		float y_moving = getdefaultView.getCenter.y, x_moving = getdefaultView.getCenter.y, zoom = 1;
		// Flag for event move and grid
		bool movin_left = false, Flag_palitra = false, moving = false;
		// Create color and vector data type
		Vector2f oldPos, deltaPos;
		Color color_draw(Color::White), color_border(Color::Black), color_change(Color::White);

		// Create window 
		RenderWindow window(VideoMode(img.cols * 10, (img.rows + 10) * 12), "SFML Works", 4);

		//initialization view color fon
		View view(getdefaultView.getCenter, getdefaultView.getSize);
		view.setViewport(FloatRect(0, 0, 1, 0.755));

		// initialization view color palitra
		View control_panel(getdefaultViewPanel.getCenter, getdefaultViewPanel.getSize);
		control_panel.setViewport(FloatRect(0.01f, 0.76f, 0.4f, 0.24f));

		// Create View button left
		View button_left(getdefaultViewButton.getCenter, getdefaultViewButton.getSize);
		button_left.setViewport(FloatRect(0.41f, 0.763f, 0.7f, 0.24f));

		// Create View button right
		View button_right(getdefaultViewButton.getCenter, getdefaultViewButton.getSize);
		button_right.setViewport(FloatRect(0.71f, 0.763f, 0.7f, 0.24f));

		// initialization class Button
		Button logic_but("images\\Button_left.png", "images\\Button_right.png", button_left, button_right);

		// Create parameters grid
		const Vector2f cellSize(10, 9), cellSizePalitra(20, 7);
		const float th = 0.85f;
		const int n = 16, m = 16;

		// initialization class Grid Palitra
		Grid_palitra grid_p(n, m, cellSizePalitra, color_draw, color_draw, 0.6);
		grid_p.create_grid();
		grid_p.view_palitra();

		// initialization class Grid Fon
		Grid_fon grid_f(img.cols, img.rows, cellSize, color_draw, color_border, th);
		grid_f.create_grid();

		while (window.isOpen())
		{
			Event event;
			while (window.pollEvent(event))
			{
				switch (event.type)
				{
				case Event::Closed:
				{
					window.close();
					break;
				}
				case Event::MouseButtonPressed:
				{
					if (event.mouseButton.button == Mouse::Right) {
						moving = true;
						oldPos = window.mapPixelToCoords(Vector2i(event.mouseButton.x, event.mouseButton.y), view);
					}
					else if (event.mouseButton.button == Mouse::Left)
					{
						if (event.mouseButton.x <= img.cols * 10 && event.mouseButton.y <= img.rows * 10.5 && Flag_palitra == true)
						{
							Vector2f mousepos = window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y }, view);
							float col = mousepos.x / 10, row = mousepos.y / 9;
							if (col < img.cols && row < img.rows)
							{
								grid_f.find_cell((int)col, (int)row, window, color_draw, color_change);
								logic_but.change_work(col, row, color_draw, color_change);
							}
							movin_left = true;
						}
						else
						{
							Vector2f mousepos = window.mapPixelToCoords({ event.mouseButton.x,event.mouseButton.y }, control_panel);
							int row = (int)mousepos.x / 20, col = (int)mousepos.y / 7;
							if ((row >= 0 && row <= 15) && (col >= 0 && col <= 15) && mousepos.y >= 0 && mousepos.x >= 0)
							{
								Flag_palitra = true;
								color_draw = grid_p.grid[row][col].getFillColor();
							}
							else
							{
								logic_but.Button_work(window, event, grid_f);
							}
						}
					}
					break;
				}
				case Event::MouseWheelScrolled:
				{
					if (moving)
						break;

					if (event.mouseWheelScroll.delta <= -1)
					{
						zoom = (zoom == .1f) ? min(1.f, zoom + .4f) : min(1.f, zoom + .5f);
					}
					else if (event.mouseWheelScroll.delta >= 1)
					{
						zoom = max(.1f, zoom - .5f);

					}
					x_moving = ((1000) - (1000 * zoom)) / 2,
						y_moving = ((543) - (543 * zoom)) / 2;
					view.setSize(getdefaultView.getSize);
					view.setCenter(getdefaultView.getCenter);
					view.zoom(zoom);
					break;
				}
				case Event::MouseButtonReleased:
					if (event.mouseButton.button == Mouse::Right) {
						moving = false;
					}
					else if (event.mouseButton.button == Mouse::Left)
					{
						movin_left = false;
					}
					break;
				case Event::MouseMoved:
				{
					if (moving && zoom != 1)
					{
						Vector2f newPos = window.mapPixelToCoords({ event.mouseMove.x, event.mouseMove.y }, view);
						deltaPos = oldPos - newPos;
						if ((x_moving + deltaPos.x) >= 0 && (x_moving + deltaPos.x) <= (1000 - (1000 * zoom)))
						{
							x_moving += deltaPos.x;
							view.setCenter(view.getCenter() + Vector2f({ deltaPos.x, 0 }));
						}
						cout << "x " << x_moving << endl;
						cout << "y " << y_moving << endl;
						if ((y_moving + deltaPos.y) >= 0 && (y_moving + deltaPos.y) <= (543 - (543 * zoom)))
						{
							y_moving += deltaPos.y;
							view.setCenter(view.getCenter() + Vector2f({ 0, deltaPos.y }));
						}
						oldPos = window.mapPixelToCoords(Vector2i(event.mouseMove.x, event.mouseMove.y), view);
					}
					else if (movin_left)
					{
						Vector2f mouse = window.mapPixelToCoords({ event.mouseMove.x, event.mouseMove.y }, view);
						float col = mouse.x / 10, row = mouse.y / 9;
						cout << col << endl;  
						cout << row << endl;
						if ((col < img.cols && row < img.rows) && (col >= 0 && row >= 0))
						{
							grid_f.find_cell((int)col, (int)row, window, color_draw, color_change);
							logic_but.change_work(col, row, color_draw, color_change);
						}
					}
				}
				}
			}
			window.clear(Color::White);
			grid_p.draw_grid(window, control_panel);
			grid_f.draw_grid(window, view);
			logic_but.draw_sprites(window);
			window.display();
		}
	}
}

#endif