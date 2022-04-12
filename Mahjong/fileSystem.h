/*****************************************************************//**
 * \file   $FILENAME
 *
 * \author Michal Jackowski
 * \date   Thursday March 21 18:52:13 2021
 *********************************************************************/

#pragma once

#include<fstream>
#include<string>
#include<vector>

#include"structures.h"

#define VERSION "Mahjong 0.17"

/**
 * Interfejs dla obiektów fileStstem.
 */
class fileSystem
{
public:
	virtual bool load() = 0;
	virtual bool save(bool _overwrite = true) = 0;
};

/**
 * Odpowiada za znalezienie odpowiednich ścieżek do plików dla silnika gry.
 */
class fileSystem_Engine : public fileSystem
{
private:
	std::vector<std::string>texturesPaths;	///< ścieżki do tekstur
	std::vector<std::string>soundPaths;		///< ścieżki do dźwięków
	std::string fontPaths;					///< ścieżka do czcionki
	std::string iconPaths;					///< ścieżka do ikony
	settings config;						///< informacje o konfiguracji programu

public:
	/** Wczytuje ścieżki dla obiektu Engine */
	virtual bool load();

	/**
	 * \todo metoda ta nie ma aktualnie zastosowania w moim projekcie.
	 * Można kiedyś dorobić plik z rejestrowaniem zdarzeń silnika.
	 */
	virtual bool save(bool _overwrite) { return true; }

	//getters

	/**
	 * Umożliwia dostęp do i-tej ścieżki.
	 * 
	 * \param _i wskazuje indeks ścieżki
	 * \return i-ta ścieżka do tekstury
	 */
	std::string getTexturesPath(size_t _i);

	/**
	 * Umożliwia dostęp do i-tej ścieżki.
	 * 
	 * \param _i wskazuje indeks ścieżki
	 * \return i-ta ścieżka do dzwięku
	 */
	std::string getSoundPath(size_t _i);

	/**
	 * Umożliwia dostęp do ścieżki.
	 * 
	 * \return ścieżkę do pliku czcionki
	 */
	std::string getFontPath();

	/**
	 * Umożliwia dostęp do ścieżki.
	 * 
	 * \return ściężkę do pliku z ikoną programu
	 */
	std::string getIconPath();
	
	/**
	 * Umożliwia sprawdzenie ilości ścieżek do tekstur.
	 * 
	 * \return ilość ścieżek do tekstur
	 */
	size_t getNumberOfTexturePaths();

	/**
	 * Umożliwia sprawdzenie ilości ścieżek do dźwięków.
	 * 
	 * \return ilość ścieżek do dźwięków
	 */
	size_t getNumberOfSoundPaths();
};

/**
 * Odpowiada za odczytanie informacji o czasie.
 */
class fileSystem_Time : public fileSystem
{
private:
	double totalGameTime = 0.0;	///< ogólny czas spędzony przez użytkownika w grze
	double bestTime = 0.0;		///< najlepszy czas gracza

public:
	/** Wczytuje informacjie potrzebne dla obiektu timeSystem */
	virtual bool load();

	/** Zapisuje ogólne informacje o czasie */
	virtual bool save(bool _overwrite);

	/**
	 * Zapisuje/dopisuje informacje o zakończonej rozgrywce do pliku o rozszerzeniu CSV.
	 * 
	 * \param[in] _date aktualna data
	 * \param[in] _daytime aktualny czas 
	 * \param[in] _monthYear aktualny miesiąc i rok
	 * \param[in] _gameTime czas rozgrywki do zapisu
	 * \param[in] _separator separator dla pliku CSV
	 * \return true jeżeli procedura zapisu się powiodła, w przeciwnym wypadku falase
	 */
	bool saveCSV(const char * _date, const char* _daytime, const char * _monthYear, int _gameTime, char _separator = ',');

	/**
	 * Umożliwia dostęp do ogólnego czasu spędzonego w grze przez użytkownika.
	 * 
	 * \return ogólny czas spędzony w grze (podany w sekundach)
	 */
	double getTotalGameTime() noexcept;

	/**
	 * Umożliwia dostęp do najlepszego czasu gracza.
	 * 
	 * \return najlepszy czas (podany w sekundach)
	 */
	double getBestTime() noexcept;

	/**
	 * Umożliwia ustawienie/aktualizacje ogólnego czasu spędzonego w programie.
	 * 
	 * \param[in] _newTotalGameTime zaktualizowany czas (podany w sekundach)
	 */
	void setTotalGameTime(double _newTotalGameTime) noexcept;

	/**
	 * Umożliwia ustawienie/aktualizacje nowego najlepszego czasu gracza.
	 * 
	 * \param _newBestTime[in] nowy rekord (podany w sekundach)
	 */
	void setBestTime(double _newBestTime) noexcept;
};

/**
 * Odpowiada za wczytywanie informacji o zdobytych osiągnięciach.
 */
class fileSystem_Achievements : public fileSystem
{
protected:
	std::vector<bool>achievements; ///< wektor przechowuje status o osiągnięciach

public:
	/** Wczytuje osiągnięcia z pliku */
	virtual bool load();

	/** Zapisuje aktualny status osiągnięć do pliku */
	virtual bool save(bool _overwrite);
};

/**
 * Odpowiada za wczytanie ścieżki do pliku zawierającego wzór planszy.
 */
class fileSystem_Board : public fileSystem
{
private:
	std::string patternPath; ///< ścieżka do pliku zawierającego wzór planszy

public:
	/** Wczytuje ściężkę do pliku  */
	virtual bool load();

	/** \todo save nie znalazło zastosowania w projekcie */
	virtual bool save(bool _overwrite) { return true; };

	/**
	 * Umożliwia dostęp do ścieżki.
	 * 
	 * \return ściężke do pliku zawierającego wzór planszy
	 */
	std::string getPatternPath();
};

/**
 * Odpowiada za wczytanie pliku konfiguracyjnego.
 */
class fileSystem_Game : public fileSystem
{
private:
	settings config; ///< struktura zawierająca informacje o konfiguracji

public:
	/** Wczytaj config */
	virtual bool load();

	/** \todo save nie znalazło zastosowania w tej fazie projektu. W przyszłości po dodaniu Menu motoda ta będzie używana */
	virtual bool save(bool _overwrite) { return true; };

	/** Tworzy plik tekstowy zawierający podstawowe informacje o aplikacji */
	bool makeReadMe(const char * _path);

	/** Zwraca informacje o pliku konfiguracyjnym */
	settings getSettings() noexcept;

	/** Zwraca szerokość ekranu */
	size_t getScreenW() noexcept;

	/** Zwraca wysokość ekranu */
	size_t getScreenH() noexcept;
};