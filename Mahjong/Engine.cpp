//Biblioteki Standardowe
#include<iostream>

//Biblioteki zewnętrzne
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<SDL_mixer.h>

#include"Engine.h"
#include"structures.h"
#include"myException.h"

bool Engine::init() noexcept
{
    //deklaracja flagi powodzenia
    bool success = true;

    //Inicjalizuje SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        std::cerr << "Window ERROR! SDL_Error: " << SDL_GetError() << std::endl;
        success = false;
    }
    else
    {
        //Utworzenie okna
        window = SDL_CreateWindow(VERSION, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, config.screenW, config.screenH, SDL_WINDOW_SHOWN);
        if (window == nullptr)
        {
            std::cerr << "The window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
            success = false;
        }
        else
        {
            //Tworzy Renderer dla okna
            if (config.vSync)
                renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            else
                renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

            if (config.fullScreen)
                SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

            if (renderer == nullptr)
            {
                std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
                success = false;
            }
            else
            {
                //Inicjalizuje kolor renderera
                SDL_SetRenderDrawColor(renderer, config.rendererColour.R, config.rendererColour.G, config.rendererColour.B, config.rendererColour.A);

                //Inicjalizacja dodatkowej biblioteki obslugujacej obrazy png
                if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
                {
                    std::cerr << "SDL_image could not be initialized! SDL_image Error: " << IMG_GetError() << std::endl;
                    success = false;
                }
            }
        }
    }
    //inicjalizuje biblioteke dodatkowa obslugujaca rozne typy czcionek, TTF
    if (TTF_Init() < 0)
    {
        std::cerr << "Font engine not initialized! TTF_Error: " << TTF_GetError() << std::endl;
        success = false;
    }

    //inicjalizacja biblioteki odpowiadającej za dzwięk
    #ifdef SOUND
    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) < 0)
    {
        std::cerr << "The sound engine has not been initialized! SDL_mixer Error: " << Mix_GetError() << std::endl;
        success = false;
    }
    #endif

    return success;
}

Engine::~Engine()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_CloseFont(font);
    SDL_FreeSurface(icon);

    renderer = nullptr;
    window = nullptr;
    font = nullptr;
    icon = nullptr;

    for (size_t i = 0; i < textures.size(); i++)
    {
        SDL_DestroyTexture(textures.at(i));
        textures.at(i) = nullptr;
    }

    #ifdef SOUND
    for (size_t i = 0; i < sounds.size(); i++)
    {
        Mix_FreeChunk(sounds.at(i));
        sounds.at(i) = nullptr;
    }
    #endif

    SDL_Quit();
    IMG_Quit();
    TTF_Quit();
    #ifdef SOUND
    Mix_Quit();
    #endif
}

SDL_Surface* Engine::loadSurface(const char* _path)
{
    SDL_Surface* optimized = nullptr;
    SDL_Surface* surface = IMG_Load(_path);

    SDL_PixelFormat* format = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA32);

    if (surface == nullptr)
    {
        std::string error("Failed to load an image from a path!\n");
        error += _path;
        error += "\nSDL Error: ";
        error += IMG_GetError();
        throw myException_Engine(error.c_str());
    }
    else
    {
        optimized = SDL_ConvertSurface(surface, format, 0);

        if (optimized == nullptr)
        {
            std::string error("Optimization has failed!\n");
            error += _path;
            error += "\nSDL Error: ";
            error += IMG_GetError();
            throw myException_Engine(error.c_str());
        }
        //zwalnianie pamieci
        SDL_FreeSurface(surface);
        SDL_FreeFormat(format);
    }
    return optimized;
}

SDL_Texture* Engine::loadTexture(const char* _path)
{
    SDL_Texture* texture = nullptr;
    SDL_Surface* surface = IMG_Load(_path);

    if (surface == nullptr)
    {
        std::string error("Failed to load an image from a path!\n");
        error += _path;
        error += "\nSDL Error: ";
        error += IMG_GetError();
        throw myException_Engine(error.c_str());
    }
    else
    {
        texture = SDL_CreateTextureFromSurface(renderer, surface);

        if (texture == nullptr)
        {
            std::string error("Could not create texture from path!\n");
            error += _path;
            error += "\nSDL Error: ";
            error += SDL_GetError();
            throw myException_Engine(error.c_str());
        }
        //zwalnianie pamieci
        SDL_FreeSurface(surface);
    }
    return texture;
}

bool Engine::loadResources()
{
    bool success = true;
    try
    {
        if (success = fileSystem_Engine::load())
        {
            textures.resize(getNumberOfTexturePaths());
            sounds.resize(getNumberOfSoundPaths());

            font = TTF_OpenFont(getFontPath().c_str(), 72); // druga wartość to rozmiar czcionki, kiedyś trzeba dodać do configu TODO
            if (font == nullptr)
            {
                success = false;
                std::string error("Could not open font from path!\n");
                error += getFontPath().c_str();
                error += "\nSDL Error: ";
                error += TTF_GetError();
                throw myException_Engine(error.c_str());
            }
           
            icon = loadSurface(getIconPath().c_str());
            if (icon == nullptr)
                success = false;
            else
                SDL_SetWindowIcon(window, icon);

            //Poniżej znajdują się instrukcję ładowania tekstur
            for (size_t i = 0; i < getNumberOfTexturePaths(); i++)
            {
                textures.at(i) = loadTexture(getTexturesPath(i).c_str());
                if (textures.at(i) == nullptr)
                    success = false;
            }
            #ifdef SOUND
            for (size_t i = 0; i < getNumberOfSoundPaths(); i++)
            {
                sounds.at(i) = Mix_LoadWAV(getSoundPath(i).c_str());
                if (sounds.at(i) == nullptr)
                    success = false;
            }
            #endif
        }
    }
    catch (myException& error)
    {
        std::cerr << error.what() << std::endl;
    }
    return success;
}

void Engine::drawTile(SDL_Rect * _cord, TILE_TYPE _tileType, bool _isSelected, bool _helpEnable) noexcept
{
    //Dla easy mode będzie zmieniony odcień tekstury TODO
    if (_tileType != EMPTY)
    {
        if (_isSelected)
        {
            SDL_RenderSetViewport(renderer, _cord);
            SDL_RenderCopy(renderer, textures.at(_tileType), nullptr, nullptr);
            SDL_RenderCopy(renderer, textures.at(SELECTED), nullptr, nullptr);
        }
        else if (_helpEnable)
        {
            SDL_RenderSetViewport(renderer, _cord);
            SDL_RenderCopy(renderer, textures.at(_tileType), nullptr, nullptr);
            SDL_RenderCopy(renderer, textures.at(HELP), nullptr, nullptr);
        }
        else
        {
            SDL_RenderSetViewport(renderer, _cord);
            SDL_RenderCopy(renderer, textures.at(_tileType), nullptr, nullptr);
        }
    }
}

void Engine::drawText(SDL_Rect* _cord, const char* _text) noexcept
{
    // Przydałoby się zrobić dodatową funkcję dostosowującą rozmiar SDL_Rect do napisu TODO
    // Plus kiedyś dorobić vector tekstur z napisami i dopiero na koniec programu zwalniac je w destruktorze TODO
    SDL_Surface* text = nullptr;
    SDL_Texture* textTexture = nullptr;
    
    text = TTF_RenderText_Solid(font, _text, {  static_cast<Uint8>(config.fontColour.R),
                                                static_cast<Uint8>(config.fontColour.G),
                                                static_cast<Uint8>(config.fontColour.B),
                                                static_cast<Uint8>(config.fontColour.A) });
    textTexture = SDL_CreateTextureFromSurface(renderer,text);

    SDL_RenderSetViewport(renderer, _cord);
    SDL_RenderCopy(renderer, textTexture, nullptr, nullptr);

    SDL_FreeSurface(text);
    SDL_DestroyTexture(textTexture);
}

void Engine::drawCurrentState() noexcept
{
    SDL_RenderPresent(renderer);
}

void Engine::clearCurrentState() noexcept
{
    SDL_RenderClear(renderer);
}