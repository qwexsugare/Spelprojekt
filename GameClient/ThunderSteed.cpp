#include "ThunderSteed.h"
#include "StunningStrike.h"
#include "RangedAttack.h"
#include "MyAlgorithms.h"

ThunderSteed::ThunderSteed(FLOAT3 _pos, Path _path) : Enemy(_pos, _path, EnemyType::THUNDERSTEED)
{
	m_modelId        = 87;

	this->increaseStrength(0);
	this->increaseAgility(5);
	this->increaseWits(2);
	this->increaseFortitude(5);

	m_lowResource    = 80+20;
	m_highRescource  = 90+20;


	m_regularAttack = new RangedAttack();
	m_aggroRange = 1.0f + m_regularAttack->getRange();

	Model *m = g_graphicsEngine->createModel("Beast", m_position);
	this->m_obb = new BoundingOrientedBox(*m->getObb());
	g_graphicsEngine->removeModel(m);
}

void ThunderSteed::attackHero(int heroIndex)
{
	this->attack(m_closestTargetId);
	this->m_attackCooldown = m_attackSpeed;

	if(random(1, 100) <= 15)
	{
		ServerEntity* e = EntityHandler::getServerEntity(m_closestTargetId);
		if(e)
		{
			((UnitEntity*)e)->stun(2.0f);
		}
	}
}

ThunderSteed::~ThunderSteed()
{

}
