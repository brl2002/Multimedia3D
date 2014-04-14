#ifndef XMLTRANSCODER_H
#define XMLTRANSCODER_H

#include "tinyxml2.h"
#include <string>
#include <map>
#include <stdlib.h>
#include <assert.h>
#include <vector>
#include "..\Engine\Advanced2D.h"

using namespace Advanced2D;

class XMLTranscoder
{
public:
	XMLTranscoder();
	~XMLTranscoder();

	XMLTranscoder(const XMLTranscoder& copy);
	XMLTranscoder& operator=(const XMLTranscoder& other);

	void Transcode(const char* fileName);

	std::vector<RECT> GetAnimRects(std::string key);
	RECT GetRect(std::string key);

private:
	std::map<std::string, std::vector<RECT>> m_animRects;
	std::map<std::string, RECT> m_rects;
	int m_Width, m_Height;

private:
	void AddAnimRects(std::string key, std::vector<RECT> rects);
	void AddRect(std::string key, RECT rect);
};

#endif