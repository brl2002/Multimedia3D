#ifndef I_THROW_H
#define I_THROW_H

#include "IRound.h"
#include "GamePhysics.h"
#include "GUIText.h"
#include "PlayState.h"

using namespace Advanced2D;

class IThrow
{
public:
	IThrow(IPlayer* plr);
	~IThrow();

	void Init();
	void Update(float deltaTime);
	void PostUpdate(float deltaTime);
	void OnMouseDown(int button, int x, int y);
	void HandleKeyUp(int key);
	void HandleKeyDown(int key);
	void End();
	void DeleteFish();

	btVector3 GetFishPosition();

private:
	bool m_throwing;

	void SetFishPosition(float x, float y, float z, float dt);

	GameObject* m_pFish;

	IPlayer* m_player;
	GUIText* m_playerText;

	bool m_NextThrow;
	bool m_HasBeenThrown;

	int updateCount;

	btVector3 m_FishPos;
	btVector3 m_LastFishPos;

	double m_friction;
	double m_xPos, m_xCap;

	Sample* m_pThrowSample;
};

#endif