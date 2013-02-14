#include "RedKnight.h"

RedKnight::RedKnight(int _playerId) : Hero(Hero::RED_KNIGHT, _playerId)
{
	m_modelId = 96;
	this->increaseStrength(5);
	this->increaseAgility(2);
	this->increaseWits(1);
	this->increaseFortitude(4);
	
	this->m_skills.push_back(new SimonsEvil());
	this->m_messageQueue->pushOutgoingMessage(new SkillBoughtMessage(Skill::SIMONS_EVIL, _playerId, 0));
	this->m_skills.push_back(new SwiftAsACatPowerfulAsABoar());
	this->m_messageQueue->pushOutgoingMessage(new SkillBoughtMessage(Skill::SWIFT_AS_A_CAT_POWERFUL_AS_A_BEAR, _playerId, 0));
}

RedKnight::~RedKnight()
{

}
