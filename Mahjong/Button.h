/*****************************************************************//**
 * \file   $FILENAME
 *
 * \author Michal Jackowski
 * \date   Thursday March 21 18:52:13 2021
 *********************************************************************/

#pragma once

#include<iostream>
#include<string>

#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<SDL_mixer.h>

#include"Enum.h"

/**
 * Rezprezentuje przycisk funkcyjny lub napis.
 */
class Button
{
private:
	std::shared_ptr<SDL_Rect>buttonPosition = nullptr;		///< wskaźnik do pozycji oraz rozmiaru napisu
	std::shared_ptr<SDL_Rect>backgroundPosition = nullptr;	///< wskaźnik do pozycji oraz rozmiaru tła
	std::string text;										///< treść napisu
	TILE_TYPE background;									///< tekstura tła

public:
	/**
	 * Inicjalizuje przycisk.
	 * 
	 * \param[in] _x współrzędna X przycisku 
	 * \param[in] _y współrzędna Y przycisku
	 * \param[in] _screenW szerokość ekranu
	 * \param[in] _screenH wysokość ekranu
	 * \param[in] _text treść wyświetlana w środku przycisku
	 */
	void init(int _x, int _y, size_t _screenW, size_t _screenH, const char* _text = "");

	/** Destruktor */
	~Button();

	/**
	 * Umożliwia sprawdzenie stanu przycisku.
	 * 
	 * \param[in] _point współrzędna myszki
	 * \return true jeżeli użytkownik kliknął w przycisk, w przeciwnym wypadku false
	 */
	bool chceckSelected(SDL_Point _point);

	/** Umożliwia nadanie nowych współrzędnych */
	void setPosition(size_t _x, size_t _y);

	/** Umożliwia zmianę treści przycisku */
	void setText(const char * _text);

	/** Skaluje rozmiar przycisku w zależność od szerokości i wysokości okna */
	void scaleRectangle(size_t _screenW, size_t _screenH);

	/** Umożliwia dostęp do pozycji przycisku */
	SDL_Rect * getButtonPosition();

	/** Umożliwia dostęp do pozycji tła przycisku */
	SDL_Rect * getBackgroundPosition();

	/** Umożliwia dostęp do treści przycisku */
	std::string getText();

	/** Umożliwia dostęp do tekstury tła przycisku */
	TILE_TYPE getBackground();
};