#ifndef ENDSTATE_H
#define ENDSTATE_H

#include "Game.h"
#include "GameObject.h"
#include "GameState.h"

class EndState : public GameState
{
public:
	void Init();
	void Clean();
	void Terminate();

	void Pause();
	void Resume();

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

	// Implement Singleton Pattern
	static EndState* Instance()
	{
		return &m_EndState;
	}

protected:
	EndState() {}

private:
	static EndState m_EndState;
};

#endif