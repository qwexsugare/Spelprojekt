#include "Doctor.h"

Doctor::Doctor(int _playerId) : Hero(Hero::DOCTOR, _playerId)
{
	m_modelId = 98;
	this->increaseStrength(1);
	this->increaseAgility(3);
	this->increaseWits(5);
	this->increaseFortitude(3);
	
	this->m_skills.push_back(new SimonsEvil());
	this->m_messageQueue->pushOutgoingMessage(new SkillBoughtMessage(Skill::SIMONS_EVIL, _playerId, 0));
	this->m_skills.push_back(new SwiftAsACatPowerfulAsABoar());
	this->m_messageQueue->pushOutgoingMessage(new SkillBoughtMessage(Skill::SWIFT_AS_A_CAT_POWERFUL_AS_A_BEAR, _playerId, 0));
}

Doctor::~Doctor()
{

}
