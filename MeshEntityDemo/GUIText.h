#ifndef GUI_TEXT
#define GUI_TEXT

#include "GUICharacter.h"
#include <string>
#include <vector>

enum GUITextAlignment
{
	LEFT,
	RIGHT
};

class GUIText : public GUIComponent
{
public:
	GUIText(std::string str, double x, double y, GUITextAlignment align);
	~GUIText();

	double getX() { return m_x; }
	double getY() { return m_y; }

	void setPosition(double x, double y);
	void setScale(double x);

	int getWidth() { return m_width; }
	int getHeight() { return m_height; }

	GUITextAlignment getAlignment() { return m_align; }
	void setAlignment(GUITextAlignment align);

	void setText(std::string str);

	void draw();

private:
	void alignText();
	void leftAlign();
	void rightAlign();

	std::vector<GUICharacter*> m_chars;
	std::string m_str;

	double m_x, m_y;
	int m_width, m_height;
	GUITextAlignment m_align;

	static const int BUFFER_SPACE = 2;
	static const int SPACE = 20;
};

#endif