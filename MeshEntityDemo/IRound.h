#ifndef I_ROUND_H
#define I_ROUND_H

#include "IPlayer.h"
#include "IThrow.h"
#include "GameObject.h"
#include "GamePhysics.h"
#include "IRoundHandler.h"
#include <vector>

class IThrow;

class IRound
{
public:
	IRound(std::vector<IPlayer*> plrs, int throws);
	~IRound();

	void Init();
	void Update(float deltaTime);
	void PostUpdate(float deltaTime);
	void OnMouseDown(int button, int x, int y);
	void HandleKeyUp(int key);
	void HandleKeyDown(int key);
	void NextThrow();

	int getNumThrows() { return m_pThrows.size(); }

	IThrow& GetCurrentThrow();

private:
	int m_numThrows;
	std::vector<IThrow> m_pThrows;

	std::vector<IThrow> m_ThrowsToDelete;

	std::vector<IPlayer*> m_players;
};

#endif