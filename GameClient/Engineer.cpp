#include "Engineer.h"

Engineer::Engineer(int _playerId, WEAPON_TYPE _weaponType) : Hero(Hero::ENGINEER, _playerId)
{
	m_modelId = 97;
	this->increaseStrength(3);
	this->increaseAgility(3);
	this->increaseWits(5);
	this->increaseFortitude(1);

	this->m_skills.push_back(new EnhancedDevelopment());

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

Engineer::~Engineer()
{

}
