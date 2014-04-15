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

	m_SpawnZ = 175.0f;

	sample = g_engine->audio->Load("trollsong.mp3");
	g_engine->audio->Play(sample);

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
    D3DXVECTOR3 dir(0.0f,1.0f,0.0f);
	m_pStageLight = new Light(0, D3DLIGHT_DIRECTIONAL, pos, dir, 100);
    m_pStageLight->setColor(D3DXCOLOR(1,1,1,1));

	//create a directional light
	D3DXVECTOR3 pos2(0.0f,0.0f,m_SpawnZ);
	D3DXVECTOR3 dir2(-1.0f,0.0f,0.0f);
	//m_pChefLight = new Light(0, D3DLIGHT_SPOT, pos2, dir2, 100);
	//m_pChefLight->setColor(D3DXCOLOR(1,1,1,1));

	GamePhysics::getInstance().SetCamera(m_pShotCamera);
	
	GameObject *plane = GamePhysics::getInstance().CreateGameObject(OTHER, new btBoxShape(btVector3(1,20,160)), 0, btVector3(0.2f, 0.6f, 0.6f), btVector3(0.0f, 0.0f, 100.0f));
	plane->GetRigidBody()->setFriction(0.5f);
	plane->LoadMesh("wood.x");
	plane->SetScale(4.0f, 3.0f, 15.0f);

	m_chef = GamePhysics::getInstance().CreateGameObject(TRIGGER, new btBoxShape(btVector3(1, 1, 1)), 0, btVector3(0.2f, 0.6f, 0.6f), btVector3(-30.0f, 0.0f, m_SpawnZ));
	m_chef->GetRigidBody()->setCollisionFlags(m_chef->GetRigidBody()->getCollisionFlags() | btCollisionObject::CF_NO_CONTACT_RESPONSE);
	m_chef->LoadMesh("chef.x");
	m_chef->SetScale(5.0f, 5.0f, 5.0f);

	m_trigger = GamePhysics::getInstance().CreateGameObject(TRIGGER, new btBoxShape(btVector3(5, 5, 15)), 0, btVector3(0.2f, 0.6f, 0.6f), btVector3(-10.0f, 6.0f, m_SpawnZ));
	m_trigger->GetRigidBody()->setCollisionFlags(m_trigger->GetRigidBody()->getCollisionFlags() | btCollisionObject::CF_NO_CONTACT_RESPONSE);

	GamePhysics::getInstance().UpdateCamera();

	m_numPlayers = 2;
	m_numRounds = 3;
	m_numThrows = 1;
	for (int i = m_numPlayers; i > 0; i--)
	{
		m_players.push_back(new IPlayer("Player " + std::to_string(i)));
	}

	m_PlayerScore1 = new GUIText(m_players[1]->getName() + ": " + std::to_string(m_players[1]->getScore()), 1,
	Game::SCREEN_HEIGHT - 100, GUITextAlignment::LEFT);
	m_PlayerScore1->setScale(.5f);

	m_PlayerScore2 = new GUIText(m_players[0]->getName() + ": " + std::to_string(m_players[0]->getScore()), 1,
	Game::SCREEN_HEIGHT - 50, GUITextAlignment::LEFT);
	m_PlayerScore2->setScale(.5f);

	GUIManager::getInstance()->AddComponent(m_PlayerScore1, 0);
	GUIManager::getInstance()->AddComponent(m_PlayerScore2, 0);

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
	m_PlayerScore1->setText(m_players[1]->getName() + ": " + std::to_string(m_players[1]->getScore()));
	m_PlayerScore2->setText(m_players[0]->getName() + ": " + std::to_string(m_players[0]->getScore()));

	IRoundHandler::getInstance().Update(deltaTime);
	GamePhysics::getInstance().PhysicsUpdate(deltaTime);
	IRoundHandler::getInstance().PostUpdate(deltaTime);
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

	if (m_pChefLight)
	{
		m_pChefLight->Update();
	}

	if (GamePhysics::getInstance().GetCamera() == m_pShotCamera)
	{
		m_pShotCamera->setPosition(currentCamPos.getX(), currentCamPos.getY(), currentCamPos.getZ());
		m_pShotCamera->setTarget(0.0f, 0.0f, 0.0f);
		m_pShotCamera->Update();
	}

	if (GamePhysics::getInstance().GetCamera() == m_pFishCamera)
	{
		btVector3 p = IRoundHandler::getInstance().GetCurrentRound().GetCurrentThrow().GetFishPosition();
		m_pFishCamera->setPosition(p.getX(), p.getY() + 100.0f, -p.getZ());
		m_pFishCamera->setUpDirection(0.0f, 0.0f, -1.0f);
		m_pFishCamera->setTarget(p.getX(), p.getY(), -p.getZ());
		m_pFishCamera->Update();
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

	delete m_pChefLight;
    delete m_pStageLight;
}