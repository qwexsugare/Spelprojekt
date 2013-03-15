#include "Shade.h"
#include "MeleeAttack.h"


Shade::Shade(FLOAT3 _pos, Path _path) : Enemy(_pos, _path, EnemyType::SHADE)
{
	m_modelId = 82;
	

	m_basePhysicalResistance = 0.02f;
	//m_baseMentalResistance = 1.00f - m_fortitude*2*0.01f;
	m_mentalResistance = m_baseMentalResistance;
	this->increaseStrength(4);
	this->increaseAgility(3);
	this->increaseWits(0);
	this->increaseFortitude(1);


	m_lowResource = 30+20;
	m_highRescource = 40+20;
	
	/*m_health = 100*m_fortitude; 
	m_physicalDamage = m_strength*5;
	m_mentalDamage = m_wits*5;
	m_baseMovementSpeed = 2.0 + m_agility*0.1f;
	m_movementSpeed = m_baseMovementSpeed;
	m_baseAttackSpeed = 2.0 - m_agility* 0.05f;
	m_attackSpeed = m_baseAttackSpeed;
	this->increaseFortitude(2);
	m_basePhysicalResistance = 0.0f;//1.00f -100*0.01f;// m_strength*2;
	m_physicalResistance = m_basePhysicalResistance ; 

	m_baseMentalResistance = 1.00f - m_fortitude*2*0.01f;
	m_mentalResistance = m_baseMentalResistance;*/

	//No obstacle avoidance! 

	m_regularAttack = new MeleeAttack();
	m_aggroRange = 2.0f + m_regularAttack->getRange() *2.0f;

	Model *m = g_graphicsEngine->createModel("Imp", m_position);
	this->m_obb = new BoundingOrientedBox(*m->getObb());
	g_graphicsEngine->removeModel(m);
}

void Shade::attackHero(int heroIndex)
{
	this->attack(m_closestTargetId);
	this->m_attackCooldown = m_attackSpeed;
}


Shade::~Shade(void)
{
}
