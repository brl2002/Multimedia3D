#ifndef GUIMANAGER_H
#define GUIMANAGER_H

#include "GUIComponent.h"
#include "XMLTranscoder.h"
#include <vector>

class GUIManager
{
public:
	~GUIManager();
	
	static GUIManager *getInstance()
	{
		static GUIManager instance;
		return &instance;
	}

	void Init();
	
	void Update(DWORD deltaTime);
	void Draw();

	void Terminate();

	void AddComponent(GUIComponent* component, int layer = -1);
	void DeleteComponent(GUIComponent* component);

	static std::string getSpriteSheet() { return FONT_SPRITESHEET; };
	static RECT getCharacter(char ch);

private:
	GUIManager();

	std::vector<GUIComponent*> m_components;
	
	static XMLTranscoder m_fontXML;
	static const std::string FONT_SPRITESHEET;
};

#endif