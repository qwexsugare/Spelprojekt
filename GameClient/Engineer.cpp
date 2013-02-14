#include "Engineer.h"

Engineer::Engineer(int _playerId) : Hero(Hero::ENGINEER, _playerId)
{
	m_modelId = 97;
	this->increaseStrength(3);
	this->increaseAgility(3);
	this->increaseWits(5);
	this->increaseFortitude(1);
	
	this->m_skills.push_back(new SimonsEvil());
	this->m_messageQueue->pushOutgoingMessage(new SkillBoughtMessage(Skill::SIMONS_EVIL, _playerId, 0));
	this->m_skills.push_back(new SwiftAsACatPowerfulAsABoar());
	this->m_messageQueue->pushOutgoingMessage(new SkillBoughtMessage(Skill::SWIFT_AS_A_CAT_POWERFUL_AS_A_BEAR, _playerId, 0));
}

Engineer::~Engineer()
{

}
