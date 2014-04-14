#include "GUIText.h"

GUIText::GUIText(std::string str, double x, double y, GUITextAlignment align)
{
	m_x = x;
	m_y = y;
	m_align = align;

	setText(str);
}

GUIText::~GUIText()
{
	for (std::vector<GUICharacter*>::iterator ch = m_chars.begin(); ch != m_chars.end(); ++ch)
	{
		delete (*ch);
	}
	m_chars.clear();
}

void GUIText::setPosition(double x, double y)
{
	m_x = x;
	m_y = y;
	alignText();
}

void GUIText::setScale(double x)
{
	for (std::vector<GUICharacter*>::iterator ch = m_chars.begin(); ch != m_chars.end(); ++ch)
	{
		//(*ch)->setScale(x);
	}
}

void GUIText::setAlignment(GUITextAlignment align)
{
	m_align = align;
	alignText();
}

void GUIText::alignText()
{
	switch (m_align)
	{
		case LEFT:
			leftAlign();
			break;
		case RIGHT:
			rightAlign();
			break;
	}
}

void GUIText::leftAlign()
{
	double xPos = m_x + m_chars.front()->getWidth() / 2;
	for (std::vector<GUICharacter*>::iterator ch = m_chars.begin(); ch != m_chars.end(); ++ch)
	{
		if ((*ch) == nullptr) 
		{
			xPos += SPACE;
		}
		else
		{
			(*ch)->setX(xPos);
			(*ch)->setY(m_y);

			xPos += (*ch)->getWidth() + BUFFER_SPACE;
		}
	}
	m_height = m_chars.front()->getHeight();
	m_width = xPos;
}

void GUIText::rightAlign()
{
	double xPos = m_x - m_chars.front()->getWidth() / 2;;
	for (std::vector<GUICharacter*>::reverse_iterator ch = m_chars.rbegin(); ch != m_chars.rend(); ++ch)
	{
		if ((*ch) == nullptr) 
		{
			xPos -= SPACE;
		}
		else
		{
			(*ch)->setX(xPos);
			(*ch)->setY(m_y);

			xPos -= (*ch)->getWidth() + BUFFER_SPACE;
		}
	}
	m_height = m_chars.front()->getHeight();
	m_width = xPos;
}

void GUIText::setText(std::string str)
{
	if (str != m_str)
	{
		if (!m_chars.empty())
		{
			for (std::vector<GUICharacter*>::iterator ch = m_chars.begin(); ch != m_chars.end(); ++ch)
			{
				delete (*ch);
			}
			m_chars.clear();
		}

		m_str = str;
		for (std::string::iterator c = str.begin(); c != str.end(); ++c) 
		{

			GUICharacter* ch;
			if (isspace(*c))
			{
				ch = nullptr;
			}
			else
			{
				ch = new GUICharacter(towlower(*c));
			}
			m_chars.push_back(ch);
		}

		alignText();
	}
}

void GUIText::draw()
{
	for (std::vector<GUICharacter*>::iterator ch = m_chars.begin(); ch != m_chars.end(); ++ch)
	{
		if ((*ch) != nullptr)
			(*ch)->draw();
	}
}