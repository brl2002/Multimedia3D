#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "GameObject.h"
#include "Singleton.h"
#include <vector>

class GameState;

class GameEngine
{
public:
	~GameEngine();

	void Init();
	void Clean();
	void Terminate();

	void ChangeState(GameState* state);
	void PushState(GameState* state);
	void PopState();

	void HandleKeyUp(int key);
	void HandleKeyDown(int key);
	void HandleMouseClick(int button, int x, int y);
	void OnMouseDown(int button, int x, int y);
	void OnMouseUp(int button, int x, int y);
	void MousePassiveMove(int x, int y);
	void HandleMouseMove(int x, int y);
	void End();

	void Update(float deltaTime);
	
	void Render3D();

	void Render2D();

	void RenderDebug();

	void GameOver() { m_gameOver = true; }
	bool IsGameOVer() { return m_gameOver; }

	bool Running() { return m_bRunning; };
	void Quit() { m_bRunning = false; };

private:
	GameEngine() {}
	friend class Singleton<GameEngine>;

	// Stack of states
	std::vector<GameState*> states;

	bool m_bRunning;
	bool m_gameOver;
};
typedef Singleton<GameEngine> GameInst; // instance of the game

#endif