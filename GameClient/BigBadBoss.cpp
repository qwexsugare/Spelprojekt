#include "BigBadBoss.h"
#include "RangedAttack.h"
#include "StunningStrike.h"
#include "MyAlgorithms.h"

BigBadBoss::BigBadBoss(FLOAT3 _pos):Enemy(_pos,EnemyType::BOSS)
{
	m_modelId = 80;
	//this->m_type = ServerEntity::BossType;

	this->increaseStrength(10);
	this->increaseAgility(5);
	this->increaseWits(8);    
	this->increaseFortitude(12);

	m_lowResource = 2000;
	m_highRescource = 3000;
	
	m_origPos = _pos;
	m_goalPosition=m_origPos;
	m_allowedMovement = 4.0f;

	

	m_skills.push_back(new StunningStrike());
	m_regularAttack = new MeleeAttack();
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

		}


		if(!m_willPursue)
		{
			m_dir = m_nextPosition - m_position;
			if(m_dir.length() > 0)
				m_dir = m_dir/m_dir.length();

			if(!m_reachedPosition && (m_position - m_nextPosition).length() > m_movementSpeed*dt)
			{
				m_position = m_position + m_dir*lastDT*m_movementSpeed;
			}

			else if(!m_reachedPosition && !m_willPursue)
			{
				m_position = m_nextPosition;
				m_reachedPosition = false;
			}
		
		}


		
				
		
		
		
		
		lastDT=0;

		if(this->m_isAttacking == false && this->m_isAttacking != this->m_oldIsAttacking)
		{
			this->m_messageQueue->pushOutgoingMessage(new CreateActionMessage(Skill::MOVE, this->m_id, this->m_position));
			this->m_oldIsAttacking = this->m_isAttacking;
		}
		
		if(this->m_dir.x!=m_prevDir.x||this->m_dir.z!=m_prevDir.z)
		{
			if(this->m_reachedPosition)
				this->m_dir=FLOAT3(0.0f,0.0f,0.0f);

			this->m_messageQueue->pushOutgoingMessage(new UpdateEntityMessage(this->m_id,m_position.x, m_position.z,m_rotation.x, m_position.x, m_position.z, m_position.x+this->m_dir.x, m_position.z+this->m_dir.z,this->getMovementSpeed()));
		}

		if(this->m_health <= 0) //The enemy has died
		{
			this->m_messageQueue->pushOutgoingMessage(new EnemyDiedMessage(this->m_id, this->m_lastDamageDealer, random(m_lowResource+m_extraDivinePower, m_highRescource+m_extraDivinePower)));
		}
	}



	this->m_obb->Center = XMFLOAT3(this->m_position.x, this->m_position.y, this->m_position.z);

}
