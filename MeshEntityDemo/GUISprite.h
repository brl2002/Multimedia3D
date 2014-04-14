#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "..\Engine\Advanced2D.h"

class GUISprite
{
public:
	GUISprite();
	~GUISprite();

	virtual void update(DWORD deltaTime) {};
	virtual void draw() {};

	//screen position
	virtual int getHeight() { return m_image->getHeight(); };
	virtual int getWidth() { return m_image->getWidth(); };

	virtual Advanced2D::Vector3 getPosition() { return m_image->getPosition(); };

	virtual void setPosition(double x, double y) { m_image->setPosition(x, y); };
	virtual void setPosition(Advanced2D::Vector3 position) { m_image->setPosition(position); };

	virtual void setScale(double x) { m_image->setScale(x); }

	virtual double getX() { return m_image->getX(); };
	virtual double getY() { return m_image->getY(); };

	virtual void setX(double x) { m_image->setX(x); };
	virtual void setY(double y) { m_image->setY(y); };

protected:
	Advanced2D::Sprite* m_image;
};

#endif