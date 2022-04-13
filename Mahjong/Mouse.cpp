#include<iostream>
#include<string>

#include"SDL.h"

#include"Mouse.h"

void Mouse::handleEvent(SDL_Event* _event)
{
	switch (_event->type)
	{
	case SDL_MOUSEMOTION:
		SDL_GetMouseState(&x, &y);
		if (buttonDown)
			isClicked = false;
		break;
	case SDL_MOUSEBUTTONDOWN:
		SDL_GetMouseState(&x, &y);
		if (!isClicked && !buttonDown)
			buttonDown = isClicked = true;
		break;
	case SDL_MOUSEBUTTONUP:
		SDL_GetMouseState(&x, &y);
		buttonDown = isClicked = false;
		break;
	default:
		break;
	}
}

SDL_Point Mouse::getPosition()
{
	return {x,y};
}

bool Mouse::checkMouseClick()
{
	return isClicked;
}