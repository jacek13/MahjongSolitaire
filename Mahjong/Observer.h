/*****************************************************************//**
 * \file   $FILENAME
 *
 * \author Michal Jackowski
 * \date   Thursday March 21 18:52:13 2021
 *********************************************************************/

#pragma once

#include<iostream>

#include"Enum.h"


/**
* Klasa obserwator jest obiektem związanym ze wzorcem projektowym Observer.
* 
* Pełni ona rolę interfejsu.
*/
class Observer
{
public:
	virtual void onNotify(GAME_EVENT _event) = 0;
	virtual ~Observer() {};
};