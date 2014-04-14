#include "GUISprite.h"

GUISprite::GUISprite()
{
	m_image = new Advanced2D::Sprite();
}

GUISprite::~GUISprite()
{
	delete m_image;
	m_image = nullptr;
}