#include "Enemy.h"
#include "MyAlgorithms.h"
#include "MeleeAttack.h"
#include "Hero.h"

Enemy::Enemy() : UnitEntity()
{
	m_type = Type::EnemyType;
	this->m_position = FLOAT3(0.0f, 0.0f, 0.0f);
	this->m_goalPosition = FLOAT3(32.0f, 0.0f, 32.0f);
	this->m_nextPosition = this->m_position;
	this->m_reachedPosition = true;
	this->m_modelId = 1;
	this->m_currClosestStatic = EntityHandler::getEntitiesByType(ServerEntity::StaticType)[0];
	this->m_prevClosestStatic = this->m_currClosestStatic;
	this->m_health = 100;
	this->m_movementSpeed = 3.0f;
	this->m_aggroRange = 10.0f;
	this->m_willPursue = false;
	this->m_closestTargetId = -1;
	m_targetType = UnitEntity::HeroType;
	lastDT=0;
	m_staticAvDir = FLOAT3(0,0,0);
	m_enemyAvDir = FLOAT3(0,0,0);
	m_goalDirection = FLOAT3(0,0,0);
	m_rotationAdding = FLOAT3(0.0f,0,0);
	m_lowResource = 10;
	m_highRescource = 10;
	m_distanceToStatic = 15;
	this->m_staticBuffer = 2.00f;
	FLOAT3 hoxit = FLOAT3(0.0f,0.0f,0.0f);
	this->m_isAttacking = false;
	this->m_oldIsAttacking = false;
}

Enemy::Enemy(FLOAT3 _pos, Path _path, EnemyType _type) : UnitEntity(_pos)
{
	m_enemyType = _type;
	m_type = Type::EnemyType;
	
	//this->m_goalPosition = FLOAT3(5.0f, 0.0f,64.0f);
	m_targetType = UnitEntity::HeroType;
	this->m_reachedPosition = true;
	this->m_modelId = 80;
	this->m_staticBuffer = 2.00f;
	this->m_movementSpeed = 2.7f;
	this->m_aggroRange = 3.0f;
	this->m_willPursue = false;
	this->m_closestTargetId = -1;
	this->m_currClosestStatic = EntityHandler::getClosestEntityByType(this, ServerEntity::StaticType);
	this->m_prevClosestStatic = this->m_currClosestStatic;
	this->m_path = _path;
	this->m_currentPoint = 0;
	avoidTimer = 0.0f;
	m_staticAvDir = FLOAT3(0,0,0);
	m_enemyAvDir = FLOAT3(0,0,0);
	m_goalDirection = FLOAT3(0,0,0);
	m_rotationAdding = FLOAT3(0.0f,0,0);
	m_lowResource = 10;
	m_highRescource = 10;
	m_distanceToStatic = 15;
	//this->m_position = FLOAT3(0.0f, 0.0f, 0.0f);
	this->m_goalPosition = FLOAT3(32.0f, 0.0f, 32.0f);

	m_destination = FLOAT3(0,0,0);
	m_destinationRadius = 0.0f;

	ServerEntity *d = EntityHandler::getClosestEntityByType(this, ServerEntity::GoalType);
	m_destination = d->getPosition();
	m_destinationRadius = sqrt(d->getObb()->Extents.x*d->getObb()->Extents.x + d->getObb()->Extents.z*d->getObb()->Extents.z);
	m_distanceToPoint = 1.0f;
	FLOAT3 hoxit = FLOAT3(0.0f,0.0f,0.0f);
	if(this->m_path.nrOfPoints > 0)
	{
		this->m_goalPosition = FLOAT3(this->m_path.points[0].x, 0.0f, this->m_path.points[0].y);
	}
	lastDT=0;
	m_nextPosition = m_goalPosition;
	m_dir = m_nextPosition - m_position;
}

Enemy::~Enemy()
{
	
}

FLOAT3 Enemy::getDirection()
{
	if(m_dir.length() > 0.0f)
		return m_dir;
	else
		return m_position;
}
FLOAT3 Enemy::getEndPos()
{
	return FLOAT3(m_position.x+this->m_dir.x,0.0f, m_position.z+this->m_dir.z);
}


void Enemy::updateSpecificUnitEntity(float dt)
{
	this->lastDT+=dt;
	
	if(this->lastDT>0.1)
	{
		//Handle incoming messages
		Message *m;
		this->m_isAttacking = false;

		//this->m_reachedPosition = false;

		this->checkPursue();

		if(m_willPursue)
		{
			this->setNextPosition(m_closestTargetId, lastDT);

			if( (m_position - EntityHandler::getServerEntity(m_closestTargetId)->getPosition()).length() < this->m_regularAttack->getRange())
			{
				m_reachedPosition = true;
				this->m_isAttacking = true;
				if(this->m_attackCooldown <= 0.0f)
				{
					this->attackHero(this->m_closestTargetId);
				}

				if(((Hero*)EntityHandler::getServerEntity(m_closestTargetId))->getAlive() == false)
				{
					m_reachedPosition = false; 
					m_attackCooldown = m_baseAttackSpeed;
					m_willPursue = false;
						this->m_nextPosition = m_goalPosition;
				}
			}
			else 
			{
				m_reachedPosition = false;
				this->m_nextPosition = m_goalPosition;
			}

				if(((Hero*)EntityHandler::getServerEntity(m_closestTargetId))->getAlive() == false)
			{
				m_reachedPosition = false; 
				m_attackCooldown = m_baseAttackSpeed;
				m_willPursue = false;
				this->m_nextPosition = m_goalPosition;
			}
			
		}
		
		else
		{
			m_reachedPosition = false;
			this->m_nextPosition = m_goalPosition;
		}


		if(this->m_attackCooldown > 0.0f)
		{
			this->m_attackCooldown = this->m_attackCooldown - lastDT;
		}
	
		m_prevDir = m_dir;
	
	
		if(avoidTimer > 0.50f)
		{
			checkCloseEnemies(lastDT);

			avoidTimer = 0.0f;
		}
		if(m_dir.x>500)
		{
			hoxit=m_dir;
		}

		avoidTimer += lastDT;

		m_goalDirection = (this->m_nextPosition - this->m_position);
		m_distanceToPoint = m_goalDirection.length();

		if(m_enemyAvDir.length() > 0)
			m_enemyAvDir = m_enemyAvDir/m_enemyAvDir.length();
	
	
		if(m_goalDirection.length() > 0.0f)
			m_goalDirection = m_goalDirection/m_goalDirection.length();

		float t = 1.0f; 
		if(this->m_enemyType != EnemyType::SHADE)
			m_staticAvDir = (m_staticAvDir +this->checkStatic(lastDT))*0.5f;
		else
			m_staticAvDir = FLOAT3(0,0,0);

		
		if( m_staticAvDir.length() > 0)
		{
			t = m_staticAvDir.length();
		}

		if(m_enemyAvDir.length() > 0)
		{
			m_dir = m_goalDirection*0.5F + m_dir+ m_enemyAvDir*2 + m_staticAvDir*4;
			m_dir = m_dir/m_dir.length();
		}
		else
		{
			m_dir = m_dir*4.5 + m_goalDirection*1.0f/t+ m_staticAvDir*5.5f;//+m_enemyAvDir;
			
			

			m_dir = (m_prevDir*2 + m_dir);//*0.25f;

			
		}
			
			
			if(m_dir.length() > 0)
				m_dir = m_dir/m_dir.length();
			else 
				m_dir = m_prevDir;



			if((m_nextPosition - m_position).length() >(this->m_movementSpeed * lastDT) && !m_reachedPosition )
			{
				if(this->m_dir.length()>0)
				{
					float f = this->m_dir.length();
					this->m_dir = this->m_dir / this->m_dir.length();
					//m_currClosestStatic = EntityHandler::getClosestStatic(this);
					ServerEntity *stat = EntityHandler::getClosestStaticWithExtents(this);
					if((stat->getPosition() - m_position).length() 
						<sqrt(stat->getObb()->Extents.x*stat->getObb()->Extents.x+stat->getObb()->Extents.z*stat->getObb()->Extents.z)*1.2f+
						 sqrt(this->getObb()->Extents.x*this->getObb()->Extents.x+this->getObb()->Extents.z*this->getObb()->Extents.z))
					{
						
						FLOAT3 v = (m_position - stat->getPosition())/(m_position - stat->getPosition()).length();
						//v= m_dir*-1;
					   
						
						FLOAT3 d;/* = m_staticAvDir;// crossProduct(m_dir, FLOAT3(0,1,0));
						if((m_position + d - stat->getPosition()).length() > (m_position - d - stat->getPosition()).length())
							m_dir = d;
						else
							m_dir = (FLOAT3(0,0,0) -d);*/

						
						d =crossProduct(m_position - stat->getPosition(), FLOAT3(0,1,0));
						d = d/d.length();
						m_position = m_position + (v)*m_movementSpeed*lastDT;

						if((m_position+d -stat->getPosition()).length() > (m_position-d -stat->getPosition()).length())
							m_dir = d;
						else
							m_dir = FLOAT3(0,0,0) - d;
						
						   

						m_dir = v;//m_dir*-1;// + v+d;
						m_dir = m_dir/m_dir.length();

						//m_position = m_position + (m_dir)*m_movementSpeed*lastDT;

					}
					else
						this->m_position = this->m_position + this->m_dir * (this->m_movementSpeed-min(m_staticAvDir.length(),1.2f)) * lastDT;
					
					
				
					if(outOfBounds(m_position,0))
					{
						m_position = m_position -m_dir*m_movementSpeed*lastDT*2;
						m_dir = FLOAT3(32,0,32) - m_position;
						m_dir = m_dir/m_dir.length();
					}
				
				}
			}
			

			if((m_dir).length() > 0.00001f)
			{			
				m_rotationAdding = (m_rotationAdding +(m_dir + m_prevDir)*0.5f)*0.5f;
				m_rotation.x =  (atan2(-( m_rotationAdding).x, -( m_rotationAdding).z));
			}




		if((m_goalPosition-m_position).length() < (this->m_movementSpeed * lastDT)+2 && this->m_currentPoint < this->m_path.nrOfPoints-1)
		{
			
			this->m_currentPoint++;
			this->m_goalPosition = FLOAT3(this->m_path.points[this->m_currentPoint].x, 0.0f, this->m_path.points[this->m_currentPoint].y);
			this->m_reachedPosition = false;
			

			m_nextPosition = m_goalPosition;
			
			if((m_nextPosition - m_position).length()>0)
			{
				m_dir = m_dir*2 + (m_nextPosition - m_position)/(m_nextPosition - m_position).length();
				m_dir=m_dir/m_dir.length();
			}
			else
				m_dir=FLOAT3(0.0f,0.0f,0.0f);
		
		}

		else if((m_goalPosition-m_position).length() < (this->m_movementSpeed * lastDT)+1 || (m_position - m_destination).length() < m_destinationRadius + 0.1f)
		{
			this->m_messageQueue->pushOutgoingMessage(new RemoveServerEntityMessage(0, EntityHandler::getId(), this->m_id));
			this->m_messageQueue->pushOutgoingMessage(new EnemyReachedGoalMessage(this->m_id, this->m_position));
		}
		

	if(this->m_health <= 0) //The enemy has died
		{
			this->m_messageQueue->pushOutgoingMessage(new CreateActionMessage(Skill::DEATH, this->m_id, this->m_position));
			this->m_messageQueue->pushOutgoingMessage(new RemoveServerEntityMessage(0, EntityHandler::getId(), this->m_id));
			this->m_messageQueue->pushOutgoingMessage(new EnemyDiedMessage(this->m_id, this->m_lastDamageDealer, random(m_lowResource, m_highRescource)));
		}

	
		if(this->m_dir.x!=m_prevDir.x||this->m_dir.z!=m_prevDir.z)
		{
			if(this->m_reachedPosition)
				this->m_dir=FLOAT3(0.0f,0.0f,0.0f);

			this->m_messageQueue->pushOutgoingMessage(new UpdateEntityMessage(this->m_id,m_position.x, m_position.z,m_rotation.x, m_position.x, m_position.z, m_position.x+this->m_dir.x, m_position.z+this->m_dir.z,this->getMovementSpeed()));
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

void Enemy::setNextPosition(unsigned int _id, float dt)
{
	ServerEntity* unit = EntityHandler::getServerEntity(m_closestTargetId);

	FLOAT3 targetPosition = m_nextPosition;
	FLOAT3 _playerDirection=FLOAT3(0.0f,0.0f,0.f);
	if(unit != NULL)
	{
		switch(unit->getType())
		{
		case UnitEntity::HeroType:
			_playerDirection = ((Hero*)unit)->getDirection();
			break;
		case UnitEntity::EnemyType:
			_playerDirection = ((Enemy*)unit)->getDirection();
			break;
		}
	
		targetPosition = unit->getPosition();// + _playerDirection*3*dt;
	}
	this->m_nextPosition = targetPosition;
	this->m_reachedPosition = false;
}

void Enemy::checkCloseEnemies(float dt)
{
	Enemy* closestEnemy = (Enemy*)EntityHandler::getClosestEntityByType(this, UnitEntity::EnemyType);

	m_enemyAvDir = FLOAT3(0,0,0);

	if(closestEnemy)
	{
		if(closestEnemy != NULL && (m_position - closestEnemy->getPosition() ).length() < sqrt(this->getObb()->Extents.x*this->getObb()->Extents.x +this->getObb()->Extents.z*this->getObb()->Extents.z)*0.5f)
		{
			m_position = m_position + (m_position - closestEnemy->getPosition()*2);
		}
		if(closestEnemy != NULL && (m_position - closestEnemy->getPosition() ).length() < sqrt(this->getObb()->Extents.x*this->getObb()->Extents.x +this->getObb()->Extents.z*this->getObb()->Extents.z)*3)
		{
			if((m_position - closestEnemy->getPosition()).length()>0)
			{
					this->updateEnemyAvDir(crossProduct(m_position - closestEnemy->getPosition(), FLOAT3(0,1,0)));
					closestEnemy->updateEnemyAvDir(m_enemyAvDir*-1);
			}
			
			m_dir = m_dir/m_dir.length();
		}
		
	}
}

void Enemy::checkPursue()
{
	//CheckDistanceToCurrentTarget
	float currDistToHero=9999999;
	if(m_closestTargetId >= 0 && EntityHandler::getServerEntity(m_closestTargetId) != NULL)
	{
		ServerEntity *e = EntityHandler::getServerEntity(m_closestTargetId);
		currDistToHero = (this->m_position - EntityHandler::getServerEntity(m_closestTargetId)->getPosition()).length();

	}
	else 
	{
		m_willPursue = false;
	}

	if(currDistToHero > this->m_aggroRange*1.5f)
	{	
		m_willPursue = false;
	}


	if(!m_willPursue)
	{
		ServerEntity* se = EntityHandler::getClosestEntityByType(this, m_targetType);
		if(se)
		{
			if((this->m_position-se->getPosition()).length() <= this->m_aggroRange )
			{
				m_willPursue = true;
				m_closestTargetId = se->getId();
				this->m_messageQueue->pushOutgoingMessage(new CreateActionMessage(Skill::ENEMY_PURSUE, this->m_id, m_position));
			}
		}
	}

	
}

void Enemy::updateEnemyAvDir(FLOAT3 _val)
{
	m_enemyAvDir = m_enemyAvDir + _val;
	if(m_enemyAvDir.length() > 1.0f)
		m_enemyAvDir = m_enemyAvDir/m_enemyAvDir.length();
	
}

FLOAT3 Enemy::checkStatic(float dt)
{
	
	FLOAT3 avoidDir = FLOAT3(0,0,0);
	FLOAT3 avd = avoidDir;
	FLOAT3 currDir =this->m_dir;
	if(currDir.length()>0)
		currDir = currDir / currDir.length();
	
	FLOAT3 cross = this->crossProduct(FLOAT3(0,1,0), currDir);
	if(cross.length()>0)
		cross = cross/cross.length();
	cross = cross*1.5f;
	float avoidBuffer = .0080f;
	float t = avoidBuffer;
	FLOAT3 temp = FLOAT3(0,0,0);
	FLOAT3 temp1 = FLOAT3(0,0,0);
	FLOAT3 temp2 = FLOAT3(0,0,0);
	ServerEntity *stat;
	
	
		
		for(int i = 1; i <12; i++)
		{
			temp = m_position + currDir*i*dt*m_movementSpeed;
			temp1 = temp+ (cross);
			temp2 = temp - (cross);
			stat = EntityHandler::getClosestSuperStatic(temp);
			
			float test  = 9999999997.3f;// = (stat->getPosition() - temp1).length();
			float test2 = 9999999997.3f;
			
			if(stat != NULL)
			{
				

				avoidBuffer = sqrt(stat->getObb()->Extents.x*stat->getObb()->Extents.x + stat->getObb()->Extents.z*stat->getObb()->Extents.z) + 
							  sqrt(this->getObb()->Extents.x*this->getObb()->Extents.x +this->getObb()->Extents.z*this->getObb()->Extents.z)+0.2f;
				t = sqrt(stat->getObb()->Extents.x*stat->getObb()->Extents.x + stat->getObb()->Extents.z*stat->getObb()->Extents.z);
				test = (stat->getPosition() - temp1).length();
				test2 = (stat->getPosition() - temp2).length();

				
	
				if(test < avoidBuffer )
				{
					if(m_currClosestStatic->getId() != stat->getId())
					{
						m_prevClosestStatic = m_currClosestStatic;
						m_currClosestStatic = stat;
					}
				
					avoidBuffer = test;
					avoidDir = FLOAT3(0,0,0) -cross;
				}

				if(test2< avoidBuffer)
				{
					if(m_currClosestStatic->getId() != stat->getId())
					{
						m_prevClosestStatic = m_currClosestStatic;
						m_currClosestStatic = stat;
					}
				
					avoidBuffer = test2;
					avoidDir =  cross;
				}


				if(outOfBounds(temp,4) && avoidTimer > 0.5f)
				{
					float t = (temp1 - FLOAT3(32,0,32)).length();

					if( t < (temp2 - FLOAT3(32,0,32)).length())
						avoidDir = cross/(0.1f*i);
					else
						avoidDir = FLOAT3(0,0,0) - cross/(0.1f*i);
					avoidDir=avoidDir/avoidDir.length();
					return avoidDir;
				}


				if( avoidDir.length() != 0)
				{
					/*if (abs(test - test2) < 0.001f)
					{
						if((temp2-m_nextPosition).length() < (temp1-m_nextPosition).length())
						{
							avoidDir = cross/10;
						}
						else
							avoidDir = FLOAT3(0,0,0) - cross/10;
					}*/

					// Cant change the movement speed this way, interferes with unitentity ms management.
					/*if((m_position - stat->getPosition()).length() <m_movementSpeed*dt*(10-i))
						m_movementSpeed = m_movementSpeed/2;
					else
						m_movementSpeed = m_baseMovementSpeed;*/

					m_distanceToStatic = i;
					avoidDir = avoidDir/avoidDir.length();
					avoidDir = avoidDir/min(avoidBuffer,1.0f);
					avoidDir = avoidDir*t;//, 0.4f);
					avoidDir = avoidDir;

					//if(m_staticAvDir.length() > (avoidDir+m_staticAvDir).length())
						//return m_staticAvDir;
					//else
						return avoidDir;
					//avd = avd + (avoidDir/i)*max(avoidBuffer,1.0f);// + max(avd,((avoidDir/i)*max(avoidBuffer,1.0f)));
				}
			}
		}
	
	//m_distanceToStatic = 0.0001f;
	return FLOAT3(0,0,0);// m_staticAvDir/2;

}

void Enemy::attackHero()
{
	this->attack(m_closestTargetId);
	this->m_attackCooldown = 1.0f;
}

FLOAT3 Enemy::crossProduct(FLOAT3 _first, FLOAT3 _second)
{
	float x = _first.y*_second.z - _first.z*_second.y;
	float y = 0;//_first.z*_second.x - _first.x*_second.z;
	float z = _first.x*_second.y - _first.y*_second.x;

	return FLOAT3(x,y,z);
}

bool Enemy::outOfBounds(FLOAT3 _pt, int _offset)
{
	bool t = false;

	if(_pt.x > 64+_offset || _pt.z > 64+_offset || _pt.x < 0-_offset || _pt.z < 0-_offset)
		t = true;

	return t;
}



bool Enemy::checkDistanceToStatic(float currFactor, float prevFactor)
{
	if((m_currClosestStatic->getPosition()-m_position).length() > currFactor*m_staticBuffer && (m_prevClosestStatic->getPosition()-m_position).length() > prevFactor*m_staticBuffer )
		return true;
	else
		return false;
}

void Enemy::setTargetType(UnitEntity::Type _type)
{
	m_targetType = _type;
	ServerEntity* se = EntityHandler::getClosestEntityByType(this, m_targetType);
	if(se)
		m_closestTargetId = se->getId();
	else
		m_closestTargetId = -1;
}

int Enemy::getSubType()const
{
	return m_enemyType;
}

