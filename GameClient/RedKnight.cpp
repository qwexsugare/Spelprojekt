#include "RedKnight.h"

RedKnight::RedKnight(int _playerId, WEAPON_TYPE _weaponType) : Hero(Hero::RED_KNIGHT, _playerId)
{
	m_modelId = 96;
	this->increaseStrength(30);
	this->increaseAgility(2);
	this->increaseWits(1);
	this->increaseFortitude(4);

	this->m_health += 1000;
	
	this->m_skills.push_back(new SwiftAsACatPowerfulAsABoar());
	this->m_skills.push_back(new CourageHonorValor());

	switch(_weaponType)
	{
	case WEAPON_TYPE::MELEE:
		this->m_regularAttack = new MeleeAttack();
		break;

	case WEAPON_TYPE::RANGED:
		this->m_regularAttack = new MeleeAOEAttack();
		break;
	}
}

RedKnight::~RedKnight()
{

}
