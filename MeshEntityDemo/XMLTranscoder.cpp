#include "XMLTranscoder.h"
#include <stdio.h>

XMLTranscoder::XMLTranscoder()
{
	m_rects = std::map<std::string, RECT>();
	m_animRects = std::map<std::string, std::vector<RECT>>();
}

XMLTranscoder::~XMLTranscoder()
{
	m_rects.clear();
	m_animRects.clear();
}

XMLTranscoder::XMLTranscoder(const XMLTranscoder& copy)
{
	this->m_rects = copy.m_rects;
}

XMLTranscoder& XMLTranscoder::operator=(const XMLTranscoder& other)
{
	this->m_rects = other.m_rects;
	this->m_animRects = other.m_animRects;

	this->m_Width = other.m_Width;
	this->m_Height = other.m_Height;

	return *this;
}

void XMLTranscoder::Transcode(const char* fileName)
{
	//Load an XML file
	tinyxml2::XMLDocument doc;
	doc.LoadFile(fileName);

	//Root element
	tinyxml2::XMLElement* root = doc.RootElement();

	m_Width = atoi(root->Attribute("w"));
	m_Height = atoi(root->Attribute("h"));

	tinyxml2::XMLElement* definitions = root->FirstChildElement();

	tinyxml2::XMLElement* dir = definitions->FirstChildElement();

	for (tinyxml2::XMLElement* anim = dir->FirstChildElement();
		anim != NULL; anim = anim->NextSiblingElement())
	{
		std::vector<RECT> animation = std::vector<RECT>();
		std::string key = anim->Attribute("name");

		if (anim->FirstChildElement() == nullptr)
		{
			//Attibutes: name, x, y, w, h
			int x = atoi(anim->Attribute("x"));
			int y = atoi(anim->Attribute("y"));
			int w = atoi(anim->Attribute("w"));
			int h = atoi(anim->Attribute("h"));

			RECT frame = {x, y, x+w, y+h};

			AddRect(key, frame);
		}
		else
		{
			for (tinyxml2::XMLElement* animFrame = anim->FirstChildElement();
				animFrame != NULL; animFrame = animFrame->NextSiblingElement())
			{
				//Attibutes: name, x, y, w, h
				int x = atoi(animFrame->Attribute("x"));
				int y = atoi(animFrame->Attribute("y"));
				int w = atoi(animFrame->Attribute("w"));
				int h = atoi(animFrame->Attribute("h"));

				RECT frame = {x, y, x+w, y+h};
				animation.push_back(frame);
			}

			AddAnimRects(key, animation);
		}
	}

	//Dump loaded XML data
	doc.Clear();
}

void XMLTranscoder::AddRect(std::string key, RECT rect)
{
	m_rects[key] = rect;
}

RECT XMLTranscoder::GetRect(std::string key)
{
	return m_rects[key];
}

void XMLTranscoder::AddAnimRects(std::string key, std::vector<RECT> rects)
{
	m_animRects[key] = rects;
}

std::vector<RECT> XMLTranscoder::GetAnimRects(std::string key)
{
	return m_animRects[key];
}