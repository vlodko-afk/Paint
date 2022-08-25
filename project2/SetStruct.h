#pragma once
#ifndef SET_STRUCT_H
#define SET_STRUCT_H

#include <SFML/Graphics.hpp>
using namespace sf;

struct {
	const int cols = 100;
	const int rows = 60;
}img;

struct {
	const Vector2f getCenter{ static_cast<float> (350), static_cast<float>(110) };
	const Vector2f getSize{ static_cast<float> (700) , static_cast<float>(220) };
}getdefaultViewButton;

struct {
	const Vector2f getCenter{ static_cast<float>(img.cols * 10 / 2), static_cast<int>((543) / 2) };
	const Vector2f getSize{ static_cast<float>(img.cols * 10) , static_cast<int>(543) };
}getdefaultView;

struct {
	const Vector2f getCenter{ static_cast<float>((img.cols * 10 / 2) * 0.4), static_cast<float>((img.rows * 12 - img.rows * 10) / 2) };
	const Vector2f getSize{ static_cast<float>((img.cols * 10) * 0.4) , static_cast<float>(img.rows * 12 - img.rows * 10) };
}getdefaultViewPanel;

#endif