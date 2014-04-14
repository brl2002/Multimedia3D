/*
  Name: MeshEntityDemo
  Date: 25/02/08
  Description: Demonstrates managed mesh entities
*/

#include "..\Engine\Advanced2D.h"
#include "GamePhysics.h"
#include "GameEngine.h"

#include <Windows.h>

using namespace Advanced2D;

DWORD previousTime = 0;
DWORD currentTime = 0;

bool game_preload() 
{
    g_engine->setAppTitle("MESH ENTITY DEMO");
    g_engine->setFullscreen(false);
    g_engine->setScreenWidth(800);
    g_engine->setScreenHeight(600);
    g_engine->setColorDepth(32);    
    return 1;
}

bool game_init(HWND) 
{
    g_engine->SetAmbient(D3DCOLOR_RGBA(0,0,0,0));

	srand(time(NULL));

	GameInst::Instance()->Init();

    return 1;
}

void game_update(float dt) 
{
	previousTime = currentTime;
	currentTime = timeGetTime();
	float deltaTime = currentTime - previousTime;

	GameInst::Instance()->Update(deltaTime);

	if (deltaTime > 0.15)
	{
		deltaTime = 0.15;
	}

	g_engine->audio->Update();
}

void game_render3d()
{
    g_engine->ClearScene(D3DCOLOR_RGBA(0,0,60,0));
    g_engine->SetIdentity();

	GameInst::Instance()->Render3D();
}

void game_keyRelease(int key) 
{ 
    if (key == DIK_ESCAPE) g_engine->Close();

	GameInst::Instance()->HandleKeyUp(key);
}

void game_keyPress(int key)
{
	GameInst::Instance()->HandleKeyDown(key);
}

void game_entityUpdate(Advanced2D::Entity* entity, float dt) 
{ 

}

void game_entityRender(Advanced2D::Entity* entity) 
{ 

}

void Render_Debug()
{
	GameInst::Instance()->RenderDebug();
}

void game_render2d()
{
	GameInst::Instance()->Render2D();
}

void game_cleanup()
{
	GameInst::Instance()->Clean();
}

void game_end() 
{
    g_engine->audio->StopAll();
	g_engine->audio->Release();

	GameInst::Instance()->End();
}

void game_mouseButton(int button, int x, int y)
{
	GameInst::Instance()->HandleMouseClick(button, x, y);
}

void game_onMouseDown(int button, int x, int y)
{
	GameInst::Instance()->OnMouseDown(button, x, y);
}

void game_onMouseUp(int button, int x, int y)
{
	GameInst::Instance()->OnMouseUp(button, x, y);
}

void game_mouseMove(int x,int y)
{
	GameInst::Instance()->HandleMouseMove(x, y);
}

void game_mousePassiveMove(int x, int y)
{
	GameInst::Instance()->MousePassiveMove(x, y);
}

void game_mouseMotion(int x,int y) { }
void game_mouseWheel(int wheel) { }
void game_controllerButtonPressed(int index, int button){}
void game_controllerButtonReleased(int index, int button){}
void game_controllerButtonDown(int index, int button){}
void game_controllerLeftTrigger(int index, int value){}
void game_controllerRightTrigger(int index, int value){}
void game_controllerThumbLX(int index, float value){}
void game_controllerThumbLY(int index, float value){}
void game_controllerThumbRX(int index, float value) { }
void game_controllerThumbRY(int index, float value) { }