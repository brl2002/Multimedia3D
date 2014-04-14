#ifndef GUI_CHARACTER
#define GUI_CHARACTER

#include "GUIComponent.h"

class GUICharacter : public GUISprite
{
public:
	GUICharacter(char ch);

	void draw();
private:

};

#endif