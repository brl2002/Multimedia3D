#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "GameState.h"
#include <Windows.h>

class MenuState : public GameState
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
	static MenuState* Instance()
	{
		return &m_MenuState;
	}

protected:
	MenuState() {}

private:
	static MenuState m_MenuState;
};

#endif