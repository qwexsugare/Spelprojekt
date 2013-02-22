#include "SoulEaterSteed.h"
#include "LifestealingStrike.h"
#include "MeleeAttack.h"


SoulEaterSteed::SoulEaterSteed(FLOAT3 _pos, Path _path) : Enemy(_pos, _path)
{
	m_modelId        = 84;
				     
	m_strength       = 6;
	m_agility        = 1;
	m_wits           = 0;
	m_fortitude      = 3;
				     
	m_lowResource    = 60;
	m_highRescource  = 70;
	

	m_health = 100*m_fortitude; 
	m_physicalDamage = m_strength*5;
	m_mentalDamage = m_wits*5;
	m_baseMovementSpeed = 2.0 + m_agility*0.1f;
	m_movementSpeed = m_baseMovementSpeed;
	m_baseAttackSpeed = 2.0 - m_agility* 0.05f;
	m_attackSpeed = m_baseAttackSpeed;

	m_basePhysicalResistance = m_strength*2;
	m_physicalResistance = m_basePhysicalResistance ; 

	m_baseMentalResistance = m_fortitude*2;
	m_mentalResistance = m_baseMentalResistance;

	m_skills.push_back(new LifestealingStrike());
	m_regularAttack = new MeleeAttack();
	m_aggroRange = m_regularAttack->getRange() *2.0f;
}

void SoulEaterSteed::attackHero(int heroIndex)
{
	this->attack(m_closestTargetId);
	this->m_attackCooldown = m_attackSpeed;

	
}

SoulEaterSteed::~SoulEaterSteed(void)
{
}
