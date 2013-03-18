#include "BigBadBoss.h"
#include "RangedAttack.h"
#include "StunningStrike.h"
#include "MyAlgorithms.h"

BigBadBoss::BigBadBoss(FLOAT3 _pos):Enemy(_pos,EnemyType::BOSS)
{
	m_modelId = 80;

	this->increaseStrength(10);
	this->increaseAgility(5);
	this->increaseWits(8);    
	this->increaseFortitude(12);

	m_lowResource = 2000;
	m_highRescource = 3000;
	
	m_origPos = _pos;
	m_allowedMovement = 4.0f;

	

	m_skills.push_back(new StunningStrike());
	m_regularAttack = new RangedAttack();
	m_regularAttack->setRange(m_regularAttack->getRange()*1.5);
	m_aggroRange = 2.0f + m_regularAttack->getRange();
	

	Model *m = g_graphicsEngine->createModel("Imp", m_position);
	this->m_obb = new BoundingOrientedBox(*m->getObb());
	g_graphicsEngine->removeModel(m);
}
void BigBadBoss::attackHero(int heroIndex)
{
	this->attack(m_closestTargetId);
	this->m_attackCooldown = m_attackSpeed;
	
	if(random(1, 100) <= 15)
	{
		ServerEntity* e = EntityHandler::getServerEntity(m_closestTargetId);
		if(e)
		{
			((UnitEntity*)e)->stun(4.0f);
		}
	}
}

BigBadBoss::~BigBadBoss(void)
{
}
void BigBadBoss::updateSpecificUnitEntity(float dt)
{
	this->lastDT+=dt;
	

	
	if(this->lastDT>0.05)
	{
		//Handle incoming messages
		Message *m;
		m_prevDir = m_dir;

		this->checkAttack(lastDT);
		
		
		if((m_position - m_origPos).length() < m_allowedMovement && !m_reachedPosition)
		{
			m_dir = (m_goalPosition - m_position);
			if(m_dir.length() > 0)
				m_dir = m_dir/m_dir.length();

			m_position = m_position + m_dir*lastDT*m_movementSpeed;
		}
		else if(!m_willPursue)
		{
			m_dir = (m_origPos - m_position)/(m_origPos - m_position).length();
			m_position = m_position + m_dir*lastDT*m_movementSpeed;
		}
		
		
	

		
		
		lastDT=0;

		if(this->m_isAttacking == false && this->m_isAttacking != this->m_oldIsAttacking)
		{
			this->m_messageQueue->pushOutgoingMessage(new CreateActionMessage(Skill::MOVE, this->m_id, this->m_position));
			this->m_oldIsAttacking = this->m_isAttacking;
		}
		
		
	}



	this->m_obb->Center = XMFLOAT3(this->m_position.x, this->m_position.y, this->m_position.z);

}
