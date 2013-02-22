#include "Enemy.h"
#include "MyAlgorithms.h"
#include "MeleeAttack.h"
#include "Hero.h"

Enemy::Enemy() : UnitEntity()
{
	m_type = Type::EnemyType;
	this->m_position = FLOAT3(0.0f, 0.0f, 0.0f);
	this->m_goalPosition = FLOAT3(32.0f, 0.0f, 32.0f);
	this->m_obb = new BoundingOrientedBox(XMFLOAT3(this->m_position.x, this->m_position.y, this->m_position.z), XMFLOAT3(0.5f, 0.5f, 0.5f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	this->m_nextPosition = this->m_position;
	this->m_reachedPosition = true;
	this->m_modelId = 1;
	this->m_currClosestStatic = EntityHandler::getEntitiesByType(ServerEntity::StaticType)[0];
	this->m_health = 100;
	this->m_movementSpeed = 3.0f;
	this->m_aggroRange = 10.0f;
	this->m_willPursue = false;
	this->m_closestTargetId = -1;
	m_targetType = UnitEntity::HeroType;
}

Enemy::Enemy(FLOAT3 _pos, Path _path) : UnitEntity(_pos)
{
	m_type = Type::EnemyType;
	
	//this->m_goalPosition = FLOAT3(5.0f, 0.0f,64.0f);
	
	m_targetType = UnitEntity::HeroType;
	this->m_regularAttack = new MeleeAttack();
	this->m_reachedPosition = true;
	this->m_modelId = 80;
	this->m_staticBuffer = 2.0f;
	this->m_movementSpeed = 2.7f;
	this->m_aggroRange = 3.0f;
	this->m_willPursue = false;
	this->m_closestTargetId = -1;
	this->m_currClosestStatic = EntityHandler::getEntitiesByType(ServerEntity::StaticType)[0];
	this->m_prevClosestStatic = this->m_currClosestStatic;
	this->m_path = _path;
	this->m_currentPoint = 0;
	avoidTimer = 0.0f;
	m_staticAvDir = FLOAT3(0,0,0);
	m_enemyAvDir = FLOAT3(0,0,0);
	m_rotationAdding = FLOAT3(0.0f,0,0);
	m_lowResource = 10;
	m_highRescource = 10;
	
	Model *m = g_graphicsEngine->createModel("Beast1_5", m_position);
	this->m_obb = new BoundingOrientedBox(*m->getObb());
	g_graphicsEngine->removeModel(m);

	if(this->m_path.nrOfPoints > 0)
	{
		this->m_goalPosition = FLOAT3(this->m_path.points[0].x, 0.0f, this->m_path.points[0].y);
	}

	m_nextPosition = m_goalPosition;
	m_dir = m_nextPosition - m_position;
}

FLOAT3 Enemy::getDirection()
{
	if(m_dir.length() > 0.0f)
		return m_dir;
	else
		return m_position;
}

void Enemy::updateSpecificUnitEntity(float dt)
{
	//Handle incoming messages
	Message *m;

	//this->m_reachedPosition = false;

	this->checkPursue();

	if(m_willPursue)
	{
		this->setNextPosition(m_closestTargetId, dt);

		if( (m_position - EntityHandler::getServerEntity(m_closestTargetId)->getPosition()).length() < this->m_regularAttack->getRange())
		{
			m_reachedPosition = true;
			if(this->m_attackCooldown <= 0.0f)
			{
				this->attackHero();
				
			}
		}
	}
	else
		this->m_nextPosition = m_goalPosition;


	if(this->m_attackCooldown > 0.0f)
	{
		this->m_attackCooldown = this->m_attackCooldown - dt;
	}
	
	m_prevDir = m_dir;
	
	ServerEntity *_static = EntityHandler::getClosestStatic(this);
	if(_static != NULL )
	{
		FLOAT3 statPos = _static->getPosition();
		m_staticAvDir = (m_staticAvDir +this->checkStatic(dt,statPos));
		
		
	FLOAT3 te = (this->m_nextPosition - this->m_position);
		
		if(te.length() > 0.01f)
			te = te/te.length();
		else
			te = te/0.01f;

		if(checkDistanceToStatic(1,1))
		{
			m_dir.y = 0;
			m_dir = m_dir*1000;
			this->m_dir =this->m_dir+ te;
			m_dir = m_dir/m_dir.length();
		}
	
		if(checkDistanceToStatic(2,1))
		{
			m_dir =m_dir +te*2;
		}
		if(checkDistanceToStatic(5,2))
		{
			m_dir =te;
			m_staticAvDir = FLOAT3(0,0,0);
		}

	}

	if(avoidTimer > 0.50f)
	{
		checkCloseEnemies(dt);
		avoidTimer = 0.0f;
	}
	avoidTimer += dt;

	
	if((m_nextPosition - m_position).length() >(this->m_movementSpeed * dt) && !m_reachedPosition )
	{
			
		this->m_dir = this->m_dir*15 + m_staticAvDir/3 + m_enemyAvDir;
		this->m_dir = this->m_dir / this->m_dir.length();
		this->m_position = this->m_position + this->m_dir * this->m_movementSpeed * dt;
	}
	

	if((m_dir).length() > 0.00001f)
	{
		m_rotationAdding = (m_rotationAdding +(m_dir + m_prevDir)*0.5f)*0.5f;
		m_rotation.x =  (atan2(-( m_rotationAdding).x, -( m_rotationAdding).z));
	}

		
	
	if((m_goalPosition-m_position).length() < (this->m_movementSpeed * dt)+2)
	{
		//Check if there's a new position in the path
		if(this->m_currentPoint < this->m_path.nrOfPoints)
		{
			this->m_currentPoint++;
			this->m_goalPosition = FLOAT3(this->m_path.points[this->m_currentPoint].x, 0.0f, this->m_path.points[this->m_currentPoint].y);
			this->m_reachedPosition = false;
			//m_nextPosition = m_goalPosition;
			//m_dir = m_dir + (m_nextPosition - m_position) + m_staticAvDir/5;
		}
		else //The enemy has reached its goal
		{
			this->m_messageQueue->pushOutgoingMessage(new RemoveServerEntityMessage(0, EntityHandler::getId(), this->m_id));
			this->m_messageQueue->pushOutgoingMessage(new EnemyReachedGoalMessage(this->m_id));
		}
	}

	if(this->m_health <= 0) //The enemy has died
	{
		this->m_messageQueue->pushOutgoingMessage(new CreateActionMessage(Skill::DEATH, this->m_id, this->m_position));
		this->m_messageQueue->pushOutgoingMessage(new RemoveServerEntityMessage(0, EntityHandler::getId(), this->m_id));
		this->m_messageQueue->pushOutgoingMessage(new EnemyDiedMessage(this->m_id, this->m_lastDamageDealer, random(m_lowResource, m_highRescource)));
	}

	this->m_obb->Center = XMFLOAT3(this->m_position.x, this->m_position.y, this->m_position.z);
}

void Enemy::setNextPosition(unsigned int _id, float dt)
{
	ServerEntity* unit = EntityHandler::getServerEntity(m_closestTargetId);

	FLOAT3 targetPosition = m_nextPosition;
	FLOAT3 _playerDirection;
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
	//if(EntityHandler::getClosestEnemy(this) != NULL && (m_position - EntityHandler::getClosestEnemy(this)->getPosition() ).length() < this->getObb()->Extents.z*2)
	//{
	//	
	//	if((m_position+m_dir/10 - EntityHandler::getClosestEnemy(this)->getPosition()).length() < (m_position - EntityHandler::getClosestEnemy(this)->getPosition() ).length())
	//	{
	//		m_movementSpeed = 0.8f;
	//		((UnitEntity*)EntityHandler::getClosestEnemy(this))->setMovementSpeed(2.5f);
	//	}
	//	else 
	//		m_movementSpeed = m_baseMovementSpeed;

	//	m_enemyAvDir =  (m_position - EntityHandler::getClosestEnemy(this)->getPosition())/(m_position - EntityHandler::getClosestEnemy(this)->getPosition()).length();
	//	m_dir = m_dir*2 + m_enemyAvDir;
	//	//m_position = m_position +m_enemyAvDir*2*dt;
	//}
	//else 
	//	m_movementSpeed = m_baseMovementSpeed;
	
	ServerEntity* closestEnemy = EntityHandler::getClosestEntityByType(this, UnitEntity::EnemyType);

	if(closestEnemy != NULL && (m_position - closestEnemy->getPosition() ).length() < this->getObb()->Extents.z*2)
	{
		
		if((m_position+m_dir/10 - closestEnemy->getPosition()).length() < (m_position - closestEnemy->getPosition() ).length())
		{
			m_movementSpeed = 0.8f;
			((UnitEntity*)closestEnemy)->setMovementSpeed(2.5f);
		}
		else 
			m_movementSpeed = m_baseMovementSpeed;

		m_enemyAvDir =  (m_position - closestEnemy->getPosition())/(m_position - closestEnemy->getPosition()).length();
		m_dir = m_dir*2 + m_enemyAvDir;
		//m_position = m_position +m_enemyAvDir*2*dt;
	}
	else 
		m_movementSpeed = m_baseMovementSpeed;
}

void Enemy::checkPursue()
{
	float currDistToHero;
	if(m_closestTargetId >= 0)
		currDistToHero = (this->m_position - EntityHandler::getServerEntity(m_closestTargetId)->getPosition()).length();
	
	else 
		currDistToHero = 99999.0f;

		

	if(currDistToHero > this->m_aggroRange*1.5f)
	{	
		m_willPursue = false;
	}
	
	if(!m_willPursue)
	{
		ServerEntity* se = EntityHandler::getClosestEntityByType(this, m_targetType);
		if((this->m_position-se->getPosition()).length() <= this->m_aggroRange )
		{
			m_willPursue = true;
			m_closestTargetId = se->getId();
		}
	}
}

FLOAT3 Enemy::checkStatic(float dt, FLOAT3 _pPos)
{
	
	FLOAT3 avoidDir = FLOAT3(0,0,0);
	FLOAT3 currDir = this->m_dir;
	currDir = currDir / currDir.length();
	//m_movementSpeed = 5.0f;
	FLOAT3 cross = this->crossProduct(FLOAT3(0,1,0), currDir);
	cross = cross/cross.length();
	cross = cross;
	float avoidBuffer = .0080f;
	float t = avoidBuffer;
	FLOAT3 temp = FLOAT3(0,0,0);
	FLOAT3 temp1 = FLOAT3(0,0,0);
	FLOAT3 temp2 = FLOAT3(0,0,0);
	ServerEntity *stat;
	
		for(int i = 1; i < 10; i++)
		{
			temp = m_position + currDir*i;
			temp1 = m_position + currDir*i+ (cross);
			temp2 = m_position + currDir*i - (cross);
			stat = EntityHandler::getClosestSuperStatic(temp);
			
			float test  = 9999999997.3f;// = (stat->getPosition() - temp1).length();
			float test2 = 9999999997.3f;
			
			if(stat != NULL)
			{
				avoidBuffer = max(stat->getObb()->Extents.x, stat->getObb()->Extents.z);
				test = (stat->getPosition() - temp1).length();
				test2 = (stat->getPosition() - temp2).length();
			}
			
			if(test < avoidBuffer +0.2f)
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
					m_currClosestStatic = EntityHandler::getClosestSuperStatic(temp1);
				}
				
				avoidBuffer = test2;
				avoidDir =  cross;
			}

			if(outOfBounds(temp) && avoidTimer > 0.5f)
			{
				float t = (temp1 - FLOAT3(32,0,32)).length();

				if( t < (temp2 - FLOAT3(32,0,32)).length())
					avoidDir = cross/(0.1f*i);
				else
					avoidDir = FLOAT3(0,0,0) - cross/(0.1f*i);

				return avoidDir;
			}

			if( avoidDir.length() != 0)
			{
				if (abs(test - test2) < 0.001f)
				{
					if((temp2-m_nextPosition).length() < (temp1-m_nextPosition).length())
					{
						avoidDir = temp2;
					}
					else
						avoidDir = temp;
				}

			
				return avoidDir*avoidBuffer/i;
			}
		}
	
	
	return avoidDir;

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

bool Enemy::outOfBounds(FLOAT3 _pt)
{
	bool t = false;

	if(_pt.x > 68 || _pt.z > 68 || _pt.x < -4 || _pt.z < -4)
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