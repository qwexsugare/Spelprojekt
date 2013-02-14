#include "Officer.h"

Officer::Officer(int _playerId) : Hero(Hero::OFFICER, _playerId)
{
	m_modelId = 95;
	this->increaseStrength(3);
	this->increaseAgility(5);
	this->increaseWits(1);
	this->increaseFortitude(3);
	
	this->m_skills.push_back(new SimonsEvil());
	this->m_messageQueue->pushOutgoingMessage(new SkillBoughtMessage(Skill::SIMONS_EVIL, _playerId, 0));
	this->m_skills.push_back(new SwiftAsACatPowerfulAsABoar());
	this->m_messageQueue->pushOutgoingMessage(new SkillBoughtMessage(Skill::SWIFT_AS_A_CAT_POWERFUL_AS_A_BEAR, _playerId, 0));
}

Officer::~Officer()
{

}
