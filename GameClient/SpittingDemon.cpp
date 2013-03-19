#include "SpittingDemon.h"
#include "PoisonStrike.h"
#include "RangedAttack.h"

SpittingDemon::SpittingDemon(FLOAT3 _pos, Path _path) : Enemy(_pos, _path, EnemyType::SPITTING_DEMON)
{
	m_modelId        = 83;
	
	this->increaseStrength(0);
	this->increaseAgility(7);
	this->increaseWits(4);
	this->increaseFortitude(1);

	m_lowResource    = 40+20;
	m_highRescource  = 50+20;
	
	m_skills.push_back(new PoisonStrike());

	m_regularAttack = new RangedAttack();
	m_aggroRange = m_regularAttack->getRange();

	Model *m = g_graphicsEngine->createModel("Imp", m_position);
	this->m_obb = new BoundingOrientedBox(*m->getObb());
	g_graphicsEngine->removeModel(m);
}

void SpittingDemon::attackHero(int heroIndex)
{
	this->attack(m_closestTargetId);
	this->m_attackCooldown = m_attackSpeed;

	//Use Poison Strike, please!
}


SpittingDemon::~SpittingDemon(void)
{
}
