#ifndef I_PLAYER_H
#define I_PLAYER_H

#include <string>

class IPlayer
{
public:
	IPlayer(std::string name) : m_score(0), m_name(name) {}

	void addScore(int score) { m_score += score; }

	int getScore() { return m_score; }
	std::string getName() { return m_name; }

private:
	std::string m_name;
	int m_score;
};

#endif