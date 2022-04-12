/*****************************************************************//**
 * \file   $FILENAME
 *
 * \author Michal Jackowski
 * \date   Thursday March 21 18:52:13 2021
 *********************************************************************/

#pragma once
#include<iostream>

#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<SDL_mixer.h>

#include"structures.h"
#include"Enum.h"

/**
 * Klasa reprezentuje pojedynczą płytkę na planszy.
 */
class Tile
{
private:
	bool active = false;						///< mówi o tym czy można wchodzić z obiektem w jakąś interakcję
	bool accessibility = false;					///< mówi o tym czy dana płytka jest zablokowana
	bool selected = false;						///< mówi o tym czy dana płytka została wybrana przez gracza
	bool help = false;							///< mówi o tym czy dana płytka została podkreślona do podpowiedzi
	position pos = { 0,0,0 };					///< jest to indeks danej płytki w strukturze 3-wymiarowej
	std::shared_ptr<SDL_Rect>cord = nullptr;	///< jest to współrzedna i rozmiar płytki wyświetlanej na ekranie
	TILE_TYPE tileType = EMPTY;					///< rodzaj płytki
	rgbaColour colour = { 208,211,212,255 };	///< kolor w formacie rgba

public:
	/**
	 * Inicjalizuje atrybuty przechowywane przez obiekt.
	 * 
	 * \param[in] _active określa aktywność danego elementu
	 * \param[in] _accessibility określa dostępność płytki
	 * \param[in] _selected określa płytkę wybraną do ściągnięcia
	 * \param[in] _help określa płytkę wskazaną przez metodę help 
	 * \param[in] _pos określa pozycję płytki w struktórze 3-wymiarowej
	 * \param[in] _cord określa pozycję płytki na ekranie
	 * \param[in] _tileType określa typ płytki
	 * \param[in] _colour określa kolor w formacie rgba
	 */
	void init(bool _active, bool _accessibility, bool _selected, bool _help, position _pos, SDL_Rect _cord, TILE_TYPE _tileType, rgbaColour _colour = { 208,211,212,255 });

	/** Destruktor */
	~Tile();

	/**
	 * Skaluje rozmiar danej płytki bazując na danych wejściowych.
	 * 
	 * \param[in] screenW szerokość ekranu
	 * \param[in] screenH wysokość ekranu
	 * \param[in] _maxX maksymalna ilość płytek w osi X
	 * \param[in] _maxY maksymalna ilość płytek w osi Y
	 */
	void scaleTile(size_t screenW, size_t screenH, size_t _maxX, size_t _maxY);

	//getters

	/**
	 * Umożliwia sprawdzenie aktywności płytki.
	 * 
	 * \return true jeżeli płytka ma status aktywny, czyli program ma ją wyświetlać na ekranie. W przeciwnym wypadku zwraca false
	 */
	bool getActive();

	/**
	 * Umożliwia sprawdzenie czy dana płytka została wybrana przez użytkownika.
	 * 
	 * \return true jeżeli płytka ma status wybranej płytki, w przeciwnym wypadku zwraca false
	 */
	bool getSelected();

	/**
	 * Umożliwia sprawdzenie czy dana płytka została wybrana przez metodę help.
	 * 
	 * \return true jeżeli płytka ma status płytki wskazanej do podpowiedzi, w przeciwnym wypadku false
	 */
	bool getHelpInfo();

	/**
	 * Umożliwia sprawdzenie pozycji danej płytki w sturkturze 3-wymiarowego vectora.
	 * 
	 * \return pozycję (indeksy: i,j,k) w strukturze 3-wymiarowej
	 */
	position getPosition();

	/**
	 * Umożliwia dostęp do informacji o pozycji/rozmiarze płytki na ekranie.
	 * 
	 * \return koordynaty oraz rozmiar płytki wyświetlanej na ekranie
	 */
	SDL_Rect * getCoOrdinates();

	/**
	 * Umożliwia sprawdzenie typu danej płytki.
	 * 
	 * \return typ płytki
	 */
	TILE_TYPE getTileType();

	//setters

	/**
	 * Umożliwia ustawienie aktywności.
	 * 
	 * \param[in] _active określa aktywność płytki
	 */
	void setActive(bool _active);

	/**
	 * Umożliwia ustawienie dostępności płytki (czy płyka jest zablokowana czy też nie).
	 * 
	 * \param _accessibility[in] określa dostępność płytki
	 */
	void setAccessibility(bool _accessibility);

	/**
	 * Umożliwia ustawienie informacji o wybraniu płytki przez użytkownika.
	 * 
	 * \param _selected określa status wyboru płytki
	 */
	void setSelected(bool _selected);

	/**
	 * Umożliwia ustawienie informacji o wybraniu płrzytki przez metodę markPair() obiektu Board.
	 * 
	 * \param _help określa status wyboru płytki do pomocy
	 */
	void setHelpInfo(bool _help);

	/**
	 * Umożliwia ustawienie pozycji w strukturze 3-wymiarowego vektora.
	 * 
	 * \param _pos[in] pozycja (indeksy: i,j,k) w strukturze 3-wymiarowej
	 */
	void setPosition(position _pos);

	/**
	 * Umożliwia ustawienie współrzednej płytki na ekranie.
	 * 
	 * \param _cord współrzedna do ustawienia
	 */
	void setCoOrdinates(SDL_Rect _cord);

	/**
	 * Umożliwia ustawienie typu płytki.
	 * 
	 * \param _tileTexture typ płytki
	 */
	void setTileType(TILE_TYPE _tileTexture);
};