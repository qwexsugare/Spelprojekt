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

	/*m_health = 100*m_fortitude; 
	m_physicalDamage = m_strength*5;
	m_mentalDamage = m_wits*5;
	m_baseMovementSpeed = 2.0 + m_agility*0.1f;
	m_movementSpeed = m_baseMovementSpeed;
	m_baseAttackSpeed = 2.0 - m_agility* 0.05f;
	m_attackSpeed = m_baseAttackSpeed;

	m_basePhysicalResistance = 1.00f - m_strength*2*0.01f;
	m_physicalResistance = m_basePhysicalResistance ; 

	m_baseMentalResistance = 1.00f - m_fortitude*2*0.01f;
	m_mentalResistance = m_baseMentalResistance;*/

	m_skills.push_back(new StunningStrike());
	m_regularAttack = new RangedAttack();
	m_regularAttack->setRange(m_regularAttack->getRange()*1.5);
	m_aggroRange = 2.0f + m_regularAttack->getRange() *2.0f;
	

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
	
	//if the ai has reached the church, it will tell the server
	//and starts a timer which makes the ai stand still for x sec
	
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
		
		
	

		
		
		lastDT=0;

		if(this->m_isAttacking == false && this->m_isAttacking != this->m_oldIsAttacking)
		{
			this->m_messageQueue->pushOutgoingMessage(new CreateActionMessage(Skill::MOVE, this->m_id, this->m_position));
			this->m_oldIsAttacking = this->m_isAttacking;
		}
		
		
	}



	this->m_obb->Center = XMFLOAT3(this->m_position.x, this->m_position.y, this->m_position.z);

}
