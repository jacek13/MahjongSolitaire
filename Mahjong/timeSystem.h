/*****************************************************************//**
 * \file   $FILENAME
 *
 * \author Michal Jackowski
 * \date   Thursday March 21 18:52:13 2021
 *********************************************************************/

#pragma once

#include<iostream>
#include<string>
#include<vector>
#include<chrono>

#include"Subject.h"
#include"fileSystem.h"

/**
 * Klasa timeSystem odpowiada za zarządzanie czasem.
 */
class timeSystem : public Subject, public fileSystem_Time
{
private:
	std::chrono::steady_clock::time_point startLoopTime;
	std::chrono::steady_clock::time_point endLoopTime;
	std::chrono::duration<double>elapsedSeconds;
	std::chrono::duration<double>sumOfElapsedSeconds;
public:
	/**
	 * Konstruktor domyślny.
	 * 
	 * Wpisuje on wartości początkowe dla atrybutów.
	 */
	timeSystem() :
		Subject(),
		fileSystem_Time(),
		startLoopTime(std::chrono::steady_clock::now()),
		endLoopTime(std::chrono::steady_clock::now()),
		elapsedSeconds(std::chrono::duration_cast<std::chrono::duration<double>>(endLoopTime - startLoopTime)),
		sumOfElapsedSeconds(elapsedSeconds) {}

	/**
	 * Destruktor.
	 * 
	 * Wywołuje metodę save() z obiektu fileSystem_Time.
	 */
	~timeSystem();

	/** Metoda inicjalizująca obiekt */
	void init();

	/** Startuje licznik */
	void start() noexcept;

	/** Aktualizuje stan licznika */
	void update() noexcept;

	/** Resetuje stan licznika */
	void reset() noexcept;

	/**
	 * Dodaje karę czasową do licznika.
	 * 
	 * \param _penalty[in] wartość kary czasowej
	 */
	void addTimePenalty(std::chrono::seconds _penalty) noexcept;

	/** Sprawdza czy zaistniała potrzeba zmiany najlepszego czasu na nowy */
	void checkForUpdate();

	/** Zwraca czas, który upłynął od początku danej razgorywki */
	double getTime();

	/** Zwraca czas trwania jednej pętli gry */
	double getLoopTime();

	/** Zwraca najlepszy czas użytkownika */
	double getPersonalBest();

	/** Zwraca całkowity czas, który gracz spędził w grze */
	double getOverallTime();

	/** Sprawdza czy aktualny czas licznika jest lepszy od dotychczasowego najlepszego czasu */
	bool isNewPersonalBest();

	/**
	 * Zapisuje informacje o aktualnej rozgrywce do pliku CSV.
	 * 
	 * Metoda wysyła również informacje do obserwatorów o zaistniałym zdarzeniu, dzięki czemu można stwierdzić czy mamy nowy rekord itp.
	 * \return true jeżeli procedura zapisu przeszła pomyślnie, w przeciwnym wypadku false
	 */
	bool saveGameInfo();

	/**
	 * Przetwarza informację o czasie.
	 * 
	 * \param[in] _min_sec_format dla wartości true dane wyjściowe zostaną przetworzone do formatu min:sec 
	 * \return czas licznika w postaci tekstu
	 * \warning Nie jest bezpieczna dla wielowątkowośći!
	 */
	std::string getTimeAsString(bool _min_sec_format = true);

	/**
	 * Przetwarza informacje o aktualnej dacie.
	 * 
	 * \param[in] _separator możemy podać znak wstawiany pomiędzy wartości daty
	 * \return sformatowana informacja o aktualnej dacie t.j dz:mies:rok
	 * \warning Nie jest bezpieczna dla wielowątkowośći!
	 */
	std::string getDate(char _separator = '.');

	/**
	 * Przetwarza informacje o czasie lokalnym.
	 * 
	 * \param[in] _separator możemy podać znak, który zostanie użyty w formatowaniu
	 * \return sformatowana informacja o czasie lokalnym t.j godz:min:sek
	 * \warning Nie jest bezpieczna dla wielowątkowośći!
	 */
	std::string getDaytime(char _separator = ':');

	/**
	 * Przetwarza informacjie o dacie.
	 * 
	 * \param[in] _separator możemy podać znak wstawiany pomiędzy wartości daty
	 * \return sformatowana informacja o aktualnej dacie t.j mies:rok
	 * \warning Nie jest bezpieczna dla wielowątkowośći!
	 */
	std::string getMonthYear(char _separator = '-');

	/**
	 * Konwertuje ilosc sekund w format min:sec.
	 * 
	 * \param[in] _sec ilość sekund do zamiany
	 * \return zwraca parę gdzie .first to minuty a .second to sekundy
	 */
	std::pair<int, int> secToMinSecFormat(int _sec) noexcept;
};