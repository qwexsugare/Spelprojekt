#include "RedKnight.h"

RedKnight::RedKnight(int _playerId, WEAPON_TYPE _weaponType) : Hero(Hero::RED_KNIGHT, _playerId)
{
	m_modelId = 96;
	this->increaseStrength(5);
	this->increaseAgility(2);
	this->increaseWits(1);
	this->increaseFortitude(4);
	m_turretConstruction = 1;
	
	this->m_skills.push_back(new CourageHonorValor());
	this->m_skills.push_back(new SwiftAsACatPowerfulAsABoar());

	switch(_weaponType)
	{
	case WEAPON_TYPE::MELEE:
		this->m_regularAttack = new MeleeAttack();
		this->m_weaponType = WEAPON_TYPE::MELEE;
		break;

	case WEAPON_TYPE::RANGED:
		this->m_regularAttack = new MeleeAOEAttack();
		this->m_weaponType = WEAPON_TYPE::AOE;
		break;
	}
}

RedKnight::~RedKnight()
{

}

int RedKnight::getSubType()const
{
	return Hero::HERO_TYPE::RED_KNIGHT;
}