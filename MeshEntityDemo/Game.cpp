#include "Game.h"
#include "GameEngine.h"
#include "EndState.h"

int Game::mouseX = 0;
int Game::mouseY = 0;

int Game::enemiesKilled = 0;
int Game::secondsPassed = 0;
int Game::playerHealth = 3;
int Game::princessHealth = 3;

void Game::GameOver()
{
	Game::enemiesKilled = 0;
	Game::secondsPassed = 0;
	Game::playerHealth = 3;
	Game::princessHealth = 3;

	GameInst::Instance()->GameOver();
	GameInst::Instance()->ChangeState(EndState::Instance());
}

void Game::ResetScore()
{
	Game::enemiesKilled = 0;
	Game::secondsPassed = 0;
	Game::playerHealth = 3;
	Game::princessHealth = 3;
}