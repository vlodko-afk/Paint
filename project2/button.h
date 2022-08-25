#pragma once
#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "grid_fon.h"

using namespace sf;
using namespace std;

struct key
{
	int col_grid = 0;
	int row_grid = 0;
	Color color_draw;
	Color color_change;
};

class Button : public key
{
private:
	string path_left, path_right;

	View button_left;
	View button_right;

	Sprite sprite, sprite2;

	Texture texture, texture1;

	FloatRect Bound_left;
	FloatRect Bound_right;

	vector<vector<key>> operation_with_color;

	bool Flag_button = false;
	int count_pos = 0, count_p = 0;

	void load_texture(Texture& texture, string path);
	void check_union_element(vector<vector<key>>& array_, bool& flag, int col);

public:

	Button(string path_left, string path_right, View button_left, View button_right);

	void Button_work(RenderWindow& window, Event& event, Grid_fon& grid_f);

	void change_work(int col, int row, Color color_draw, Color color_change);

	void draw_sprites(RenderWindow& window);
};

#endif