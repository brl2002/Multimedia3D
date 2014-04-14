#ifndef GAME_H
#define GAME_H

class Game
{
public:
	static const int SCREEN_WIDTH = 800;
	static const int SCREEN_HEIGHT = 600;

	static void GameOver();

	static int getMouseX() { return Game::mouseX; };
	static int getMouseY() { return Game::mouseY; };
	
	static int getEnemiesKilled() { return Game::enemiesKilled; };
	static int getSecondsPassed() { return Game::secondsPassed; };

	static int getPlayerHealth() { return Game::playerHealth; };
	static int getPrincessHealth() { return Game::princessHealth; };

	static void ResetScore();

	static void hurtPlayer() { Game::playerHealth--; };
	static void hurtPrincess() { Game::princessHealth--; };
	static void enemyKilled() { Game::enemiesKilled++; };
	static void secondPassed() { Game::secondsPassed++; };

private:
	static int mouseX;
	static int mouseY;

	static int enemiesKilled;
	static int secondsPassed;
	static int playerHealth;
	static int princessHealth;
};

#endif