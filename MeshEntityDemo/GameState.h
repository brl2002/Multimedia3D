#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "GameEngine.h"

class GameState
{
public:
	virtual void Init() = 0;
	virtual void Clean() = 0;
	virtual void Terminate() = 0;

	virtual void Pause() = 0;
	virtual void Resume() = 0;

	virtual void HandleKeyUp(int key) = 0;
	virtual void HandleKeyDown(int key) = 0;
	virtual void HandleMouseClick(int button, int x, int y) = 0;
	virtual void OnMouseDown(int button, int x, int y) = 0;
	virtual void OnMouseUp(int button, int x, int y) = 0;
	virtual void MousePassiveMove(int x, int y) = 0;
	virtual void HandleMouseMove(int x, int y) = 0;
	virtual void End() = 0;

	virtual void Update(float deltaTime) = 0;
	virtual void Render3D() = 0;
	virtual void Render2D() = 0;

	virtual void RenderDebug() = 0;

	void ChangeState(GameState* state)
	{
		GameInst::Instance()->ChangeState(state);
	}

protected:
	GameState() {}
};

#endif