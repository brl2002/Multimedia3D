#include <iostream>
#include "Game.h"
#include "GameEngine.h"
#include "PlayState.h"
#include "PauseState.h"
#include "GUIManager.h"

PlayState PlayState::m_PlayState;

void PlayState::Init()
{
	GamePhysics::getInstance().Initialize();
	GUIManager::getInstance()->Init();

	idleCamPos = Vector3(0.0f, 20.0f, 100.0f);
	currentCamPos = Vector3(idleCamPos);
	throwCamPos = Vector3(0.0f, 20.0f, -20.0f);

    //set the camera and perspective
    m_pShotCamera = new Camera();
	m_pShotCamera->setPosition(idleCamPos.getX(), idleCamPos.getY(), idleCamPos.getZ());
    m_pShotCamera->setTarget(0.0f, 0.0f, 0.0f);
    m_pShotCamera->Update();

	//set the camera and perspective
	m_pFishCamera = new Camera();
	m_pFishCamera->setPosition(idleCamPos.getX(), idleCamPos.getY(), idleCamPos.getZ());
	m_pFishCamera->setTarget(0.0f, 0.0f, 0.0f);
	m_pFishCamera->Update();

    //create a directional light
    D3DXVECTOR3 pos(0.0f,100.0f,0.0f);
    D3DXVECTOR3 dir(0.0f,-1.0f,10.0f);
	m_pStageLight = new Light(0, D3DLIGHT_DIRECTIONAL, pos, dir, 100);
    m_pStageLight->setColor(D3DXCOLOR(1,1,1,1));

	GamePhysics::getInstance().SetCamera(m_pShotCamera);
	
	GameObject *plane = GamePhysics::getInstance().CreateGameObject(new btBoxShape(btVector3(1,20,200)), 0, btVector3(0.2f, 0.6f, 0.6f), btVector3(0.0f, 0.0f, 100.0f));
	plane->GetRigidBody()->setFriction(0.5f);

	GamePhysics::getInstance().UpdateCamera();

	m_numPlayers = 2;
	m_numRounds = 3;
	m_numThrows = 1;
	for (int i = m_numPlayers; i > 0; i--)
	{
		m_players.push_back(new IPlayer("Player " + std::to_string(i)));
	}

	IRoundHandler::getInstance().Init(m_players, m_numRounds, m_numThrows);
}

void PlayState::Pause()
{
	
}

void PlayState::Resume()
{
	
}

void PlayState::Terminate() {}

void PlayState::HandleKeyDown(int key)
{
	//if (key == DIK_A)
		//physInst->

	if (key == DIK_D)
		vel = D3DXVECTOR3(-1.0, 0.0, 0.0);

	if (key == DIK_Q)
		cameraVec = Vector3(1.0, 0.0, 0.0);

	if (key == DIK_E)
		cameraVec = Vector3(-1.0, 0.0, 0.0);	

	IRoundHandler::getInstance().HandleKeyDown(key);
}

void PlayState::HandleKeyUp(int key)
{
	if (key == DIK_SPACE)
		GameInst::Instance()->PushState(PauseState::Instance());

	if (key == DIK_Z)
		SwitchCamera();

	IRoundHandler::getInstance().HandleKeyUp(key);
}

void PlayState::HandleMouseClick(int button, int x, int y)
{

}

void PlayState::OnMouseDown(int button, int x, int y)
{
	IRoundHandler::getInstance().OnMouseDown(button, x, y);
}

void PlayState::OnMouseUp(int button, int x, int y)
{
	
}

void PlayState::MousePassiveMove(int x, int y)
{
}

void PlayState::HandleMouseMove(int x, int y)
{
	GamePhysics::getInstance().Motion(x, y);
}

void PlayState::Update(float deltaTime)
{
	IRoundHandler::getInstance().Update(deltaTime);
	GamePhysics::getInstance().PhysicsUpdate(deltaTime);
	GUIManager::getInstance()->Update(deltaTime);
}

void PlayState::SwitchCamera()
{
	if (GamePhysics::getInstance().GetCamera() == m_pFishCamera)
	{
		GamePhysics::getInstance().SetCamera(m_pShotCamera);
	}
	else
	{
		GamePhysics::getInstance().SetCamera(m_pFishCamera);
	}
}

void PlayState::Render3D()
{
	if (m_pStageLight)
	{
		//light->setPosition(light->getPosition().x + lightVec.getX(), light->getPosition().y + lightVec.getY(), light->getPosition().z + lightVec.getZ());
		m_pStageLight->Update();
	}

	if (m_pShotCamera)
	{
		m_pShotCamera->setPosition(currentCamPos.getX(), currentCamPos.getY(), currentCamPos.getZ());
		m_pShotCamera->setTarget(0.0f, 0.0f, 0.0f);
		m_pShotCamera->Update();
		cameraVec = Vector3(0.0, 0.0, 0.0);
	}

	if (m_pFishCamera)
	{
		//btVector3 p = fish->GetRigidBody()->getWorldTransform().getOrigin();

		//m_pFishCamera->setPosition(p.getX(), p.getY(), p.getZ());
		//m_pFishCamera->setTarget(p.getX(), p.getY(), p.getZ());
		//m_pFishCamera->Update();
	}
}

void PlayState::Render2D()
{
	GUIManager::getInstance()->Draw();
}

void PlayState::RenderDebug()
{
	GamePhysics::getInstance().DebugRender();
}

void PlayState::Clean()
{

}

void PlayState::End()
{
	for (auto p = m_players.begin(); p != m_players.end(); p++)
	{
		delete (*p);
		(*p) = nullptr;
	}
	m_players.clear();

	GamePhysics::getInstance().End();
	IRoundHandler::getInstance().End();

    delete m_pShotCamera;
	delete m_pFishCamera;

	delete m_pFishLight;
    delete m_pStageLight;
}