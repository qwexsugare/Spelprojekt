#include "SoulEaterSteed.h"
#include "LifestealingStrike.h"
#include "MeleeAttack.h"


SoulEaterSteed::SoulEaterSteed(FLOAT3 _pos, Path _path) : Enemy(_pos, _path, EnemyType::SOUL_EATER_STEED)
{
	m_modelId        = 84;
				     
	this->increaseStrength(6);
	this->increaseAgility(1);
	this->increaseWits(0);
	this->increaseFortitude(3);

	m_lowResource    = 60+20;
	m_highRescource  = 70+20;
				     

	
	m_skills.push_back(new LifestealingStrike());
	m_regularAttack = new MeleeAttack();
	m_aggroRange = 2.0f + m_regularAttack->getRange();

	Model *m = g_graphicsEngine->createModel("Beast", m_position);
	this->m_obb = new BoundingOrientedBox(*m->getObb());
	g_graphicsEngine->removeModel(m);
}

void SoulEaterSteed::attackHero(int heroIndex)
{
	this->attack(m_closestTargetId);
	this->m_attackCooldown = m_attackSpeed;

	
}

SoulEaterSteed::~SoulEaterSteed(void)
{
}
