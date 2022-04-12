/*****************************************************************//**
 * \file   $FILENAME
 *
 * \author Michal Jackowski
 * \date   Thursday March 21 18:52:13 2021
 *********************************************************************/

#pragma once

#include<iostream>
#include<vector>
#include<queue>
#include<utility>
#include<string>
#include<chrono>

#include"Observer.h"
#include"fileSystem.h"
#include"Enum.h"

/**
 * Klasa Achievements odpowiada za zarządzanie osiągnięciami.
 */
class Achievements : public Observer, public fileSystem_Achievements
{
private:

	std::queue<std::pair<std::string,std::chrono::duration<double>>>toDisplay; /*!< Kolejka zawierająca informacje o osiągnięciach do wyświetlenia. Zastosowanie kolejki zapobiegnie ewentualnemu nałożeniu się
																			   kilku odblokowanych osiągnieć. Szablon pary ułatwi przechowywanie informacji. Dzięki temu w prosty
																			   sposób możemy dostać się do treści oraz dokonać pomiaru czasu trwania pojedynczego wyświetlania. */

	/**
	 * Odblokowuje dane osiągnięce jeżeli nie zostało jeszcze osiągnięte.
	 * 
	 * \param[in] _achievement wejściowa enumeracja wskazuje osiągnięcie, które można odblokować
	 */
	void unlock(ACHIEVEMENT _achievement);

public:
	/** 
	 * Konstruktor domyślny.
	 * 
	 * Wywołuje metodę load z obiektu fileSystem_Achievments w celu sprawdzenia które osiągnięcia są już odblokowane
	 */
	Achievements() { load(); }

	/**
	 * Destruktor.
	 * 
	 * Wywołuje metodę save z obiektu fileSystem_Achievments w celu zapisania dotychczasowych osiągnięć
	 */
	~Achievements() { save(true); }
	
	/**
	 * Metoda ta odpowiednio interpretuje obserwowane zdarzenie.
	 * 
	 * \param[in] _event enumeracja symbolizująca dane zdarzenie
	 */
	virtual void onNotify(GAME_EVENT _event);

	/** Usuwa najstarszą informacje o osiągnięciu z obiektu std::queue<...>toDisplay. */
	void removeAchievmentFromQueue();

	/**
	 * Dodaje wartosc argumentu do zmiennej znajdujacej sie w obiekcie std::queue<...>toDisplay.second.
	 * 
	 * \param _duration wartość którą należy dodać do czasu wyświetlania informacji o osiągnięciu
	 */
	void addDuration(double _duration) noexcept;


	/**
	 * Metoda zwraca nazwę osiągnięcia znajdującego się z przodu kolejki.
	 * 
	 * \return nazwa osiągnięcia
	 */
	std::string getAchievementFromQueue();

	/**
	 * Sprawdza czy w kolejce znajduje się jakaś informacja do wyświetlenia.
	 * 
	 * \return true jeżeli jest informacja do wyświetlenia, w przeciwnym wypadku false
	 */
	bool isAchievementToDisplay();

	/**
	 * Metoda zwraca ile czasu wyświetla się już informacja o osiągnięciu.
	 * 
	 * \return aktualny czas wyświetlania informacji
	 */
	double getDurationTime();
};