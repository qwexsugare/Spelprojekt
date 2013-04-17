#include "Imp.h"
#include "MeleeAttack.h"


Imp::Imp(FLOAT3 _pos, Path _path) : Enemy(_pos,_path, EnemyType::IMP)
{
	m_modelId = 81;
	
	
	m_baseMentalResistance = 1.00f - 0.5f;
	this->increaseStrength(2+(g_configFile->getLevelMode()-1));
	this->increaseAgility(7+(g_configFile->getLevelMode()));
	this->increaseWits(0+(g_configFile->getLevelMode()));
	this->increaseFortitude(1);


	m_lowResource = 20+20;
	m_highRescource = 30+20;
	
	m_regularAttack = new MeleeAttack();
	m_aggroRange = 2.0f + m_regularAttack->getRange();

	Model *m = g_graphicsEngine->createModel("Imp", m_position);
	this->m_obb = new BoundingOrientedBox(*m->getObb());
	g_graphicsEngine->removeModel(m);

}

void Imp::attackHero(int heroIndex)
{
	this->attack(m_closestTargetId);
	this->m_attackCooldown = m_attackSpeed;

	
}


Imp::~Imp(void)
{
}
