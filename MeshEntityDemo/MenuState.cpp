#include <iostream>
#include "..\Engine\Advanced2D.h"
#include "GameEngine.h"
#include "MenuState.h"
#include "PlayState.h"
#include "Game.h"

MenuState MenuState::m_MenuState;
Advanced2D::Sprite* background1;
void MenuState::Init()
{
	background1 = new Advanced2D::Sprite();
	background1->loadImage("../res/GameStart.png");
	background1->setPosition(0, 0);
}

void MenuState::Pause()
{
	std::cout << "MenuState Paused" << std::endl;
}

void MenuState::Resume()
{
	std::cout << "MenuState Resumed" << std::endl;
}

void MenuState::Terminate() {}

void MenuState::HandleKeyDown(int key)
{
	
}

void MenuState::HandleKeyUp(int key)
{
	if (key == DIK_SPACE)
		GameInst::Instance()->ChangeState(PlayState::Instance());
}

void MenuState::HandleMouseClick(int button, int x, int y)
{

}

void MenuState::OnMouseDown(int button, int x, int y)
{

}

void MenuState::OnMouseUp(int button, int x, int y)
{

}

void MenuState::MousePassiveMove(int x, int y)
{

}

void MenuState::HandleMouseMove(int x, int y)
{

}

void MenuState::Update(float deltaTime)
{

}

void MenuState::Render3D()
{

}

void MenuState::Render2D()
{
	background1->draw();
}

void MenuState::RenderDebug()
{

}

void MenuState::Clean()
{

}

void MenuState::End()
{
	delete background1;

	//std::cout << "MenuState Clean Successful" << std::endl;
	OutputDebugString(L"MenuState Clean Successful");
}