/*****************************************************************//**
 * \file   $FILENAME
 *
 * \author Michal Jackowski
 * \date   Thursday March 21 18:52:13 2021
 *********************************************************************/

#pragma once

#include<iostream>

#include"Engine.h"
#include"Board.h"
#include"Mouse.h"
#include"Button.h"
#include"structures.h"
#include"timeSystem.h"
#include"Achievements.h"

/**
 * Obiekt zarządzający innymi obiektami.
 */
class Game : public fileSystem_Game
{
private:
	Engine* gameEngine;				///< wskaźnik do silnika gry
	Board* gameBoard;				///< wskaźnik do planszy gry
	Mouse* gameMouse;				///< wskaźnik do obiektu obsługującego mysz
	SDL_Event* gameEvent;			///< wskaźnik do zdarzeń rejestrowanych przez moduł SDL
	timeSystem* gameTime;			///< wkaźnik do systemu obsługującego czas
	Achievements* gameAchievements;	///< wskaźnik do obiektu obsługującego osiągnięcia
	std::vector<Button>gameButtons;	///< przyciski/informacje wyświetlane w grze
	bool gameLoop;					///< flaga pętli gry

public:
	/** Konstruktor domyślny. Ustawia wartośći początkowe oraz wywołuje metodę makeReadMe() */
	Game() :
		fileSystem_Game(), gameEngine(nullptr), gameBoard(nullptr), gameMouse(nullptr), gameEvent(nullptr), gameTime(nullptr), gameAchievements(nullptr), gameLoop(true) 
	{
		fileSystem_Game::makeReadMe("readme.txt");
	}

	/** Destruktor zwalniający obiekty */
	~Game();

	/**
	 * Umożliwia inicjalizacje poszczególnych obiektów z których korzysta gra.
	 * 
	 * W pierwszym kroku wywoływana jest metoda fileSystem_Game::load(). Jeżeli wszelkie niezbędne informacje zostaną
	 * poprawnie wczytane to rozpocznie się procedura alokowania obiektów gameEngine, gameBoard itd.  
	 */
	void init();

	/**
	 * Realizuje pętlę główną gry.
	 * 
	 * Odpowiada za sekwencyjne wywoływanie poszczególnych metod i funkcji.
	 */
	void loop();

	/** Rysuje plansze do gry na ekraniu */
	void drawBoard();

	/**
	 * Rysuje przycisk na ekranie.
	 * 
	 * \param[in] _button przycisk do narysowania
	 */
	void drawButton(Button _button);

	/**
	 * Umożliwia sprawdzenie stanu aktualnej gry.
	 * 
	 * \return true jeśli gra została zakończona, w przeciwnym wypadku false
	 */
	bool isWin();
};