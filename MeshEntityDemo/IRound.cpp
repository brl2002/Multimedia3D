#include "IRound.h"

IRound::IRound(std::vector<IPlayer*> plrs, int throws) :
	m_numThrows(throws)
{
	m_players = plrs;

	for (int i = 0; i < m_numThrows; i++)
	{
		for (auto p = m_players.begin(); p != m_players.end(); p++)
		{
			m_pThrows.push_back(IThrow(*p));
		}
	}
}

IRound::~IRound()
{
	m_pThrows.clear();
}

void IRound::Init()
{
	if (!m_pThrows.empty())
	{
		m_pThrows.back().Init();
	}
}

void IRound::HandleKeyUp(int key)
{
	if (!m_pThrows.empty())
	{
		m_pThrows.back().HandleKeyUp(key);
	}
}

void IRound::HandleKeyDown(int key)
{
 	if (!m_pThrows.empty())
	{
		m_pThrows.back().HandleKeyDown(key);
	}
}

void IRound::OnMouseDown(int button, int x, int y)
{
	if (!m_pThrows.empty())
	{
		m_pThrows.back().OnMouseDown(button, x, y);
	}
}

void IRound::Update(float deltaTime)
{
	if (!m_pThrows.empty())
	{
		m_pThrows.back().Update(deltaTime);
	}
}

void IRound::PostUpdate(float deltaTime)
{
	if (!m_pThrows.empty())
	{
		m_pThrows.back().PostUpdate(deltaTime);
	}
}

void IRound::NextThrow()
{
	if (m_pThrows.size() > 1)
	{
		m_pThrows.pop_back();
		m_pThrows.back().Init();
	}
	else
	{
		IRoundHandler::getInstance().NextRound();
	}
}

IThrow& IRound::GetCurrentThrow()
{
	return m_pThrows.back();
}