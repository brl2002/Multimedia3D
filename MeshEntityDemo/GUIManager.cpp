#include "GUIManager.h"
#include <string>

const std::string GUIManager::FONT_SPRITESHEET = "../res/font2.png";
XMLTranscoder GUIManager::m_fontXML;

RECT GUIManager::getCharacter(char ch)
{
	std::string s(1, (ch));
	return m_fontXML.GetRect(s);
}

void GUIManager::Init()
{
	m_fontXML.Transcode("../res/font2.sprites");
	m_components = std::vector<GUIComponent*>();
}

GUIManager::~GUIManager()
{
	
}

GUIManager::GUIManager()
{

}

void GUIManager::Draw()
{
	//Draw GUIComponents in the order of layer, very last layer would be drawn first and first layer drawn last
	for (std::vector<GUIComponent*>::iterator c = m_components.begin() ; c != m_components.end(); ++c)
	{
		(*c)->draw();
	}
}

void GUIManager::Update(DWORD deltaTime)
{
	//Update all GUIComponents
	//Draw GUIComponents in the order of layer, very last layer would be drawn first and first layer drawn last
	for (std::vector<GUIComponent*>::iterator c = m_components.begin() ; c != m_components.end(); ++c)
	{
		(*c)->update(deltaTime);
	}
}

void GUIManager::AddComponent(GUIComponent* component, int layer)
{
	//Add GUIComponent to a specific layer provided in the parameter, layer less than 0 would mean
	//the GUIComponent would be added to the back of our vector array.

	if (layer >= 0)
	{
		m_components.insert(m_components.begin()+layer, component);
	}
}

void GUIManager::DeleteComponent(GUIComponent* component)
{
	//Add GUIComponent to a specific layer provided in the parameter, layer less than 0 would mean
	//the GUIComponent would be added to the back of our vector array.
	for (auto iter = m_components.begin(); iter != m_components.end(); ++iter)
	{
		if ((*iter) == component)
		{
			// erase the object from the list
			m_components.erase(iter);
			// delete the object from memory
			delete component;
			// done
			return;
		}
	}
}

void GUIManager::Terminate()
{
	for (std::vector<GUIComponent*>::iterator c = m_components.begin() ; c != m_components.end(); ++c)
	{
		delete (*c);
	}
	m_components.clear();
}