#include "TheMentalist.h"

TheMentalist::TheMentalist(int _playerId) : Hero(Hero::THE_MENTALIST, _playerId)
{
	m_modelId = 99;
	this->increaseStrength(1);
	this->increaseAgility(4);
	this->increaseWits(5);
	this->increaseFortitude(2);

	m_skills.push_back(new EnigmaticPresence());
}

TheMentalist::~TheMentalist()
{

}
