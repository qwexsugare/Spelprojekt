#include "BruteSteed.h"
#include "MeleeAttack.h"


BruteSteed::BruteSteed(FLOAT3 _pos, Path _path) : Enemy(_pos, _path, EnemyType::BRUTE_STEED)
{
	m_modelId        = 85;
				    
	m_baseMentalResistance =1.00f - 0.50f;
	m_mentalResistance = m_baseMentalResistance;
	this->increaseStrength(2+(g_configFile->getLevelMode()-1));
	this->increaseAgility(2+(g_configFile->getLevelMode()*2));
	this->increaseWits(1);
	this->increaseFortitude(8+(g_configFile->getLevelMode()*2));
				    
	m_lowResource    = 90+20;
	m_highRescource  = 100+20;
	


	
	m_regularAttack = new MeleeAttack();
	m_aggroRange = 2.0f + m_regularAttack->getRange();

	Model *m = g_graphicsEngine->createModel("Beast", m_position);
	this->m_obb = new BoundingOrientedBox(*m->getObb());
	g_graphicsEngine->removeModel(m);
}

void BruteSteed::attackHero(int heroIndex)
{
	this->attack(m_closestTargetId);
	this->m_attackCooldown = m_attackSpeed;

	
}


BruteSteed::~BruteSteed(void)
{
}
