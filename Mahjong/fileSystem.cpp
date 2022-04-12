#include<iostream>
#include<fstream>
#include<iterator>
#include<algorithm>
#include<vector>
#include<string>
#include<utility>

#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<SDL_mixer.h>

#include"fileSystem.h"
#include"myException.h"
#include"Enum.h"

//Funkcja wczytuje sciezki do niezbednych elementow modulu Engine
bool fileSystem_Engine::load()
{
	std::string texturePath("E:/Projekty/PK4/f310ed3c-gr52-repo/Projekt/Mahjong/Mahjong/data/textures_paths.txt"),
				soundPath("E:/Projekty/PK4/f310ed3c-gr52-repo/Projekt/Mahjong/Mahjong/data/sound_paths.txt"),
				fontPath("E:/Projekty/PK4/f310ed3c-gr52-repo/Projekt/Mahjong/Mahjong/data/font_path.txt"),
				iconPath("E:/Projekty/PK4/f310ed3c-gr52-repo/Projekt/Mahjong/Mahjong/data/icon_path.txt");

	bool success = true;

	//Otwieranie pliku zawierajacego sciezki do tekstur

	std::vector<std::string>tmp;
	std::fstream file(texturePath.c_str());
	std::istream_iterator<std::string>fileIterator(file);
	tmp.assign(fileIterator, std::istream_iterator<std::string>());

	if (tmp.empty())
	{
		success = false;
		std::string error("Cannot open file from path: " + texturePath);
		throw myException_fileSystem(error.c_str());
	}
	else
	{
		//zmieniam rozmiar atrybutu texturesPaths na ilosc tekstur dostepnych dla płytek
		texturesPaths.resize(HELP + 1);

		//przeszukuje wczytany plik w celu znalezienia wzorców 
		for (size_t i = 0; i < EMPTY; i++)
		{
			auto match = std::find(std::begin(tmp), std::end(tmp), TILE_TYPEtoString((TILE_TYPE)i).c_str());
			if (match != std::end(tmp))
			{
				auto index = std::distance(std::begin(tmp), match);
				texturesPaths.at(i) = tmp.at(index + 1);
			}
		}
	}
	file.close();

	//Otwieranie pliku zawierajacego sciezki do dzwiekow
	file.open(soundPath.c_str());
	fileIterator = file;
	tmp.assign(fileIterator, std::istream_iterator<std::string>());

	if (tmp.empty())
	{
		success = false;
		std::string error("Cannot open file from path: " + soundPath);
		throw myException_fileSystem(error.c_str());
	}
	else
	{
		soundPaths.resize(SOUND_BUTTON_PRESS + 1);

		//przeszukuje wczytany plik w celu znalezienia wzorców 
		for (size_t i = 0; i < SOUND_BUTTON_PRESS + 1; i++)
		{
			auto match = std::find(std::begin(tmp), std::end(tmp), SOUNDtoString((SOUND)i).c_str());
			if (match != std::end(tmp))
			{
				auto index = std::distance(std::begin(tmp), match);
				soundPaths.at(i) = tmp.at(index + 1);
			}
		}
	}
	file.close();

	//Otwieranie pliku zawierajacego sciezke do czcionki
	file.open(fontPath.c_str());
	fileIterator = file;
	tmp.assign(fileIterator, std::istream_iterator<std::string>());

	if (tmp.empty())
	{
		success = false;
		std::string error("Cannot open file from path: " + fontPath);
		throw myException_fileSystem(error.c_str());
	}
	else
	{
		//przeszukuje wczytany plik w celu znalezienia wzorców 
		auto match = std::find(std::begin(tmp), std::end(tmp), "FONT");
		if (match != std::end(tmp))
		{
			auto index = std::distance(std::begin(tmp), match);
			fontPaths = tmp.at(index + 1);
		}
	}
	file.close();

	//Otwieranie pliku zawierajacego sciezke do ikony
	file.open(iconPath.c_str());
	fileIterator = file;
	tmp.assign(fileIterator, std::istream_iterator<std::string>());

	if (tmp.empty())
	{
		success = false;
		std::string error("Cannot open file from path: " + iconPath);
		throw myException_fileSystem(error.c_str());
	}
	else
	{
		//przeszukuje wczytany plik w celu znalezienia wzorców 
		auto match = std::find(std::begin(tmp), std::end(tmp), "ICON");
		if (match != std::end(tmp))
		{
			auto index = std::distance(std::begin(tmp), match);
			iconPaths = tmp.at(index + 1);
		}
	}
	file.close();

	return success;
}


std::string fileSystem_Engine::getTexturesPath(size_t _i)
{
	return texturesPaths.at(_i); //metoda at() zgłasza już wyjątek w razie wskazania złego indeksu
}

std::string fileSystem_Engine::getSoundPath(size_t _i)
{
	return soundPaths.at(_i);
}

std::string fileSystem_Engine::getFontPath()
{
	return fontPaths;
}

std::string fileSystem_Engine::getIconPath()
{
	return iconPaths;
}

size_t fileSystem_Engine::getNumberOfTexturePaths()
{
	return texturesPaths.size();
}

size_t fileSystem_Engine::getNumberOfSoundPaths()
{
	return soundPaths.size();
}

bool fileSystem_Game::load()
{

	std::string configPath("E:/Projekty/PK4/f310ed3c-gr52-repo/Projekt/Mahjong/Mahjong/data/config.txt");
	std::vector<std::string>patterns({ "FULLSCREEN","VSYNC","SCREEN_HEIGHT","SCREEN_WIDTH","FONT_COLOUR","BACKGROUND_COLOUR" });

	bool success = true;

	std::vector<std::string>tmp;
	std::fstream file(configPath.c_str());
	std::istream_iterator<std::string>fileIterator(file);
	tmp.assign(fileIterator, std::istream_iterator<std::string>());

	if (tmp.empty())
	{
		success = false;
		std::string error("Cannot open file from path: " + configPath);
		throw myException_fileSystem(error.c_str());
	}
	else
	{
		//przeszukuje wczytany plik w celu znalezienia wzorców 
		//Kiedyś można dodać więcej zabezpieczeń sprawdzających czy dana wartość jest cyfrą itp
		for (size_t i = 0; i < patterns.size(); i++)
		{
			auto match = std::find(std::begin(tmp), std::end(tmp), patterns.at(i).c_str());
			if (match != std::end(tmp) && patterns.at(i) == "FULLSCREEN")
			{
				auto index = std::distance(std::begin(tmp), match);
				config.fullScreen = static_cast<bool>(std::stoi(tmp.at(index + 1)));
			}
			if (match != std::end(tmp) && patterns.at(i) == "VSYNC")
			{
				auto index = std::distance(std::begin(tmp), match);
				config.vSync = static_cast<bool>(std::stoi(tmp.at(index + 1)));
			}
			if (match != std::end(tmp) && patterns.at(i) == "SCREEN_HEIGHT")
			{
				auto index = std::distance(std::begin(tmp), match);
				config.screenH = std::stoi(tmp.at(index + 1));
			}
			if (match != std::end(tmp) && patterns.at(i) == "SCREEN_WIDTH")
			{
				auto index = std::distance(std::begin(tmp), match);
				config.screenW = std::stoi(tmp.at(index + 1));
			}
			if (match != std::end(tmp) && patterns.at(i) == "FONT_COLOUR")
			{
				auto index = std::distance(std::begin(tmp), match);
				config.fontColour.R = std::stoi(tmp.at(index + 1));
				config.fontColour.G = std::stoi(tmp.at(index + 2));
				config.fontColour.B = std::stoi(tmp.at(index + 3));
				config.fontColour.A = std::stoi(tmp.at(index + 4));
			}
			if (match != std::end(tmp) && patterns.at(i) == "BACKGROUND_COLOUR")
			{
				auto index = std::distance(std::begin(tmp), match);
				config.rendererColour.R = std::stoi(tmp.at(index + 1));
				config.rendererColour.G = std::stoi(tmp.at(index + 2));
				config.rendererColour.B = std::stoi(tmp.at(index + 3));
				config.rendererColour.A = std::stoi(tmp.at(index + 4));
			}
		}
	}
	file.close();

	return success;
}

bool fileSystem_Game::makeReadMe(const char* _path)
{
	bool success = true;
	bool notExist = false;

	// W celu sprawdzenia istnienia danego pliku tworze strumien wejsciowy dla plikow
	std::ifstream check(_path);

	if (!check)
		notExist = true;
	check.close();

	std::fstream file(_path, std::ios::out | std::ios::app);

	if (file.good())
	{
		if (notExist)
		{
			file << "Plik README" << std::endl;
			file << "Autor: Michal Jackowski" << std::endl;
			file << "Wersja: " << VERSION << " z dnia " << __DATE__ << std::endl;
			file << std::endl;

			file << "1. Mahjong Solitaire" << std::endl;
			file << "Mahjong jednoosobowy to gra polegajaca na znajdowaniu par jednakowych plytek i usuwaniu ich z planszy" << std::endl;
			file << "wedlug scisle okreslonych regul. Plytki mozna usunac tylko wtedy, gdy nie sa one zablokowane, to znaczy, " << std::endl;
			file << "ze plytka nie jest przykryta inna lub nie sasiaduje z lewej i prawej strony z innymi. Rozgrywka konczy" << std::endl;
			file << "się wtedy, gdy usuniemy wszystkie pary z planszy. " << std::endl;
			file << std::endl;

			file << "2. Ustawienia" << std::endl;
			file << "W celu zmiany ustawien w aktualnej wersji programu, nalezy odszukac plik 'config.txt'" << std::endl;
			file << "Za pomoca slow kluczowych i wartosci liczbowych zmieniamy wartosci ustawien." << std::endl;
			file << std::endl;
			file << "PRZYKLAD:" << std::endl;
			file << "FULLSCREEN 1\t\t <- ustawia pelny ekran" << std::endl;
			file << "SCREEN_WIDTH 1600\t <- ustawia szerokosc okna na 1600 pikseli" << std::endl;
			file << "SCREEN_HEIGHT 900\t <- ustawia wysokosc okna na 900 pikseli" << std::endl;
			file << std::endl;
			
			file << "3. Modyfikowanie" << std::endl;
			file << "Program umozliwia modyfikowanie warstwy video poprzez podmiane tekstur i czcionki." << std::endl;
			file << "Mozna to zrobic na 2 sposoby. Pierwszy polega na doslownym podmienieniu poszczegolnych plikow. " << std::endl;
			file << "Zachowujac te same nazwy plikow. Drugim sposobem jest modyfikowanie sciezek w plikach: 'textures_paths.txt' oraz 'font_path.txt.'" << std::endl;
			file << "Za pomoca komend oznaczajacych odpowiednie tekstury mozemy wskazywac cale sciezki do szukanego pliku." << std::endl;
			file << std::endl;
			file << "PRZYKLAD:" << std::endl;
			file << "BAMBOO_THREE E:/Inne_tekstury/bamboo_3.png\t <- ustawienie sciezki dla tekstury BAMBOO_THREE" << std::endl;
			file << "FONT E:/Inne_czcionki/Merienda-Regular.ttf\t <- ustawia sciezke do alternatywnej czcionki" << std::endl;
			file << std::endl;


			file << "4. Spis komend" << std::endl;
			file << "W przypadku gdy pliki w folderze data zostana zle nadpisane mozesz skorzystac z ponizszej listy komend zawierajacej" << std::endl;
			file << "wszystkie niezbedne slowa kluczowe dla poszczegolnych plikow. W razie skasowania zawartosci pliku 'readme.txt' wystarczy usunac go trwale." << std::endl;
			file << "Program w takim wypadku wykryje brak pliku i stworzy go na nowo" << std::endl;
			file << std::endl;

			file << "Lista komend:" << std::endl;
			file << "1) dla pliku 'textures_paths.txt'" << std::endl;
			for (size_t i = 0; i < EMPTY; i++)
				file << TILE_TYPEtoString((TILE_TYPE)i) << (i == EMPTY - 1 ? '.' : ',' ) << std::endl;
			file << std::endl;

			file << "2) dla pliku 'icon_path.txt'" << std::endl;
			file << "ICON" << std::endl;
			file << std::endl;

			file << "3) dla pliku 'font_path.txt'" << std::endl;
			file << "FONT" << std::endl;
			file << std::endl;

			file << "4) dla pliku 'pattern_path.txt'" << std::endl;
			file << "PATTERN" << std::endl;
			file << std::endl;

			file << "5. Przykladowy wzor dla planszy:" << std::endl;
			file << "W 12" << std::endl;
			file << "H 8" << std::endl;
			file << "111111111111" << std::endl;
			file << "000001100000" << std::endl;
			file << "000112211000" << std::endl;
			file << "011123321110" << std::endl;
			file << "011123321110" << std::endl;
			file << "000112211000" << std::endl;
			file << "000001100000" << std::endl;
			file << "111111111111" << std::endl;
			file << std::endl;
		}
	}
	else
	{
		success = false;
		std::string error("Cannot open file from path: ");
		error += _path;
		throw myException_fileSystem(error.c_str());
	}
	file.close();

	return success;
}

settings fileSystem_Game::getSettings() noexcept
{
	return config;
}

size_t fileSystem_Game::getScreenW() noexcept
{
	return config.screenW;
}

size_t fileSystem_Game::getScreenH() noexcept
{
	return config.screenH;
}

bool fileSystem_Board::load()
{
	std::string basicPath("E:/Projekty/MahjongSolitaire/MahjongSolitaire/Mahjong/data/pattern_path.txt");

	bool success = true;

	std::vector<std::string>tmp;
	std::fstream file(basicPath.c_str());
	std::istream_iterator<std::string>fileIterator(file);
	tmp.assign(fileIterator, std::istream_iterator<std::string>());

	if (tmp.empty())
	{
		success = false;
		std::string error("Cannot open file from path: " + basicPath);
		throw myException_fileSystem(error.c_str());
	}
	else
	{
		auto match = std::find(std::begin(tmp), std::end(tmp), "PATTERN_PATH");
		if (match != std::end(tmp))
		{
			auto index = std::distance(std::begin(tmp), match);
			patternPath = tmp.at(index + 1);
		}
	}
	file.close();

	return success;
}

std::string fileSystem_Board::getPatternPath()
{
	return patternPath;
}

bool fileSystem_Achievements::load()
{
	std::string achievementsPath("E:/Projekty/PK4/f310ed3c-gr52-repo/Projekt/Mahjong/Mahjong/data/achievements.txt");

	bool success = true;

	std::vector<std::string>tmp;
	std::fstream file(achievementsPath.c_str());
	std::istream_iterator<std::string>fileIterator(file);
	tmp.assign(fileIterator, std::istream_iterator<std::string>());

	if (tmp.empty())
	{
		success = false;
		std::string error("Cannot open file from path: " + achievementsPath);
		throw myException_fileSystem(error.c_str());
	}
	else
	{
		achievements.resize(ACHIEVEMENT_TOTAL_COUNT + 1);

		for (size_t i = 0; i < ACHIEVEMENT_TOTAL_COUNT + 1; i++)
		{
			auto match = std::find(std::begin(tmp), std::end(tmp), ACHIEVEMENTStoString((ACHIEVEMENT)i).c_str());
			if (match != std::end(tmp))
			{
				auto index = std::distance(std::begin(tmp), match);
				achievements.at(i) = static_cast<bool>(std::stoi(tmp.at(index + 1)));
			}
		}
	}
	file.close();

	return success;
}

bool fileSystem_Achievements::save(bool _overwrite)
{
	std::string achievementsPath("E:/Projekty/PK4/f310ed3c-gr52-repo/Projekt/Mahjong/Mahjong/data/achievements.txt");

	bool success = true;

	std::fstream file(achievementsPath.c_str());

	if (file.good())
	{
		for (size_t i = 0; i < achievements.size(); i++)
			file << ACHIEVEMENTStoString((ACHIEVEMENT)i).c_str() << ' ' << achievements.at(i) << std::endl;
	}
	else
	{
		success = false;
		std::string error("Cannot open file from path: " + achievementsPath);
		throw myException_fileSystem(error.c_str());
	}
	file.close();

	return success;
}

bool fileSystem_Time::load()
{
	std::string timePath("E:/Projekty/PK4/f310ed3c-gr52-repo/Projekt/Mahjong/Mahjong/data/time.txt");

	bool success = true;

	std::vector<std::string>tmp;
	std::fstream file(timePath.c_str());
	std::istream_iterator<std::string>fileIterator(file);
	tmp.assign(fileIterator, std::istream_iterator<std::string>());

	if (tmp.empty())
	{
		success = false;
		std::string error("Cannot open file from path: " + timePath);
		throw myException_fileSystem(error.c_str());
	}
	else
	{
		auto match = std::find(std::begin(tmp), std::end(tmp), "TOTAL_GAME_TIME");
		if (match != std::end(tmp))
		{
			auto index = std::distance(std::begin(tmp), match);
			totalGameTime = std::stod(tmp.at(index + 1));
		}

		match = std::find(std::begin(tmp), std::end(tmp), "BEST_TIME");
		if (match != std::end(tmp))
		{
			auto index = std::distance(std::begin(tmp), match);
			bestTime = std::stod(tmp.at(index + 1));
		}
	}
	file.close();

	return success;
}

bool fileSystem_Time::save(bool _overwrite)
{
	std::string timePath("E:/Projekty/PK4/f310ed3c-gr52-repo/Projekt/Mahjong/Mahjong/data/time.txt");

	bool success = true;

	std::fstream file(timePath.c_str());

	if (file.good())
	{ 
		file << "TOTAL_GAME_TIME " << totalGameTime << std::endl;
		file << "BEST_TIME " << static_cast<size_t>(bestTime) << std::endl;
	}
	else
	{
		success = false;
		std::string error("Cannot open file from path: " + timePath);
		throw myException_fileSystem(error.c_str());
	}
	file.close();

	return success;
}

bool fileSystem_Time::saveCSV(const char* _date, const char* _daytime, const char* _monthYear, int _gameTime, char _separator)
{
	std::string timePath("E:/Projekty/PK4/f310ed3c-gr52-repo/Projekt/Mahjong/Mahjong/results/");
	timePath += _monthYear;
	timePath += ".csv";

	bool success = true;
	bool notExist = false;

	// W celu sprawdzenia istnienia danego pliku tworze strumien wejsciowy dla plikow
	std::ifstream check(timePath.c_str());

	if (!check)
		notExist = true;
	check.close();
		
	std::fstream file(timePath.c_str(), std::ios::out | std::ios::app);
	
	if (file.good())
	{
		if(notExist)
			file << "Date"<< _separator << "Daytime" << _separator << "Game time [s]" << std::endl;
		file << _date << _separator << _daytime << _separator << _gameTime << std::endl;
	}
	else
	{
		success = false;
		std::string error("Cannot open file from path: " + timePath);
		throw myException_fileSystem(error.c_str());
	}
	file.close();

	return success;
}

double fileSystem_Time::getTotalGameTime() noexcept
{
	return totalGameTime;
}

double fileSystem_Time::getBestTime() noexcept
{
	return bestTime;
}

void fileSystem_Time::setTotalGameTime(double _newTotalGameTime) noexcept
{
	totalGameTime = _newTotalGameTime;
}

void fileSystem_Time::setBestTime(double _newBestTime) noexcept
{
	bestTime = _newBestTime;
}