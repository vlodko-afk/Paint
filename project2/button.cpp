#include "button.h"
#include <vector>
#include <string>
#include "grid_fon.h"
#include <iostream>
using namespace sf;
using namespace std;


void Button::load_texture(Texture& texture, string path)
	{
	if (!texture.loadFromFile(path))
		{
			cerr << "failed to load image" << endl;
			exit(1);
		}
	}

void Button::check_union_element(vector<vector<key>>& array_, bool& flag, int col)
{
	if (flag != true)
	{
		array_.push_back(operation_with_color[col]);
	}
	else
	{
		flag = false;
	}
}


Button::Button(string path_left, string path_right, View button_left, View button_right)
{
	this->path_left = path_left;
	this->path_right = path_right;

	load_texture(texture, path_left);
	load_texture(texture1, path_right);
	this->button_left = button_left;
	this->button_right = button_right;
	sprite.setTexture(texture);
	sprite2.setTexture(texture1);

	Bound_left = sprite.getGlobalBounds();
	Bound_right = sprite2.getGlobalBounds();
}

void Button::Button_work(RenderWindow& window, Event& event, Grid_fon& grid_f)
{
	Vector2f mousepos_left = window.mapPixelToCoords({ event.mouseButton.x,event.mouseButton.y }, button_left);
	Vector2f mousepos_right = window.mapPixelToCoords({ event.mouseButton.x,event.mouseButton.y }, button_right);
	if (Bound_left.contains(mousepos_left))
	{
		if ((operation_with_color.size() - count_p) != 0)
		{
			Flag_button = false;
			count_p += 1;
			count_pos = (int)operation_with_color.size() - count_p;
			key* data = operation_with_color[count_pos].data();
			grid_f.grid[data->col_grid][data->row_grid].setFillColor(data->color_change);
		}
	}
	else if (Bound_right.contains(mousepos_right))
	{
		if (operation_with_color.size() > count_pos && count_p != 0)
		{
			Flag_button = true;
			count_pos = (int)operation_with_color.size() - count_p;
			count_p -= 1;
			key* data = operation_with_color[count_pos].data();
			grid_f.grid[data->col_grid][data->row_grid].setFillColor(data->color_draw);
		}
	}
}
void Button::change_work(int col, int row, Color color_draw, Color color_change)
{
	vector<vector<key>> change_mas;
	bool flag = false;
	if (count_p != 0)
	{
		if (Flag_button == false)
		{
			for (int i = 0; i < count_pos; i++)
			{
				for (int j = i + 1; j < count_pos; j++)
				{
					if (operation_with_color[i].data() == operation_with_color[j].data() && j != i)
					{
						flag = true;
						break;
					}
				}
				check_union_element(change_mas, flag, i); 
			}
		}
		else
		{
			for (int i = 0; i <= count_pos; i++)
			{
				for (int j = i + 1; j <= count_pos; j++)
				{
					if (operation_with_color[i].data() == operation_with_color[j].data() && j != i)
					{
						flag = true;
						break;
					}
				}
				check_union_element(change_mas, flag, i);
			}
		}
		operation_with_color = change_mas;
		count_p = 0;
	}
	key intializtion_key;
	intializtion_key = { col, row, color_draw, color_change };
	operation_with_color.push_back({ intializtion_key });
	count_pos = 1;
}
void Button::draw_sprites(RenderWindow& window)
{
	window.setView(button_left);
	window.draw(sprite);
	window.setView(button_right);
	window.draw(sprite2);
}
