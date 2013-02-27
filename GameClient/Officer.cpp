#include "Officer.h"

Officer::Officer(int _playerId, WEAPON_TYPE _weaponType) : Hero(Hero::OFFICER, _playerId)
{
	m_modelId = 95;
	this->increaseStrength(3);
	this->increaseAgility(5);
	this->increaseWits(1);
	this->increaseFortitude(3);

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

Officer::~Officer()
{

}
