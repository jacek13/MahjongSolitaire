/*****************************************************************//**
 * \file   $FILENAME
 *
 * \author Michal Jackowski
 * \date   Thursday March 21 18:52:13 2021
 *********************************************************************/

#pragma once

#include"SDL.h"
#include"SDL_image.h"
#include"SDL_ttf.h"
#include"SDL_mixer.h"

#include"Enum.h"

/**
 * Struktura dla formatu rgba.
 */
struct rgbaColour
{
    size_t  R,  ///< kanał R-red
            G,  ///< kanał G-green
            B,  ///< kanał B-blue
            A;  ///< kanał A-alpha (przezroczystość)
};

/**
 * Struktura przechowująca ustawienia wejściowe.
 */
struct settings
{
	bool    fullScreen,         ///< wyświetlanie programu w pełnym ekranie
            vSync;              ///< synchronizacja pionowa
	size_t  screenW,            ///< szerokość ekranu
            screenH;            ///< wysokość ekranu
    rgbaColour  fontColour,     ///< kolor czcionki
                rendererColour; ///< podstawwowy kolor renderera (u nas określa kolor tła)
};

/**
 * Struktura przechowująca informacje o pozycji w obiekcie trójwymiarowym.
 */
struct position
{
    size_t  x,  ///< indeks i/x
            y,  ///< indeks j/y
            z;  ///< indeks k/z
};

struct tileTexture
{
    SDL_Texture* texture = nullptr;
    TILE_TYPE tileType;
};