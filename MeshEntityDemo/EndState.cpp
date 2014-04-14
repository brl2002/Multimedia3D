#include <iostream>

#include "GameEngine.h"
#include "EndState.h"
#include "PlayState.h"

EndState EndState::m_EndState;
Advanced2D::Sprite* backgroundEnd;
void EndState::Init()
{
	backgroundEnd = new Advanced2D::Sprite();
	backgroundEnd->loadImage("../res/GameOver.png");
	backgroundEnd->setPosition(0, 0);
}

void EndState::Pause() {}

void EndState::Resume() { }

void EndState::Terminate()
{

}

void EndState::HandleKeyDown(int key)
{

}

void EndState::HandleKeyUp(int key)
{
	if (key == DIK_SPACE)
		GameInst::Instance()->ChangeState(PlayState::Instance());
}

void EndState::HandleMouseClick(int button, int x, int y)
{

}

void EndState::OnMouseDown(int button, int x, int y)
{

}

void EndState::OnMouseUp(int button, int x, int y)
{

}

void EndState::MousePassiveMove(int x, int y)
{

}

void EndState::HandleMouseMove(int x, int y)
{

}

void EndState::Update(float deltaTime)
{

}

void EndState::Render3D()
{

}

void EndState::Render2D()
{
	backgroundEnd->draw();
}

void EndState::RenderDebug()
{

}

void EndState::Clean()
{
	std::cout << "PauseState Clean Successful" << std::endl;
}

void EndState::End()
{
	delete backgroundEnd;
}