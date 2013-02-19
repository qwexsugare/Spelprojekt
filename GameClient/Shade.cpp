#include "Shade.h"


Shade::Shade(FLOAT3 _pos, Path _path) : Enemy(_pos, _path)
{
	m_modelId = 82;
	
	m_strength = 4;
	m_agility  = 3;
	m_wits = 0;
	m_fortitude = 1;

	m_lowResource = 30;
	m_highRescource = 40;
	

	m_health = 100*m_fortitude; 
	m_physicalDamage = m_strength*5;
	m_mentalDamage = m_wits*5;
	m_baseMovementSpeed = 2.0 + m_agility*0.1f;
	m_movementSpeed = m_baseMovementSpeed;
	m_baseAttackSpeed = 2.0 - m_agility* 0.05f;
	m_attackSpeed = m_baseAttackSpeed;

	m_basePhysicalResistance = 100;// m_strength*2;
	m_physicalResistance = m_basePhysicalResistance ; 

	m_baseMentalResistance = m_fortitude*2;
	m_mentalResistance = m_baseMentalResistance;

	//No obstacle avoidance! 
}

void Shade::attackHero(int heroIndex)
{
	this->dealDamage(EntityHandler::getAllHeroes()[heroIndex], this->getPhysicalDamage(), this->getMentalDamage());
	this->m_attackCooldown = m_attackSpeed;
}


Shade::~Shade(void)
{
}
