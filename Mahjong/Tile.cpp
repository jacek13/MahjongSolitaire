#include<iostream>

#include"SDL.h"
#include"SDL_image.h"
#include"SDL_ttf.h"
#include"SDL_mixer.h"

#include"Tile.h"
#include"structures.h"
#include"Enum.h"

void Tile::init(bool _active, bool _accessibility, bool _selected, bool _help, position _pos, SDL_Rect _cord, TILE_TYPE _tileType, rgbaColour _colour)
{
	active = _active;
	selected = _selected;
	help = _help;
	pos = _pos;
	cord = std::make_shared<SDL_Rect>();
	cord->x = _cord.x;
	cord->y = _cord.y;
	cord->h = _cord.h;
	cord->w = _cord.w;
	tileType = _tileType;
	colour = _colour;
}

void Tile::scaleTile(size_t screenW, size_t screenH, size_t _maxX, size_t _maxY)
{
	cord->w = (double)screenW / _maxX * 0.75;
	cord->h = (double)screenH / _maxY * 0.75;
}

SDL_Rect * Tile::getCoOrdinates()
{
	return cord.get();
}

TILE_TYPE Tile::getTileType()
{
	return tileType;
}

void Tile::setCoOrdinates(SDL_Rect _cord)
{
	cord->x = _cord.x;
	cord->y = _cord.y;
	cord->h = _cord.h;
	cord->w = _cord.w;
}

void Tile::setTileType(TILE_TYPE _tileTexture)
{
	tileType = _tileTexture;
}

bool Tile::getActive()
{
	return active;
}

void Tile::setActive(bool _active)
{
	active = _active;
}

void Tile::setAccessibility(bool _accessibility)
{
	accessibility = _accessibility;
}

position Tile::getPosition()
{
	return pos;
}

bool Tile::getSelected()
{
	return selected;
}

bool Tile::getHelpInfo()
{
	return help;
}

void Tile::setHelpInfo(bool _help)
{
	help = _help;
}

void Tile::setSelected(bool _selected)
{
	selected = _selected;
}

void Tile::setPosition(position _pos)
{
	pos = _pos;
}

Tile::~Tile()
{
	//Po zastosowaniu inteligentnych wskaźników zwalnianie pamięci nie jest potrzebne
	//delete cord;
	//cord = nullptr;
}