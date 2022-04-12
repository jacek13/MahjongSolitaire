#define DEBUG_MEMORY_LEAKS
#ifdef DEBUG_MEMORY_LEAKS && _MSC_BUILD
	#define _CRTDBG_MAP_ALLOC
	#include<stdlib.h>
	#include<crtdbg.h>
#endif

//Biblioteki Standardowe
#include<iostream>
#include<chrono>

//Biblioteki zewnętrzne
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<SDL_mixer.h>

#include"Game.h"
#include"structures.h"
#include"myException.h"

int main(int argc, char* args[])
{
	try
	{
		Game app;
		app.init();
		app.loop();
	}
	catch (myException& e)
	{
		std::cerr << e.what() << std::endl;
	}

	#ifdef DEBUG_MEMORY_LEAKS && _MSC_BUILD
	_CrtDumpMemoryLeaks();
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
	#endif

	return 0;
}