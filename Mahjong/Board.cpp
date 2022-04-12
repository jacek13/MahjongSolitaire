#include<iostream>
#include<vector>
#include<algorithm>
#include<random>

#include"structures.h"
#include"Board.h"
#include"myException.h"

bool Board::chceckTheCorrectness() noexcept
{
    //Sprawdzenie czy ilość płytek jest liczba parzysta, jeżeli nie funkcja zwroci false
    //Metoda sprawdza rowniez czy znaki ASCII mieszcza sie w przedziale od '0' do '9'
    bool success = true;
    maxNumberOfTiles = 0;

    for (size_t i = 0; i < map.size(); i++)
        for (size_t j = 0; j < map.at(i).size(); j++)
            if (map.at(i).at(j) >= '0' && map.at(i).at(j) <= '9')
                maxNumberOfTiles += map.at(i).at(j) - '0';
            else
                return success = false;

    totalNumberOfTiles = maxNumberOfTiles;

    return !(maxNumberOfTiles % 2) ? success = true : success = false;
}

void Board::initGameTiles() noexcept
{
    gameTiles.resize(maxNumberOfTiles);

    std::mt19937 randomGenerator(randomDevice());
    std::uniform_int_distribution<>distribution(0, DEFAULT - 1); // W celu uzyskania lepszego rozlozenia wartosci losowych, skorzystalem z rozkladu jednostajnego
    //Dzieki temu plytki beda losowane z rownym prawdopodobienstwem. Jest to lepsza metoda niz uzywanie funkcji rand(), ktora daje malo wiarygodne zroznicowanie

    for (size_t i = 0; i < gameTiles.size(); i += 2)
        gameTiles.at(i) = gameTiles.at(i + 1) = (TILE_TYPE)distribution(randomGenerator);
}

void Board::updateActiveTiles() noexcept
{
    //aby nie przechodzic ponownie przez 3 wymiarowy vector, zostana zapisane wspolrzedne aktywnych plytek
    activeTilesPos.clear();
    for (size_t i = 0; i < board.size(); i++)
        for (size_t j = 0; j < board[0].size(); j++)
            for (size_t k = 0; k < board[0][0].size(); k++)
                if (board[i][j][k]->getActive())
                    activeTilesPos.push_back(board[i][j][k]->getPosition());
}

void Board::updateAccessibleTiles() noexcept
{
    accessibleTilesPos.clear();
    accessibleTilesTypes.clear();
    unmarkPair();

    if (!activeTilesPos.empty())
    {
        for (size_t i = 0; i < activeTilesPos.size(); i++)
        {
            if (activeTilesPos.at(i).z == maxZ - 1)
            {
                if (activeTilesPos.at(i).x == 0 || activeTilesPos.at(i).x == maxX - 1)
                {
                    board[activeTilesPos.at(i).y][activeTilesPos.at(i).x][activeTilesPos.at(i).z]->setAccessibility(true);
                    accessibleTilesPos.push_back(activeTilesPos.at(i));
                    accessibleTilesTypes.push_back(board[activeTilesPos.at(i).y][activeTilesPos.at(i).x][activeTilesPos.at(i).z]->getTileType());
                }
                else if (board[activeTilesPos.at(i).y][activeTilesPos.at(i).x - 1][activeTilesPos.at(i).z]->getTileType() == EMPTY || board[activeTilesPos.at(i).y][activeTilesPos.at(i).x + 1][activeTilesPos.at(i).z]->getTileType() == EMPTY)
                {
                    board[activeTilesPos.at(i).y][activeTilesPos.at(i).x][activeTilesPos.at(i).z]->setAccessibility(true);
                    accessibleTilesPos.push_back(activeTilesPos.at(i));
                    accessibleTilesTypes.push_back(board[activeTilesPos.at(i).y][activeTilesPos.at(i).x][activeTilesPos.at(i).z]->getTileType());
                }
                else 
                {
                    board[activeTilesPos.at(i).y][activeTilesPos.at(i).x][activeTilesPos.at(i).z]->setAccessibility(false);
                }
            }
            else if (activeTilesPos.at(i).z + 1 < maxZ)
            {
                if (board[activeTilesPos.at(i).y][activeTilesPos.at(i).x][activeTilesPos.at(i).z + 1]->getTileType() == EMPTY)
                {
                    if (activeTilesPos.at(i).x == 0 || activeTilesPos.at(i).x == maxX - 1)
                    {
                        board[activeTilesPos.at(i).y][activeTilesPos.at(i).x][activeTilesPos.at(i).z]->setAccessibility(true);
                        accessibleTilesPos.push_back(activeTilesPos.at(i));
                        accessibleTilesTypes.push_back(board[activeTilesPos.at(i).y][activeTilesPos.at(i).x][activeTilesPos.at(i).z]->getTileType());
                    }
                    else if (board[activeTilesPos.at(i).y][activeTilesPos.at(i).x - 1][activeTilesPos.at(i).z]->getTileType() == EMPTY || board[activeTilesPos.at(i).y][activeTilesPos.at(i).x + 1][activeTilesPos.at(i).z]->getTileType() == EMPTY)
                    {
                        board[activeTilesPos.at(i).y][activeTilesPos.at(i).x][activeTilesPos.at(i).z]->setAccessibility(true);
                        accessibleTilesPos.push_back(activeTilesPos.at(i));
                        accessibleTilesTypes.push_back(board[activeTilesPos.at(i).y][activeTilesPos.at(i).x][activeTilesPos.at(i).z]->getTileType());
                    }
                    else
                    {
                        board[activeTilesPos.at(i).y][activeTilesPos.at(i).x][activeTilesPos.at(i).z]->setAccessibility(false);
                    }
                }
                else
                {
                    board[activeTilesPos.at(i).y][activeTilesPos.at(i).x][activeTilesPos.at(i).z]->setAccessibility(false);
                }
            }
            else
            {
                board[activeTilesPos.at(i).y][activeTilesPos.at(i).x][activeTilesPos.at(i).z]->setAccessibility(false);
            }
            //jezeli nie jest przykryta z gory lub jest na maksymalnej wysokosci
                //sprawdz jej sasiedztwo
                    //dla true dodaj do available i zmien status plytki na accesable
                    // ewentualnie zmien tylko plytki na accesable
            //w przeciwnym razie zmien status plytki na false accesable i przegladaj dalej
        }
    }
}

bool sortMyPair(const std::pair<TILE_TYPE, position>& _a, const std::pair<TILE_TYPE, position>& _b)
{
    return (_a.first < _b.first);
}

bool equalMyPair(const std::pair<TILE_TYPE, position>& _a, const std::pair<TILE_TYPE, position>& _b)
{
    return _a.first == _b.first ? true : false;
}

bool Board::lookForPair() noexcept
{
    bool success = false;
    updateActiveTiles();    // aktualizuje te ktore sa jeszcze w grze
    updateAccessibleTiles(); // aktualizuje te ktore da sie wybrac muszka, czyli te nie zablokowane
    
    std::vector<std::pair<TILE_TYPE, position>>tmp;
    tmp.resize(accessibleTilesTypes.size());

    for (size_t i = 0; i < tmp.size(); i++)
    {
        tmp.at(i).first = accessibleTilesTypes.at(i);
        tmp.at(i).second = accessibleTilesPos.at(i);
    }

    while (true && totalNumberOfTiles > 2)
    {
        std::sort(accessibleTilesTypes.begin(),accessibleTilesTypes.end()); //sortowanie typow plytek ktore sa dostepne do wyboru
        std::sort(tmp.begin(), tmp.end(), sortMyPair);
        
        // TEST TODO kiedys, pomysl taki zeby zamiast 2 wektorow uzywac jednego przechowujacego std::pair
        success = std::adjacent_find(tmp.begin(), tmp.end(), equalMyPair) != tmp.end();
        
        if (success)
        {
            auto iterator = std::adjacent_find(tmp.begin(), tmp.end(), equalMyPair);
            auto distance = std::distance(tmp.begin(), iterator);
            helpTiles.first = tmp.at(distance).second;
            helpTiles.second = tmp.at(distance + 1).second;
            break;
        }
        else
        {
            shuffle();
            updateAccessibleTiles();

            for (size_t i = 0; i < tmp.size(); i++)
            {
                tmp.at(i).first = accessibleTilesTypes.at(i);
                tmp.at(i).second = accessibleTilesPos.at(i);
            }
        }
    }
    return success;
}

bool Board::areSameTiles() noexcept
{
    return firstSelectedTile->getTileType() == SecondSelectedTile->getTileType() ? true : false;
}

bool Board::selectTile(SDL_Point _cursor) noexcept
{
    bool isSelected = false;

    for(size_t i = 0; i < accessibleTilesPos.size(); i++)
            if (_cursor.x < board[accessibleTilesPos.at(i).y][accessibleTilesPos.at(i).x][accessibleTilesPos.at(i).z]->getCoOrdinates()->x)
                isSelected = false;
            else if (_cursor.x > board[accessibleTilesPos.at(i).y][accessibleTilesPos.at(i).x][accessibleTilesPos.at(i).z]->getCoOrdinates()->x + board[accessibleTilesPos.at(i).y][accessibleTilesPos.at(i).x][accessibleTilesPos.at(i).z]->getCoOrdinates()->w)
                isSelected = false;
            else if (_cursor.y < board[accessibleTilesPos.at(i).y][accessibleTilesPos.at(i).x][accessibleTilesPos.at(i).z]->getCoOrdinates()->y)
                isSelected = false;
            else if (_cursor.y > board[accessibleTilesPos.at(i).y][accessibleTilesPos.at(i).x][accessibleTilesPos.at(i).z]->getCoOrdinates()->y + board[accessibleTilesPos.at(i).y][accessibleTilesPos.at(i).x][accessibleTilesPos.at(i).z]->getCoOrdinates()->h)
                isSelected = false;
            else
            {
                isSelected = true;
                board[accessibleTilesPos.at(i).y][accessibleTilesPos.at(i).x][accessibleTilesPos.at(i).z]->setSelected(true);
                if (!firstSelectedTile && !SecondSelectedTile)
                    firstSelectedTile = board[accessibleTilesPos.at(i).y][accessibleTilesPos.at(i).x][accessibleTilesPos.at(i).z];
                else if (firstSelectedTile == board[accessibleTilesPos.at(i).y][accessibleTilesPos.at(i).x][accessibleTilesPos.at(i).z])
                {
                    firstSelectedTile->setSelected(false);
                    firstSelectedTile = nullptr;
                }
                else if(firstSelectedTile != board[accessibleTilesPos.at(i).y][accessibleTilesPos.at(i).x][accessibleTilesPos.at(i).z] && !SecondSelectedTile)
                {
                    SecondSelectedTile = board[accessibleTilesPos.at(i).y][accessibleTilesPos.at(i).x][accessibleTilesPos.at(i).z];
                    if (areSameTiles())
                    {
                        firstSelectedTile->setActive(false);
                        firstSelectedTile->setAccessibility(false);
                        firstSelectedTile->setSelected(false);
                        firstSelectedTile->setTileType(EMPTY);

                        SecondSelectedTile->setActive(false);
                        SecondSelectedTile->setAccessibility(false);
                        SecondSelectedTile->setSelected(false);
                        SecondSelectedTile->setTileType(EMPTY);

                        firstSelectedTile = nullptr;
                        SecondSelectedTile = nullptr;
                        totalNumberOfTiles -= 2;
                        lookForPair();
                    }
                    else
                    {
                        firstSelectedTile->setSelected(false);
                        SecondSelectedTile->setSelected(false);

                        firstSelectedTile = nullptr;
                        SecondSelectedTile = nullptr;
                    }
                }
                break;
            }

    return isSelected;
}

void Board::shuffle() noexcept
{
    updateActiveTiles();
    gameTiles.clear();
    for (size_t i = 0; i < activeTilesPos.size(); i++)
        gameTiles.push_back(board[activeTilesPos.at(i).y][activeTilesPos.at(i).x][activeTilesPos.at(i).z]->getTileType());

    std::mt19937 randomGenerator(randomDevice());

    std::shuffle(gameTiles.begin(),gameTiles.end(), randomGenerator);

    for (size_t i = 0; i < activeTilesPos.size(); i++)
    {
        board[activeTilesPos.at(i).y][activeTilesPos.at(i).x][activeTilesPos.at(i).z]->setTileType(gameTiles.back());
        gameTiles.pop_back();
    }
}

void Board::markPair() noexcept
{
    if (totalNumberOfTiles > 2)
    {
        if (board[helpTiles.first.y][helpTiles.first.x][helpTiles.first.z]->getActive() && board[helpTiles.second.y][helpTiles.second.x][helpTiles.second.z]->getActive())
        {
            board[helpTiles.first.y][helpTiles.first.x][helpTiles.first.z]->setHelpInfo(true);
            board[helpTiles.second.y][helpTiles.second.x][helpTiles.second.z]->setHelpInfo(true);
        }
        else
            unmarkPair();
    }
}

void Board::unmarkPair() noexcept
{

    board[helpTiles.first.y][helpTiles.first.x][helpTiles.first.z]->setHelpInfo(false);
    board[helpTiles.second.y][helpTiles.second.x][helpTiles.second.z]->setHelpInfo(false);
}

size_t Board::getMaxY() noexcept
{
    return maxY;
}

size_t Board::getMaxX() noexcept
{
    return maxX;
}

size_t Board::getMaxZ() noexcept
{
    return maxZ;
}

size_t Board::getTotalNumberOfTiles() noexcept
{
    return totalNumberOfTiles;
}

std::pair<position, position> Board::getHelpTiles() noexcept
{
    return helpTiles;
}

bool Board::loadMap()
{
    std::string patternPath = fileSystem_Board::getPatternPath();

    bool success = true;

    std::vector<std::string>tmp;
    std::fstream file(patternPath.c_str());
    std::istream_iterator<std::string>fileIterator(file);
    tmp.assign(fileIterator, std::istream_iterator<std::string>());

    if (tmp.empty())
    {
        success = false;
        std::string error("Cannot open file from path: " + patternPath);
        throw myException_fileSystem(error.c_str());
    }
    else
    {
        auto match = std::find(std::begin(tmp), std::end(tmp), "W");
        if (match != std::end(tmp))
        {
            auto index = std::distance(std::begin(tmp), match);
            maxX = static_cast<size_t>(std::stoi(tmp.at(index + 1)));
        }

        match = std::find(std::begin(tmp), std::end(tmp), "H");
        if (match != std::end(tmp))
        {
            auto index = std::distance(std::begin(tmp), match);
            maxY = static_cast<size_t>(std::stoi(tmp.at(index + 1)));
        }

        match = std::find(std::begin(tmp), std::end(tmp), "PATTERN");
        if (match != std::end(tmp))
        {
            auto index = std::distance(std::begin(tmp), match);
            for (size_t i = 0; i < maxY; i++)
                map.push_back(tmp.at(index + 1 + i));

            //znalezienie maksymalnej wysokosci planszy
            size_t maxElement = 0;
            std::string::iterator iterator;
            for (size_t i = 0; i < map.size(); i++)
            {
                iterator = std::max_element(map.at(i).begin(), map.at(i).end());
                if (maxElement <= *iterator)
                    maxElement = *iterator;
            }
            maxZ = maxElement - '0';
        }
    }
    file.close();

    return success;
}

void Board::scaleTiles(size_t _screenW, size_t _screenH) noexcept
{
    SDL_Rect tmpRect = { _screenW / 4, _screenH / 6,0,0 };
    tmpRect.w = _screenW / (maxX * 2);
    tmpRect.h = _screenH / (maxY * 1.25);
    int offsetX = tmpRect.w * 0.125;
    int offsetY = tmpRect.h * 0.09;

    for (size_t i = 0; i < board.size(); i++)
    {
        for (size_t j = 0; j < board[0].size(); j++)
        {
            SDL_Rect tmp2 = tmpRect;
            for (size_t k = 0; k < board[0][0].size(); k++)
            {
                board[i][j][k]->setCoOrdinates(tmp2);
                tmp2.x += offsetX;
                tmp2.y -= offsetY;
            }
            tmpRect.x += tmpRect.w - offsetX;
        }
        tmpRect.y += tmpRect.h - offsetY;
        tmpRect.x = _screenW / 4;
    }
}

void Board::init(size_t _screenW, size_t _screenH)
{
    if (load())
        loadMap();

    if (chceckTheCorrectness())
    {
        initGameTiles();

        //Narazie wypelniam cala objetosc prostopadloscianu ale w przyszlosci mozna to zoptymalizowac
        board.resize(getMaxY());
        for (size_t i = 0; i < board.size(); i++)
            board[i].resize(getMaxX());
        for (size_t i = 0; i < board.size(); i++)
            for (size_t j = 0; j < board[i].size(); j++)
                board[i][j].resize(getMaxZ());

        //Inicjalizowanie zawartosci
        for (size_t i = 0; i < board.size(); i++)
        {
            for (size_t j = 0; j < board[0].size(); j++)
            {
                for (size_t k = 0; k < board[0][0].size(); k++)
                {
                    board[i][j][k] = new Tile;
                    if (map.at(i).at(j) != '0' && k < map.at(i).at(j) - '0')
                    {
                        board[i][j][k]->init(true, false, false, false, { j,i,k }, { 0,0,0,0 }, gameTiles.back());
                        gameTiles.pop_back();
                    }
                    else
                        board[i][j][k]->init(false, false, false, false, { j,i,k }, { 0,0,0,0 }, EMPTY);
                }
            }
        }

        scaleTiles(_screenW, _screenH);
        shuffle();
        lookForPair();
    }
    else
    {
        std::string error("The board has no even number of pieces!\nOr values out of range [0 : 9]!\nCheck the pattern files.\n");
        throw myException_Board(error.c_str());
    }
}

void Board::reset(size_t _screenW, size_t _screenH) noexcept
{
    chceckTheCorrectness();
    initGameTiles();
    firstSelectedTile = nullptr;
    SecondSelectedTile = nullptr;

    //Inicjalizowanie zawartosci
    for (size_t i = 0; i < board.size(); i++)
    {
        for (size_t j = 0; j < board[0].size(); j++)
        {
            for (size_t k = 0; k < board[0][0].size(); k++)
            {
                if (map.at(i).at(j) != '0' && k < map.at(i).at(j) - '0')
                {
                    board[i][j][k]->setTileType(gameTiles.back());
                    gameTiles.pop_back();
                    board[i][j][k]->setActive(true);
                    board[i][j][k]->setSelected(false);
                    board[i][j][k]->setAccessibility(false);
                    board[i][j][k]->setHelpInfo(false);
                }
                else
                {
                    board[i][j][k]->setTileType(EMPTY);
                    board[i][j][k]->setActive(false);
                    board[i][j][k]->setSelected(false);
                    board[i][j][k]->setAccessibility(false);
                    board[i][j][k]->setHelpInfo(false);
                }
            }
        }
    }

    scaleTiles(_screenW, _screenH);
    shuffle();
    lookForPair();
}

bool Board::checkBlockedTiles() noexcept
{
    if(activeTilesPos.size() == 2)
        return activeTilesPos.at(0).x == activeTilesPos.at(1).x && activeTilesPos.at(0).y == activeTilesPos.at(1).y ? true : false;
    return false;
}

Board::~Board()
{
    //Zwalnianie pamięci
    for (size_t i = 0; i < board.size(); i++)
        for (size_t j = 0; j < board[0].size(); j++)
            for (size_t k = 0; k < board[0][0].size(); k++)
            {
                delete board[i][j][k];
                board[i][j][k] = nullptr;
            }
}