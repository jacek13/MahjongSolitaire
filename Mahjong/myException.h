/*****************************************************************//**
 * \file   $FILENAME
 *
 * \author Michal Jackowski
 * \date   Thursday March 21 18:52:13 2021
 *********************************************************************/

#pragma once

#include<iostream>
#include<exception>

/**
 * Klasa myException pełni rolę interfejsu.
 */
class myException : public std::exception
{
protected:
	std::string message; ///< informacja o zaistniałym wyjątku
public:
	/**
	 * Konstruktor.
	 * 
	 * \param[in] _message treść jaką obiekt będzie przechowywał
	 */
	myException(const char* _message) :
		message(_message) {}

	/**
	 * Umożliwia zwrócenie zawartości przechowywanej przez wyjątek.
	 * 
	 * \return treść wyjątku
	 */
	virtual const char* what() const noexcept override;
};


/// Klasa wyjątku dla obiektu Engine
class myException_Engine : public myException
{
public:
	myException_Engine(const char* _message) :
		myException(_message) {}
	virtual const char* what() const noexcept override;
};

/// Klasa wyjątku dla obiektu fileSystem
class myException_fileSystem : public myException
{
public:
	myException_fileSystem(const char* _message) :
		myException(_message) {}
	virtual const char* what() const noexcept override;
};

/// Klasa wyjątku dla obiektu Board
class myException_Board : public myException
{
public:
	myException_Board(const char * _message) :
		myException(_message) {}
	virtual const char* what() const noexcept override;
};
