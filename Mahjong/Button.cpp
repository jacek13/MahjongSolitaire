#include<iostream>

#include<SDL.h>

#include"Button.h"

bool Button::chceckSelected(SDL_Point _point)
{
	bool isSelected = true;

	if (_point.x < buttonPosition->x)
		isSelected = false;
	else if (_point.x > buttonPosition->x + buttonPosition->w)
		isSelected = false;
	else if (_point.y < buttonPosition->y)
		isSelected = false;
	else if (_point.y > buttonPosition->y + buttonPosition->h)
		isSelected = false;

	return isSelected;
}

void Button::init(int _x, int _y, size_t _screenW, size_t _screenH, const char * _text)
{
	buttonPosition = std::make_shared<SDL_Rect>();

	backgroundPosition = std::make_shared<SDL_Rect>();

	text = _text;
	background = DEFAULT;
	scaleRectangle(_screenW, _screenH);
	setPosition(_x,_y);
}

void Button::setPosition(size_t _x, size_t _y)
{
	buttonPosition->x = _x;
	buttonPosition->y = _y;

	backgroundPosition->x = buttonPosition->x - 8;
	backgroundPosition->y = buttonPosition->y - 4;
}

void Button::setText(const char* _text)
{
	text = _text;
}

SDL_Rect * Button::getButtonPosition()
{
	return buttonPosition.get();
}

SDL_Rect* Button::getBackgroundPosition()
{
	return backgroundPosition.get();
}

std::string Button::getText()
{
	return text;
}

TILE_TYPE Button::getBackground()
{
	return background;
}

void Button::scaleRectangle(size_t _screenW, size_t _screenH)
{
	buttonPosition->w = (_screenW / 45) * text.size();
	buttonPosition->h = _screenH / 12;

	backgroundPosition->w = buttonPosition->w + 16;
	backgroundPosition->h = buttonPosition->h + 8;
}

Button::~Button()
{
	//Po zastosowaniu inteligentnych wskaźników zwalnianie pamięci nie jest potrzebne
	//if (position)
	//	delete position;
	//position = nullptr;
}