/*****************************************************************//**
 * \file   $FILENAME
 *
 * \author Michal Jackowski
 * \date   Thursday March 21 18:52:13 2021
 *********************************************************************/

#pragma once

/**
 * Wartości wyliczeniowe dla zdarzenia.
 */
enum GAME_EVENT
{
	SOUND_TILE_REMOVED = 0,			///< płytka została usunięta
	TIME_LESS_THAN_10_MIN,			///< gracz osiągnął czas poniżej 10 minut
	TIME_LESS_THAN_5_MIN,			///< gracz osiągnął czas poniżej 5 minut
	TIME_LESS_THAN_4_MIN,			///< gracz osiągnął czas poniżej 4 minut
	TIME_LESS_THAN_3_MIN,			///< gracz osiągnął czas poniżej 3 minut
	TIME_LESS_THAN_2_MIN,			///< gracz osiągnął czas poniżej 2 minut
	TIME_GAME_MORE_THAN_2_HOURS,	///< gracz spędził w grze ponad 2 godziny
	TIME_GAME_MORE_THAN_4_HOURS,	///< gracz spędził w grze ponad 4 godziny
	TIME_GAME_MORE_THAN_8_HOURS,	///< gracz spędził w grze ponad 8 godzin
	TIME_GAME_MORE_THAN_16_HOURS,	///< gracz spędził w grze ponad 16 godzin
	TIME_GAME_MORE_THAN_32_HOURS,	///< gracz spędził w grze ponad 32 godziny
	TIME_GAME_MORE_THAN_64_HOURS,	///< gracz spędził w grze ponad 64 godziny
	TIME_GAME_MORE_THAN_128_HOURS,	///< gracz spędził w grze ponad 128 godzin
	TIME_GAME_MORE_THAN_256_HOURS,	///< gracz spędził w grze ponad 256 godzin
	TIME_GAME_MORE_THAN_512_HOURS,	///< gracz spędził w grze ponad 512 godzin
	TIME_GAME_MORE_THAN_1024_HOURS,	///< gracz spędził w grze ponad 1024 godziny
	NONE							///< nie zaszło żadne ciekawe zdarzenie
};

/**
 * Wyliczenie ułatwiające indeksowanie osiągnięć.
 */
enum ACHIEVEMENT
{
	ACHIEVEMENT_TIME_LESS_THAN_10_MIN = 0,		///< gracz osiągnął czas poniżej 10 minut
	ACHIEVEMENT_TIME_LESS_THAN_5_MIN,			///< gracz osiągnął czas poniżej 5 minut
	ACHIEVEMENT_TIME_LESS_THAN_4_MIN,			///< gracz osiągnął czas poniżej 4 minut
	ACHIEVEMENT_TIME_LESS_THAN_3_MIN,			///< gracz osiągnął czas poniżej 3 minut
	ACHIEVEMENT_TIME_LESS_THAN_2_MIN,			///< gracz osiągnął czas poniżej 2 minut
	ACHIEVEMENT_TIME_GAME_MORE_THAN_2_HOURS,	///< gracz spędził w grze ponad 2 godziny
	ACHIEVEMENT_TIME_GAME_MORE_THAN_4_HOURS,	///< gracz spędził w grze ponad 4 godziny
	ACHIEVEMENT_TIME_GAME_MORE_THAN_8_HOURS,	///< gracz spędził w grze ponad 8 godzin
	ACHIEVEMENT_TIME_GAME_MORE_THAN_16_HOURS,	///< gracz spędził w grze ponad 16 godzin
	ACHIEVEMENT_TIME_GAME_MORE_THAN_32_HOURS,	///< gracz spędził w grze ponad 32 godziny
	ACHIEVEMENT_TIME_GAME_MORE_THAN_64_HOURS,	///< gracz spędził w grze ponad 64 godziny
	ACHIEVEMENT_TIME_GAME_MORE_THAN_128_HOURS,	///< gracz spędził w grze ponad 128 godzin
	ACHIEVEMENT_TIME_GAME_MORE_THAN_256_HOURS,	///< gracz spędził w grze ponad 256 godzin
	ACHIEVEMENT_TIME_GAME_MORE_THAN_512_HOURS,	///< gracz spędził w grze ponad 512 godzin
	ACHIEVEMENT_TIME_GAME_MORE_THAN_1024_HOURS,	///< gracz spędził w grze ponad 1024 godziny
	ACHIEVEMENT_TOTAL_COUNT						///< ogólna liczba osiągnięć dostępnych w grze
};

/**
 * Wyliczenie reprezentujące typ bloczku (ułatwia one indeksowanie tekstur).
 */
enum TILE_TYPE
{
	SIGN_RED_ONE = 0,
	SIGN_RED_TWO,
	SIGN_RED_THREE,
	SIGN_RED_FOUR,
	SIGN_RED_FIVE,
	SIGN_GREEN,
	SIGN_GOLD_ONE,
	SIGN_GOLD_TWO,
	SIGN_GOLD_THREE,
	SIGN_GOLD_FOUR,
	SIGN_BLACK_ONE,
	SIGN_BLACK_TWO,
	SIGN_BLACK_THREE,
	SIGN_BLACK_FOUR,
	SIGN_RECTANGLE,
	SIGNS_ONE,
	SIGNS_TWO,
	SIGNS_THREE,
	SIGNS_FOUR,
	SIGNS_FIVE,
	SIGNS_SIX,
	SIGNS_SEVEN,
	SIGNS_EIGHT,
	SIGNS_NINE,
	DOTS_ONE,
	DOTS_TWO,
	DOTS_THREE,
	DOTS_FOUR,
	DOTS_FIVE,
	DOTS_SIX,
	DOTS_SEVEN,
	DOTS_EIGHT,
	DOTS_NINE,
	BAMBOO_ONE,
	BAMBOO_TWO,
	BAMBOO_THREE,
	BAMBOO_FOUR,
	BAMBOO_FIVE,
	BAMBOO_SIX,
	BAMBOO_SEVEN,
	BAMBOO_EIGHT,
	BAMBOO_NINE,
	DEFAULT,
	SELECTED,
	HELP,
	EMPTY
};

/**
 * Wyliczenie reprezentujące rodzaj dzwięku (ułatwia one indeksowanie dźwięków).
 */
enum SOUND
{
	SOUND_BUTTON_PRESS = 0
};

/**
 * Wyliczenie reprezentujące typ przycisku.
 */
enum BUTTON_TYPE
{
	BUTTON_RESTART = 0,
	BUTTON_HELP,
	BUTTON_SHUFFLE,
	BUTTON_TIME,
	BUTTON_ACHIEVEMENT,
	BUTTON_PLAY_AGAIN
};

/** Konwersja TILE_TYPE do std::string. */
std::string TILE_TYPEtoString(TILE_TYPE _tileType);

/** Konwersja SOUND do std::string */
std::string SOUNDtoString(SOUND _sound);

/** Konwersja ACHIEVEMENTS do std::string */
std::string ACHIEVEMENTStoString(ACHIEVEMENT _achievement);

/** Konwersja int do GAME_EVENT (dla zdarzen związanych z najlepszym czasem) */
GAME_EVENT convertBestTime(int _time);

/** Konwersja int do GAME_EVENT (dla zdarzen związanych z ogólnym czasem)*/
GAME_EVENT convertOverallTime(int _time);

/** Konwersja GAME_EVENT do ACHIEVEMENT */
ACHIEVEMENT GAME_EVENTtoACHIEVEMENT(GAME_EVENT _event);