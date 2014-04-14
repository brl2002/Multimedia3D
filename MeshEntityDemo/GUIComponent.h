#ifndef GUICOMPONENT_H
#define GUICOMPONENT_H

#include "GUISprite.h"

class GUIComponent
{
public:
	virtual void update(DWORD deltaTime) {};
	virtual void draw() {};
};

#endif