/*****************************************************************//**
 * \file   $FILENAME
 *
 * \author Michal Jackowski
 * \date   Thursday March 21 18:52:13 2021
 *********************************************************************/

#pragma once

#include<iostream>
#include<vector>
#include<random>
#include<utility>

#include"structures.h"
#include"fileSystem.h"
#include"Tile.h"

/**
 * Klasa zarządzająca logiką gry.
 */
class Board : public fileSystem_Board
{
private:
	std::vector<Tile*>v1d;
	std::vector<std::vector<Tile*>>v2d{ v1d };

	Tile* firstSelectedTile = nullptr;	///< Pierwsza płytka wybrana przez gracza
	Tile* SecondSelectedTile = nullptr;	///< Druga płytka wybrana przez gracza

	size_t totalNumberOfTiles;	///< aktualna ilość płytek w grze
	size_t maxNumberOfTiles = 0;	///< maksymalna ilość płytek w grze

	size_t maxY;	///< Maksymalna ilość płytek w osi Y
	size_t maxX;	///< Maksymalna ilość płytek w osi X
	size_t maxZ;	///< Maksymalna ilość płytek w osi Z

	//i-ty string to ita linijka wzoru
	// do samych znakow mozna odwolywac się poprzez operator[] lub metode at()
	std::vector<std::string>map;	///< wektor napisów. Przechowuje wzór planszy

	//vector zawierajacy odpowiednia liczbe typow plytek
	//Bedzie to obiekt potrzebny w algorytmie mieszajacym
	std::vector<TILE_TYPE>gameTiles;			///< wektor przechowujący płytki
	std::vector<position>activeTilesPos;		///< wektor indeksów aktywnych płytek
	std::vector<position>accessibleTilesPos;	///< wektor indeksów płytek, z którymi można wejść w interakcję
	std::vector<TILE_TYPE>accessibleTilesTypes;	///< wektor rodzajów płytek, z którymi można wejść w interakcję

	std::pair<position, position>helpTiles;	///< para płytek pokazywana przez opcję help

	std::random_device randomDevice;	///< do tworzenia ziarna

public:

	std::vector<std::vector<std::vector<Tile*>>>board{ v2d };	///< trójwymiarowy wektor przechowujący wskaźniki do płytek.

	/** Destruktor zwalniający pamięć  */
	~Board();

	/**
	 * Inicjalizuje planszę wypełniając jej zawartość.
	 * 
	 * \param[in] _screenW szerokość ekranu
	 * \param[in] _screenH wysokość ekranu
	 */
	void init(size_t _screenW, size_t _screenH);

	/**
	 * Resetuje zawartość obiektu.
	 * 
	 * \param[in] _screenW szerokość ekranu
	 * \param[in] _screenH wysokość ekranu
	 */
	void reset(size_t _screenW, size_t _screenH) noexcept;

	/**
	 * Miesza zawartość planszy.
	 * 
	 * Używa rozkładu jednostajnego oraz generatora Mersenne twister w celu uzykania jak najwiarygodniejszych liczb psudolosowych
	 */
	void shuffle() noexcept;

	/**
	 * Skaluje rozmiar płytek oraz dobiera odpowiednie współrzedne na ekranie.
	 * 
	 * \param[in] _screenW szerokość ekranu
	 * \param[in] _screenH wysokość ekranu
	 */
	void scaleTiles(size_t _screenW, size_t _screenH) noexcept;

	/** Inicjalizuje płytki, które będą dostępne w grze */
	void initGameTiles() noexcept;

	/** Aktualizuje płytki, które będą widoczne dla gracza */
	void updateActiveTiles() noexcept;

	/** Aktualizuje płytki, z którymi można wejść w interakcję */
	void updateAccessibleTiles() noexcept;

	/** Zaznacza dwie płytki, które są parą  */
	void markPair() noexcept;

	/** Odznacza dwie płytki, które zostały wcześniej wskazane przez metodę markPair() */
	void unmarkPair() noexcept;

	/**
	 * Wczytuje informację o rozmiarze i kształcie planszy.
	 * 
	 * \return true jeżeli procedura przebiegła poprawnie, w przeciwnym wypadku false
	 */
	bool loadMap();

	/**
	 * Sprawdza poprawność odczytanego z pamięci kształtu
	 * 
	 * \return true jeżeli plansza jest zapisana w dobrym formacie, w przeciwnym wypadku false
	 */
	bool chceckTheCorrectness() noexcept;

	/**
	 * Wyszukuje parę, którą można ściągnąć z planszy.
	 * 
	 * \return true jeżeli znaleziono parę, w przeciwnym wypadku false
	 */
	bool lookForPair() noexcept;

	/**
	 * Umożliwa zaznaczenie płytek przez gracza.
	 * 
	 * \param[in] _cursor współrzędnę myszki
	 * \return stan wyboru wskazanej płytki
	 */
	bool selectTile(SDL_Point _cursor) noexcept;

	/**
	 * Porównuje ze sobą parę płytek.
	 * 
	 * \return true jeżeli są tego samego typu, w przeciwnym wypadku zwraca false
	 */
	bool areSameTiles() noexcept;

	/**
	 * Sprawdza czy nie doszło do sytuacji w której 2 ostatnie płytki są sąsiadami względem osi Z.
	 * 
	 * \return true jeżeli 2 ostanie płytki mają te same współrzędne dla indeklsów X i Y, w przeciwnym wypadku false
	 */
	bool checkBlockedTiles() noexcept;

	/** Zwraca maksymalną liczbę płytek w osi Y */
	size_t getMaxY() noexcept;

	/** Zwraca maksymalną liczbę płytek w osi X */
	size_t getMaxX() noexcept;

	/** Zwraca maksymalną liczbę płytek w osi Z */
	size_t getMaxZ() noexcept;

	/** Zwraca ilość wszystkich płytek na planszy */
	size_t getTotalNumberOfTiles() noexcept;

	/** Zwraca parę indeksów płytek, które można ściągnąć */
	std::pair<position, position> getHelpTiles() noexcept;
};