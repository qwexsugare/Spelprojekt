#include "FrostDemon.h"
#include "StunningStrike.h"
#include "RangedAttack.h"
#include "MyAlgorithms.h"

FrostDemon::FrostDemon(FLOAT3 _pos, Path _path) : Enemy(_pos, _path, EnemyType::FROST_DEMON)
{
	m_modelId = 80;

	this->increaseStrength(1);
	this->increaseAgility(3);
	this->increaseWits(3);    
	this->increaseFortitude(2);

	m_lowResource = 50+20;
	m_highRescource = 60+20;
	


	m_skills.push_back(new StunningStrike());
	m_regularAttack = new RangedAttack();
	m_aggroRange = 1.0f + m_regularAttack->getRange();

	Model *m = g_graphicsEngine->createModel("Imp", m_position);
	this->m_obb = new BoundingOrientedBox(*m->getObb());
	g_graphicsEngine->removeModel(m);
}

void FrostDemon::attackHero(int heroIndex)
{
	this->attack(m_closestTargetId);
	this->m_attackCooldown = m_attackSpeed;
	
	if(random(1, 100) <= 12)
	{
		ServerEntity* e = EntityHandler::getServerEntity(m_closestTargetId);
		if(e)
		{
			((UnitEntity*)e)->stun(2.0f);
		}
	}
}

FrostDemon::~FrostDemon()
{

}
