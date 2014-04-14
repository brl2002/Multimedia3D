#include "GameEngine.h"
#include "MenuState.h"
#include "GameState.h"
#include "Windows.h"
#include <iostream>

GameEngine::~GameEngine()
{

}

void GameEngine::Init()
{
	m_bRunning = true;
	m_gameOver = false;
	ChangeState(MenuState::Instance());
}

void GameEngine::Terminate()
{
	states.back()->Terminate();
}

void GameEngine::ChangeState(GameState* state)
{
	// clean up the current state
	if (!states.empty())
	{
		states.back()->End();
		states.pop_back();
	}

	// store and init the new state
	states.push_back(state);
	states.back()->Init();
}

void GameEngine::PushState(GameState* state)
{
	// pause current state
	if (!states.empty())
	{
		states.back()->Pause();
	}

	// store and init the new state
	states.push_back(state);
	states.back()->Init();
}

void GameEngine::PopState()
{
	// clean up the current state
	if (!states.empty())
	{
		states.back()->End();
		states.pop_back();
	}

	// resume previous state
	if (!states.empty())
	{
		states.back()->Resume();
	}
}

void GameEngine::HandleKeyUp(int key)
{
	// let the state handle events
	states.back()->HandleKeyUp(key);
}

void GameEngine::HandleKeyDown(int key)
{
	// let the state handle events
	states.back()->HandleKeyDown(key);
}

void GameEngine::HandleMouseClick(int button, int x, int y)
{
	// let the state handle events
	states.back()->HandleMouseClick(button, x, y);
}

void GameEngine::OnMouseDown(int button, int x, int y)
{
	// let the state handle events
	states.back()->OnMouseDown(button, x, y);
}

void GameEngine::OnMouseUp(int button, int x, int y)
{
	// let the state handle events
	states.back()->OnMouseUp(button, x, y);
}

void GameEngine::MousePassiveMove(int x, int y)
{
	states.back()->MousePassiveMove(x, y);
}

void GameEngine::HandleMouseMove(int x, int y)
{
	states.back()->HandleMouseMove(x, y);
}

void GameEngine::Update(float deltaTime)
{
	// let the state update the game
	states.back()->Update(deltaTime);
}

void GameEngine::Render3D()
{
	// let the state draw the screen
	states.back()->Render3D();
}

void GameEngine::Render2D()
{
	states.back()->Render2D();
}

void GameEngine::RenderDebug()
{
	states.back()->RenderDebug();
}

void GameEngine::Clean()
{
	states.back()->Clean();

	if (m_gameOver)
	{
		m_gameOver = false;
		states.back()->Terminate();
	}
}

void GameEngine::End()
{
	while (!states.empty())
	{
		states.back()->End();
		states.pop_back();
	}
}