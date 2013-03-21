#include "MindReaver.h"


#include "MindReaver.h"
#include "RangedAttack.h"
#include "StunningStrike.h"
#include "MyAlgorithms.h"
#include "MeleeAOEAttack.h"

MindReaver::MindReaver(FLOAT3 _pos):Enemy(_pos,EnemyType::BOSS)
{
	m_modelId = 89;
	//this->m_type = ServerEntity::BossType;
	this->m_weaponType = WEAPON_TYPE::AOE;

	m_health = 1000; 
	m_maxHealth=m_health;
	this->increaseAgility(10);
	this->increaseWits(16);    
	this->increaseFortitude(4);

	m_lowResource = 2000;
	m_highRescource = 3000;
	
	m_origPos = _pos;
	m_goalPosition=m_origPos;
	m_allowedMovement = 4.0f;

	

	m_skills.push_back(new StunningStrike());
	m_regularAttack = new MeleeAOEAttack();
	m_regularAttack->setRange(m_regularAttack->getRange()*1.5);
	m_aggroRange = 2.0f + m_regularAttack->getRange();
	

	Model *m = g_graphicsEngine->createModel("Char", m_position);
	this->m_obb = new BoundingOrientedBox(*m->getObb());
	g_graphicsEngine->removeModel(m);

	this->setScale(1.4f);
}
void MindReaver::attackHero(int heroIndex)
{
	this->attack(m_closestTargetId);
	this->m_attackCooldown = m_attackSpeed;
	
	if(random(1, 100) <= 15)
	{
		ServerEntity* e = EntityHandler::getServerEntity(m_closestTargetId);
		if(e)
		{
			this->attack(m_closestTargetId);
			this->attack(m_closestTargetId);
			
		}
	}
}

MindReaver::~MindReaver(void)
{
}
void MindReaver::updateSpecificUnitEntity(float dt)
{
	this->lastDT+=dt;
	
	if(this->lastDT>0.05)
	{
		//Handle incoming messages
		Message *m;
		m_prevDir = m_dir;

		this->checkAttack(lastDT);

		if(!m_willPursue)
			m_nextPosition = m_goalPosition;

		m_dir = m_dir + (m_nextPosition - m_position);
		
		if(m_dir.length() > 0)
			m_dir = m_dir/m_dir.length();

		
		if(!m_reachedPosition)
		{
			if(m_willPursue && (m_origPos - m_position).length() < m_allowedMovement)
			{
					m_position = m_position + m_dir*lastDT*m_movementSpeed;
			}
			
		
			else 
			{
				m_dir = m_goalPosition - m_position;
				if(m_dir.length() > 0) 
					m_dir = m_dir/m_dir.length();
				if((m_goalPosition - m_position).length() > 0.1f)
				{
					m_position = m_position + m_dir*m_movementSpeed*lastDT;
				}
				else
				{
					m_position = m_goalPosition;
					m_reachedPosition = true; 
				}
			}
		}

		
		
		if((m_dir).length() > 0.00001f)
		{			
			m_rotationAdding = (m_rotationAdding +(m_dir + m_prevDir)*0.5f)*0.5f;
			m_rotation.x =  (atan2(-( m_rotationAdding).x, -( m_rotationAdding).z));
		}

		lastDT=0;

		if(this->m_isAttacking == false && this->m_isAttacking != this->m_oldIsAttacking)
		{
			
			
			this->m_messageQueue->pushOutgoingMessage(new CreateActionMessage(Skill::MOVE, this->m_id, this->m_position));
				
			
			this->m_oldIsAttacking = this->m_isAttacking;
		}

		if((m_position -m_origPos).length() < 0.1f)
			{
				this->m_messageQueue->pushOutgoingMessage(new CreateActionMessage(Skill::IDLE, this->m_id, this->m_position));
			}
		
		if(this->m_dir.x!=m_prevDir.x||this->m_dir.z!=m_prevDir.z)
		{
			if(this->m_reachedPosition)
				this->m_dir=FLOAT3(0.0f,0.0f,0.0f);

			this->m_messageQueue->pushOutgoingMessage(new UpdateEntityMessage(this->m_id,m_position.x, m_position.z,m_rotation.x, m_position.x, m_position.z, m_position.x+this->m_dir.x, m_position.z+this->m_dir.z,this->getMovementSpeed()));
		}
	}



	this->m_obb->Center = XMFLOAT3(this->m_position.x, this->m_position.y, this->m_position.z);



}

void MindReaver::tellBossToDropGold()
{
	this->m_messageQueue->pushOutgoingMessage(new CreateActionMessage(Skill::DEATH, this->m_id, this->m_position));
	this->m_messageQueue->pushOutgoingMessage(new EnemyDiedMessage(this->m_id, this->m_lastDamageDealer, random(m_lowResource+m_extraDivinePower, m_highRescource+m_extraDivinePower)));
}
unsigned short MindReaver::getWeaponType()
{
	return this->m_weaponType;
}