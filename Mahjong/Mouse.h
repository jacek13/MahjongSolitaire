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

/**
 * Reprezentuje obiekt myszy.
 */
class Mouse
{
private:
	int x;						///< współrzędna x myszy
	int y;						///< współrzędna y myszy
	bool isClicked = false;		///< zmienna przechowująca status dotyczący kliknięcia myszki
	bool buttonDown = false;	///< zmienna przechowująca status dotyczący wciśniętego lewego klawisza myszy

public:
	/**
	 * Obsługuje zdarzenia związane z myszką.
	 * 
	 * \param _event zdarzenia rejestrowane przez SDL
	 */
	void handleEvent(SDL_Event* _event);

	/**
	 * Umożliwia dostęp do pozycji myszki na ekranie.
	 * 
	 * \return współrzędne myszy
	 */
	SDL_Point getPosition();

	/**
	 * Umożliwia sprawdzenie statusu kliknięcia.
	 * 
	 * \return true jeżeli użytkownik kliknął, w przeciwnym wypadku false
	 */
	bool checkMouseClick();
};