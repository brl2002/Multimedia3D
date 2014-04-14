#ifndef I_THROW_H
#define I_THROW_H

#include "IRound.h"
#include "GamePhysics.h"
#include "GUIText.h"

class IThrow
{
public:
	IThrow(IPlayer* plr);
	~IThrow();

	void Init();
	void Update(float deltaTime);
	void OnMouseDown(int button, int x, int y);
	void HandleKeyUp(int key);
	void HandleKeyDown(int key);
	void End();

private:
	bool m_throwing;

	void SetFishPosition(float x, float y, float z, float dt);

	GameObject* m_pFish;

	IPlayer* m_player;
	GUIText* m_playerText;
};

#endif