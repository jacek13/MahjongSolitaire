/*****************************************************************//**
 * \file   $FILENAME
 *
 * \author Michal Jackowski
 * \date   Thursday March 21 18:52:13 2021
 *********************************************************************/

#pragma once

#include<iostream>
#include<vector>

#include"Observer.h"
#include"Enum.h"

/**
 * Klasa podmiotu jest obiektem związanym ze wzorcem projektowym obserwator.
 */
class Subject
{
private:
	std::vector<Observer*>observers;

protected:
	/**
	 * Wysyła powiadomienia do obserwatorów.
	 * 
	 * \param _event typ zdarzenia który zostanie przesłany
	 */
	void notify(GAME_EVENT _event);

public:
	/**
	 * Umożliwia dodanie obserwatora.
	 * 
	 * \param _observer nowy obserwator
	 */
	void addObserver(Observer* _observer);
};