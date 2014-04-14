#include <iostream>

#include "GameEngine.h"
#include "PauseState.h"

PauseState PauseState::m_PauseState;

void PauseState::Init()
{
	
}

void PauseState::Pause() {}

void PauseState::Resume() { }

void PauseState::Terminate() {}

void PauseState::HandleKeyDown(int key)
{
	
}

void PauseState::HandleKeyUp(int key)
{
	if (key == DIK_SPACE)
		GameInst::Instance()->PopState();
}

void PauseState::HandleMouseClick(int button, int x, int y)
{

}

void PauseState::OnMouseDown(int button, int x, int y)
{

}

void PauseState::OnMouseUp(int button, int x, int y)
{

}

void PauseState::MousePassiveMove(int x, int y)
{

}

void PauseState::HandleMouseMove(int x, int y)
{

}

void PauseState::Update(float deltaTime)
{

}

void PauseState::Render3D()
{

}

void PauseState::Render2D()
{

}

void PauseState::RenderDebug()
{

}

void PauseState::Clean()
{
	std::cout << "PauseState Clean Successful" << std::endl;
}

void PauseState::End()
{

}