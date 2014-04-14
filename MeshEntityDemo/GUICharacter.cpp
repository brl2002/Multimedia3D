#include "GUICharacter.h"
#include "GUIManager.h"
#include "Game.h"

GUICharacter::GUICharacter(char ch)
{
	m_image->loadImage(GUIManager::getSpriteSheet());
	m_image->setX(Game::SCREEN_WIDTH / 2);
	m_image->setY(Game::SCREEN_HEIGHT / 2);
	m_image->setPortionRect(GUIManager::getCharacter(ch));
}

void GUICharacter::draw()
{
	m_image->draw();
}