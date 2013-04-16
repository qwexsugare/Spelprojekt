#include "Shade.h"
#include "MeleeAttack.h"


Shade::Shade(FLOAT3 _pos, Path _path) : Enemy(_pos, _path, EnemyType::SHADE)
{
	m_modelId = 82;
	

	m_basePhysicalResistance = 0.02f;
	m_mentalResistance = m_baseMentalResistance;
	this->increaseStrength(4+(g_configFile->getLevelMode()));
	this->increaseAgility(3+(g_configFile->getLevelMode()-1));
	this->increaseWits(0);
	this->increaseFortitude(1+(g_configFile->getLevelMode()-1));


	m_lowResource = 30+20;
	m_highRescource = 40+20;
	

	m_regularAttack = new MeleeAttack();
	m_aggroRange = 2.0f + m_regularAttack->getRange();

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
