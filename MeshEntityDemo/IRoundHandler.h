#ifndef I_ROUND_HANDLER
#define I_ROUND_HANDLER

#include "IPlayer.h"
#include "IRound.h"
#include "GameObject.h"
#include "GamePhysics.h"
#include "GUIText.h"
#include <vector>

class IRound;

class IRoundHandler
{
public:
	void Init(std::vector<IPlayer*> plrs, int rounds, int throws);
	void End();

	static IRoundHandler& getInstance()
	{
		static IRoundHandler instance;
		return instance;
	}

	void Update(float deltaTime);
	void PostUpdate(float deltaTime);
	void OnMouseDown(int button, int x, int y);
	void HandleKeyUp(int key);
	void HandleKeyDown(int key);
	void NextRound();
	void NextThrow();

	IRound& GetCurrentRound();

private:
	IRoundHandler() {}
	
	int m_curRound, m_curThrow;

	int m_numRounds, m_numThrows;
	std::vector<IRound> m_rounds;

	std::vector<IPlayer*> m_players;
	GUIText* m_roundText;
	GUIText* m_throwText;
};

#endif