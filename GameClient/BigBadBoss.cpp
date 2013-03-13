#include "BigBadBoss.h"
#include "RangedAttack.h"
#include "StunningStrike.h"

BigBadBoss::BigBadBoss(FLOAT3 _pos, Path _path) : Enemy(_pos, _path, EnemyType::BOSS)
{
	m_modelId = 80;

	this->increaseStrength(10);
	this->increaseAgility(5);
	this->increaseWits(8);    
	this->increaseFortitude(12);

	m_lowResource = 2000;
	m_highRescource = 3000;
	

	/*m_health = 100*m_fortitude; 
	m_physicalDamage = m_strength*5;
	m_mentalDamage = m_wits*5;
	m_baseMovementSpeed = 2.0 + m_agility*0.1f;
	m_movementSpeed = m_baseMovementSpeed;
	m_baseAttackSpeed = 2.0 - m_agility* 0.05f;
	m_attackSpeed = m_baseAttackSpeed;

	m_basePhysicalResistance = 1.00f - m_strength*2*0.01f;
	m_physicalResistance = m_basePhysicalResistance ; 

	m_baseMentalResistance = 1.00f - m_fortitude*2*0.01f;
	m_mentalResistance = m_baseMentalResistance;*/

	m_skills.push_back(new StunningStrike());
	m_regularAttack = new RangedAttack();
	m_regularAttack->setRange(m_regularAttack->getRange()*1.5);
	m_aggroRange = m_regularAttack->getRange() *2.0f;
	

	Model *m = g_graphicsEngine->createModel("Imp", m_position);
	this->m_obb = new BoundingOrientedBox(*m->getObb());
	g_graphicsEngine->removeModel(m);
}


BigBadBoss::~BigBadBoss(void)
{
}
