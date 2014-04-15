#include "IRoundHandler.h"
#include "EndState.h"
#include "GUIManager.h"

void IRoundHandler::Init(std::vector<IPlayer*> plrs, int rounds, int throws) 
{
	m_numRounds = rounds;
	m_numThrows = throws;
	m_players = plrs;

	m_curRound = 1;
	m_curThrow = 1;

	for (int i = 0; i < m_numRounds; i++)
	{
		m_rounds.push_back(IRound(plrs, m_numThrows));
	}

	if (!m_rounds.empty())
	{
		m_rounds.back().Init();
	}

	m_roundText = new GUIText("ROUND: ", 1,
		1, GUITextAlignment::LEFT);

	m_throwText = new GUIText("THROW: ", 1,
		30, GUITextAlignment::LEFT);

	GUIManager::getInstance()->AddComponent(m_roundText, 0);
	GUIManager::getInstance()->AddComponent(m_throwText, 0);
}

void IRoundHandler::End()
{
	m_curRound = 1;
	m_curThrow = 1;

	m_rounds.clear();

	GUIManager::getInstance()->DeleteComponent(m_roundText);
	GUIManager::getInstance()->DeleteComponent(m_throwText);
}

void IRoundHandler::HandleKeyUp(int key)
{
	if (!m_rounds.empty())
	{
		m_rounds.back().HandleKeyUp(key);
	}
}

void IRoundHandler::HandleKeyDown(int key)
{
	if (!m_rounds.empty())
	{
		m_rounds.back().HandleKeyDown(key);
	}
}

void IRoundHandler::OnMouseDown(int button, int x, int y)
{
	if (!m_rounds.empty())
	{
		m_rounds.back().OnMouseDown(button, x, y);
	}
}

void IRoundHandler::Update(float deltaTime)
{
	if (!m_rounds.empty())
	{
		m_rounds.back().Update(deltaTime);
	}

	m_roundText->setText("ROUND: " + std::to_string(m_curRound));
	m_throwText->setText("THROW: " + std::to_string(m_curThrow));
}

void IRoundHandler::PostUpdate(float deltaTime)
{
	if (!m_rounds.empty())
	{
		m_rounds.back().PostUpdate(deltaTime);
	}
}

void IRoundHandler::NextRound()
{
	if (m_rounds.size() > 1)
	{
		m_curRound++;
		m_curThrow = 1;
		m_rounds.pop_back();
		m_rounds.back().Init();
	}
	else
	{
		GameInst::Instance()->ChangeState(EndState::Instance());
	}
}

void IRoundHandler::NextThrow()
{
	if (!m_rounds.empty())
	{
		m_curThrow++;
		m_rounds.back().NextThrow();
	}
}

IRound& IRoundHandler::GetCurrentRound()
{
	return m_rounds.back();
}