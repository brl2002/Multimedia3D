#ifndef PLAY_STATE_H
#define PLAY_STATE_H

#include "GameObject.h"
#include "GameState.h"
#include <vector>

#include "..\Engine\Advanced2D.h"
#include "GamePhysics.h"
#include "IRoundHandler.h"
#include "GUIText.h"

using namespace Advanced2D;

#define MAX 10

class PlayState : public GameState
{
public:
	void Init();
	void Clean();
	void Terminate();

	void Pause();
	void Resume();

	void HandleKeyUp(int key);
	void HandleKeyDown(int key);
	void HandleMouseClick(int button, int x, int y);
	void OnMouseDown(int button, int x, int y);
	void OnMouseUp(int button, int x, int y);
	void MousePassiveMove(int x, int y);
	void HandleMouseMove(int x, int y);
	void End();

	void Update(float deltaTime);
	void Render3D();
	void Render2D();

	void RenderDebug();
	void SwitchCamera();

	// Implement Singleton Pattern
	static PlayState* Instance()
	{
		return &m_PlayState;
	}

protected:
	PlayState() {}

private:
	static PlayState m_PlayState;

	bool mouseDown1;
	bool m_throw;

	Vector3 throwCamPos;
	Vector3 idleCamPos;
	Vector3 currentCamPos;

	//camera object
	Camera* m_pShotCamera;
	Camera* m_pFishCamera;

	Light *m_pStageLight;
	Light *m_pFishLight;

	D3DXVECTOR3 vel;

	Vector3 lightVec;
	Vector3 cameraVec;

	int m_numPlayers;
	int m_numRounds, m_numThrows;
	std::vector<IPlayer*> m_players;

	GUIText* m_player;

	Sample *sample;
};

#endif