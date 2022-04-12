#include<iostream>

#include"Game.h"
#include"Button.h"
#include"myException.h"
#include"timeSystem.h"

void Game::init()
{

	if (fileSystem_Game::load())
	{
		gameEngine = new Engine(getSettings());
		gameEngine->init();
		gameEngine->loadResources();

		gameBoard = new Board();
		gameBoard->init(getScreenW(),getScreenH());

		gameEvent = new SDL_Event;

		gameMouse = new Mouse;

		gameButtons.resize(BUTTON_PLAY_AGAIN + 1); // W grze beda cztery funkcjonalne przyciski + przycisk time i achievement nie posiadajacy interakcji
		gameButtons.at(BUTTON_RESTART).init(20, 20, getScreenW(), getScreenH(), "RESTART");
		gameButtons.at(BUTTON_HELP).init(gameButtons.at(0).getButtonPosition()->x + gameButtons.at(0).getButtonPosition()->w * 2, 20, getScreenW(), getScreenH(), "HELP");
		gameButtons.at(BUTTON_SHUFFLE).init(gameButtons.at(1).getButtonPosition()->x + gameButtons.at(1).getButtonPosition()->w * 2, 20, getScreenW(), getScreenH(), "SHUFFLE");
		gameButtons.at(BUTTON_TIME).init(gameButtons.at(2).getButtonPosition()->x + gameButtons.at(2).getButtonPosition()->w * 2, 20, getScreenW(), getScreenH(), "TIME:");
		gameButtons.at(BUTTON_ACHIEVEMENT).init(getScreenW() / 2, getScreenH() - 85, getScreenW(), getScreenH(), "ACHIEVEMENT");
		gameButtons.at(BUTTON_PLAY_AGAIN).init(getScreenW() / 2, getScreenH() / 2, getScreenW(), getScreenH(), "PLAY AGAIN");
		// TODO przycisk wyjścia z gry i przycisk zagraj ponownie

		gameAchievements = new Achievements();

		gameTime = new timeSystem;
		gameTime->init();
		gameTime->addObserver(gameAchievements);
	}
}

Game::~Game()
{
	if (gameEngine)
		delete gameEngine;
	if (gameBoard)
		delete gameBoard;
	if (gameTime)
		delete gameTime;
	if (gameMouse)
		delete gameMouse;
	if (gameEvent)
		delete gameEvent;
	if (gameAchievements)
		delete gameAchievements;

	gameEngine = nullptr;
	gameBoard = nullptr;
	gameTime = nullptr;
	gameMouse = nullptr;
	gameEvent = nullptr;
	gameAchievements = nullptr;
}

void Game::loop()
{
	while (gameLoop)
	{
		if(!isWin())
			gameTime->start();

		while (SDL_PollEvent(gameEvent) != 0)
		{
			if (gameEvent->type == SDL_QUIT)
				gameLoop = false;
			gameMouse->handleEvent(gameEvent);
			if (gameMouse->checkMouseClick())
			{
				for (size_t i = 0; i < gameButtons.size(); i++)
					if (gameButtons.at(i).chceckSelected(gameMouse->getPosition()))
						switch (i)
						{
						case BUTTON_RESTART:
							gameTime->update(); // Update poniewaz musimy zaktualizowac czas w ktorym oczekiwalismy na reset i dopiero potem zresetowac
							gameTime->start();
							gameTime->reset();
							gameBoard->reset(getScreenW(),getScreenH());
							break;
						case BUTTON_HELP:
							if (gameBoard->getTotalNumberOfTiles() > 2)
							{
								gameTime->addTimePenalty(std::chrono::seconds(30));
								gameBoard->markPair();
							}
							break;
						case BUTTON_SHUFFLE:
							gameTime->addTimePenalty(std::chrono::seconds(30));
							gameBoard->shuffle();
							gameBoard->lookForPair();
							break;
						case BUTTON_PLAY_AGAIN:
							if (isWin())
							{
								gameTime->saveGameInfo();
								gameBoard->reset(getScreenW(), getScreenH());
								gameTime->checkForUpdate();
								gameTime->update(); // Update poniewaz musimy zaktualizowac czas w ktorym oczekiwalismy na reset i dopiero potem zresetowac
								gameTime->start();
								gameTime->reset();
							}
							break;
						default:
							break;
						}
				gameBoard->selectTile(gameMouse->getPosition());
			}
		}
		try
		{
			gameEngine->clearCurrentState();

			for(size_t i = 0; i < gameButtons.size(); i++)
				if (i == BUTTON_ACHIEVEMENT && gameAchievements->isAchievementToDisplay())
				{
					gameButtons.at(BUTTON_ACHIEVEMENT).setText(gameAchievements->getAchievementFromQueue().c_str());
					gameButtons.at(BUTTON_ACHIEVEMENT).scaleRectangle(getScreenW(),getScreenH());
					gameButtons.at(BUTTON_ACHIEVEMENT).setPosition(getScreenW() / 2 - gameButtons.at(BUTTON_ACHIEVEMENT).getBackgroundPosition()->w / 2, getScreenH() - 85);
					gameAchievements->addDuration(gameTime->getLoopTime());
					drawButton(gameButtons.at(BUTTON_ACHIEVEMENT));
					if (gameAchievements->getDurationTime() >= 10.0)
						gameAchievements->removeAchievmentFromQueue();
				}
				else if (i == BUTTON_PLAY_AGAIN && isWin() )
				{
					std::string tmp("Play again! Your time: ");
					tmp += gameTime->getTimeAsString();
					gameButtons.at(BUTTON_PLAY_AGAIN).setText(tmp.c_str());
					gameButtons.at(BUTTON_PLAY_AGAIN).scaleRectangle(getScreenW(), getScreenH());
					gameButtons.at(BUTTON_PLAY_AGAIN).setPosition(getScreenW() / 2 - gameButtons.at(BUTTON_PLAY_AGAIN).getButtonPosition()->w / 2, getScreenH() / 2 - gameButtons.at(BUTTON_PLAY_AGAIN).getButtonPosition()->h / 2);
					drawButton(gameButtons.at(BUTTON_PLAY_AGAIN));
				}
				else if(i != BUTTON_ACHIEVEMENT && i != BUTTON_PLAY_AGAIN)
					drawButton(gameButtons.at(i));

			drawBoard();

			gameEngine->drawCurrentState();
		}
		catch (myException& e)
		{
			std::cerr << e.what() << std::endl;
		}
		if (!isWin())
			gameTime->update();
		gameButtons.at(BUTTON_TIME).setText(gameTime->getTimeAsString().c_str());
		gameButtons.at(BUTTON_TIME).scaleRectangle(getScreenW(),getScreenH());
	}
}

void Game::drawBoard()
{
	// zmienne iteracyjne muszą byc intami poniewaz tablice trzeba rysowac od konca aby plytki odpowiednio na siebie nachodzily
	// Zatem warunek końcowy będzie sprawdzany dla liczby -1, wtedy zwarace zostanie false, zatem nie mozemy uzyc size_t = unsigned int
	for (int i = 0; i < gameBoard->getMaxY(); i++)
	{
		for (int j = gameBoard->getMaxX() - 1; j >= 0; j--)
		{
			for (int k = 0; k < gameBoard->getMaxZ(); k++)
			{
				gameEngine->drawTile(gameBoard->board[i][j][k]->getCoOrdinates(), gameBoard->board[i][j][k]->getTileType(), gameBoard->board[i][j][k]->getSelected(), gameBoard->board[i][j][k]->getHelpInfo());
			}
		}
	}
}

void Game::drawButton(Button _button)
{
	gameEngine->drawTile(_button.getBackgroundPosition(), _button.getBackground());
	gameEngine->drawText(_button.getButtonPosition(),_button.getText().c_str());
}

bool Game::isWin()
{
	return (gameBoard->getTotalNumberOfTiles() == 0 || gameBoard->checkBlockedTiles());
}
