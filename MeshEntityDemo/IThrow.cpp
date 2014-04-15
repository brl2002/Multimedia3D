#include "IThrow.h"
#include "GUIText.h"
#include "Game.h"
#include "GUIManager.h"

IThrow::IThrow(IPlayer* plr)
{
	m_player = plr;
	m_throwing = false;
	m_NextThrow = false;
	m_HasBeenThrown = false;
	updateCount = 3;
}

IThrow::~IThrow()
{
	//GamePhysics::getInstance().DestroyGameObject(m_pFish->GetRigidBody());
	//delete m_pFish;
}

void IThrow::Init()
{
	m_pFish = GamePhysics::getInstance().CreateGameObject(FISH, new btBoxShape(btVector3(1,5,1)), 0.5f, btVector3(1.0f, 1.0f, 1.0f), btVector3(0.0f, 50.0f, 0.0f));
	m_pFish->GetRigidBody()->setFriction(0.1f);
	m_pFish->LoadMesh("fish.x");
	m_pFish->RequiresContactTest();

	m_FishPos = m_pFish->GetRigidBody()->getWorldTransform().getOrigin();
	m_LastFishPos = m_FishPos;

	m_playerText = new GUIText(m_player->getName(), Game::SCREEN_WIDTH - 20,
		Game::SCREEN_HEIGHT - 30, GUITextAlignment::RIGHT);
	m_playerText->setScale(.5f);

	GUIManager::getInstance()->AddComponent(m_playerText, 0);
}

void IThrow::HandleKeyUp(int key)
{
	m_NextThrow = false;

	if (key == DIK_B)
	{
		//m_throwing = true;
		//m_NextThrow = true;
	}
}

void IThrow::HandleKeyDown(int key)
{
	
}

void IThrow::OnMouseDown(int button, int x, int y)
{
	if (!m_throwing)
	{
		m_pFish->GetRigidBody()->activate(true);
		m_HasBeenThrown = true;
		GamePhysics::getInstance().ShootObject(m_pFish->GetRigidBody(), 15.0f, x, y);
		//physInst->SetCamera(m_pFishCamera);
		m_throwing = true;
	}
}

void IThrow::Update(float deltaTime)
{
	if (!m_throwing)
	{
		SetFishPosition(0.0f, 10.0f, -40.0f, deltaTime);
	}

	if (m_HasBeenThrown)
	{
		m_FishPos = m_pFish->GetRigidBody()->getWorldTransform().getOrigin();

		if (m_FishPos.getY() < -10.0f)
		{
			m_NextThrow = true;
		}

		if (m_FishPos == m_LastFishPos)
		{
			updateCount--;

			if (updateCount == 0)
			{
				m_NextThrow = true;
			}
		}

		m_LastFishPos = m_FishPos;
	}
}

//Called after physics update
void IThrow::PostUpdate(float deltaTime)
{
	if (m_NextThrow)
	{
		End();
		IRoundHandler::getInstance().NextThrow();
	}
}

void IThrow::SetFishPosition(float x, float y, float z, float dt)
{
	btTransform t = m_pFish->GetRigidBody()->getWorldTransform();
	btVector3 v = btVector3(x, y, z);
	t.setOrigin(v);
	m_pFish->GetRigidBody()->updateDeactivation(dt);
	m_pFish->GetRigidBody()->setWorldTransform(t);
}

btVector3 IThrow::GetFishPosition()
{
	return m_pFish->GetRigidBody()->getWorldTransform().getOrigin();
}

void IThrow::End()
{
	if (m_pFish->IsCollidingWithTrigger())
	{
		m_player->addScore(5);
	}

	GamePhysics::getInstance().DestroyGameObject(m_pFish);
	GUIManager::getInstance()->DeleteComponent(m_playerText);
}