#include "TheMentalist.h"

TheMentalist::TheMentalist(int _playerId, WEAPON_TYPE _weaponType) : Hero(Hero::THE_MENTALIST, _playerId)
{
	m_modelId = 99;
	this->increaseStrength(1);
	this->increaseAgility(4);
	this->increaseWits(5);
	this->increaseFortitude(2);
	
	m_skills.push_back(new EnigmaticPresence());
	m_skills.push_back(new HypnoticStare());

	switch(_weaponType)
	{
	case WEAPON_TYPE::MELEE:
		this->m_regularAttack = new MeleeAttack();
		this->m_weaponType = WEAPON_TYPE::MELEE;
		break;

	case WEAPON_TYPE::RANGED:
		this->m_regularAttack = new RangedAttack();
		this->m_weaponType = WEAPON_TYPE::RANGED;
		break;
	}
}

TheMentalist::~TheMentalist()
{

}