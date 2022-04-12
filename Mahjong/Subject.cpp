#include<iostream>

#include"Subject.h"

void Subject::notify(GAME_EVENT _event)
{
	for (size_t i = 0; i < observers.size(); i++)
		observers.at(i)->onNotify(_event);
}

void Subject::addObserver(Observer* _observer)
{
	observers.push_back(_observer);
}