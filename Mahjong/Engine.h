/*****************************************************************//**
 * \file   $FILENAME
 *
 * \author Michal Jackowski
 * \date   Thursday March 21 18:52:13 2021
 *********************************************************************/

#pragma once

//Biblioteki Standardowe
#include<iostream>
#include<vector>

//Biblioteki zewnętrzne
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<SDL_mixer.h>

//Biblioteki programu
#include"structures.h"
#include"fileSystem.h"

/**
 * Odpowiada za obsługę biblioteki SDL.
 */
class Engine : public fileSystem_Engine
{
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Surface* icon;
	TTF_Font* font;
	std::vector<Mix_Chunk*>sounds;
	std::vector<SDL_Texture*>textures;
	settings config;

public:
	//Kontruktoy

	/** Konstruktor domyślny */
	Engine() :
		window(nullptr), renderer(nullptr), icon(nullptr), font(nullptr), config({ false,true,1280,720,0,0,0,255,37,150,190,255 }) {}

	/**
	 * Konstruktor parametryczny.
	 * 
	 * \param[in] _config informacje zawarte w pliku konfiguracyjnym
	 */
	Engine(settings _config) :
		window(nullptr), renderer(nullptr), icon(nullptr), font(nullptr), config(_config) {}

	//Destruktor

	/** Destruktor zwalniający poszczególne moduły SDL */
	~Engine();

	/** Inicjalizuje wybrane moduły SDL */
	bool init() noexcept;

	/** Wczytuje potrzebne zasoby (tekstury, czcionki itp.) */
	bool loadResources();

	/**
	 * Rysuje pojedynczy kafelek.
	 * 
	 * \param[in] _cord współrzedne kafelka na ekranie
	 * \param[in] _tileType typ kafelka
	 * \param[in] _isSelected status wybrania kafelka
	 * \param[in] _helpEnable status wybrania kafelka (przez metodę markPair())
	 */
	void drawTile(SDL_Rect* _cord, TILE_TYPE _tileType, bool _isSelected = false, bool _helpEnable = false) noexcept;

	/** Rysuje aktualny stan renderera */
	void drawCurrentState() noexcept;

	/** Czyści aktualny stan renderera */
	void clearCurrentState() noexcept;

	/**
	 * Umożliwia ryswanie tekstu.
	 * 
	 * \param _cord współrzędne tekstu na ekranie
	 * \param _text treść napisu do wyświetlenia
	 */
	void drawText(SDL_Rect* _cord, const char* _text) noexcept;

	/**
	 * Umożliwia wczytywanie poweirzchni.
	 * 
	 * \param[in] _path ścieżka do powierzchni
	 * \return wskaźnik do nowo utworzonej powierzchni
	 */
	SDL_Surface* loadSurface(const char* _path);

	/**
	 * Umożliwia wczytywanie tekstury.
	 * 
	 * \param[in] _path ścieżka do tekstury
	 * \return nowo utworzona tekstura
	 */
	SDL_Texture* loadTexture(const char* _path);
};