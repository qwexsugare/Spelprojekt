#include "FrostDemon.h"
#include "StunningStrike.h"
#include "RangedAttack.h"


FrostDemon::FrostDemon(FLOAT3 _pos, Path _path) : Enemy(_pos, _path)
{
	m_modelId = 80;

	m_strength = 1;
	m_agility  = 3;
	m_wits = 3;
	m_fortitude = 2;

	m_lowResource = 50;
	m_highRescource = 60;
	

	m_health = 100*m_fortitude; 
	m_physicalDamage = m_strength*5;
	m_mentalDamage = m_wits*5;
	m_baseMovementSpeed = 2.0 + m_agility*0.1f;
	m_movementSpeed = m_baseMovementSpeed;
	m_baseAttackSpeed = 2.0 - m_agility* 0.05f;
	m_attackSpeed = m_baseAttackSpeed;

	m_basePhysicalResistance = 1.00f - m_strength*2*0.01f;
	m_physicalResistance = m_basePhysicalResistance ; 

	m_baseMentalResistance = 1.00f - m_fortitude*2*0.01f;
	m_mentalResistance = m_baseMentalResistance;

	m_skills.push_back(new StunningStrike());
	m_regularAttack = new RangedAttack();
	m_aggroRange = m_regularAttack->getRange() *2.0f;

	Model *m = g_graphicsEngine->createModel("Imp", m_position);
	this->m_obb = new BoundingOrientedBox(*m->getObb());
	g_graphicsEngine->removeModel(m);

}

void FrostDemon::attackHero(int heroIndex)
{
	this->attack(m_closestTargetId);
	this->m_attackCooldown = m_attackSpeed;

	m_skills[0]->activate(heroIndex, this->m_id);
}


FrostDemon::~FrostDemon(void)
{
}
