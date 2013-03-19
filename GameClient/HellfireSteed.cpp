#include "HellfireSteed.h"
#include "RangedAttack.h"


HellfireSteed::HellfireSteed(FLOAT3 _pos, Path _path) : Enemy(_pos, _path, EnemyType::HELLFIRE_STEED)
{
	m_modelId        = 86;

	
	this->increaseStrength(4);
	this->increaseAgility(3);
	this->increaseWits(1);
	this->increaseFortitude(3);

	m_lowResource    = 70+20;
	m_highRescource  = 80+20;
	

	

	m_regularAttack = new RangedAttack();
	m_aggroRange =m_regularAttack->getRange();

	Model *m = g_graphicsEngine->createModel("Beast", m_position);
	this->m_obb = new BoundingOrientedBox(*m->getObb());
	g_graphicsEngine->removeModel(m);

}

void HellfireSteed::attackHero(int heroIndex)
{
	this->attack(m_closestTargetId);
	this->m_attackCooldown = m_attackSpeed;

	//Special skill: 
	//  20% Critical strike 3x times physical damage
}


HellfireSteed::~HellfireSteed(void)
{
}
