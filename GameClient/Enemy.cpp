#include "Enemy.h"

Enemy::Enemy() : UnitEntity()
{
	m_type = Type::EnemyType;
	this->m_position = FLOAT3(0.0f, 0.0f, 0.0f);
	this->m_goalPosition = FLOAT3(32.0f, 0.0f, 32.0f);
	this->m_obb = new BoundingOrientedBox(XMFLOAT3(this->m_position.x, this->m_position.y, this->m_position.z), XMFLOAT3(0.5f, 0.5f, 0.5f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	this->m_nextPosition = this->m_position;
	this->m_reachedPosition = true;
	this->m_modelId = 1;
	this->m_health = 100;

	this->m_movementSpeed = 1.5f;
	this->m_aggroRange = 10.0f;
	this->m_willPursue = false;
	this->m_closestHero = 999;
}

Enemy::Enemy(FLOAT3 _pos, Path _path) : UnitEntity(_pos)
{
	m_type = Type::EnemyType;
	
	//this->m_goalPosition = FLOAT3(5.0f, 0.0f,64.0f);
	this->m_obb = new BoundingOrientedBox(XMFLOAT3(this->m_position.x, this->m_position.y, this->m_position.z), XMFLOAT3(0.5f, 0.5f, 0.5f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	this->m_nextPosition = this->m_position;
	this->m_reachedPosition = true;
	this->m_modelId = 1;

	this->m_movementSpeed = 1.5f;
	this->m_aggroRange = 10.0f;
	this->m_willPursue = false;
	this->m_closestHero = 999;
	this->m_closestStatic = EntityHandler::getAllStaticObjects()[EntityHandler::getAllStaticObjects().size()-1];
	this->m_path = _path;
	this->m_currentPoint = 0;

	if(this->m_path.nrOfPoints > 0)
	{
		this->m_goalPosition = FLOAT3(this->m_path.points[0].x, 0.0f, this->m_path.points[0].y);
	}

	m_nextPosition = m_goalPosition;
}

void Enemy::updateSpecificUnitEntity(float dt)
{
	//Handle incoming messages
	Message *m;

	//this->m_reachedPosition = false;

	this->checkPursue();
	
	if(m_willPursue)
		this->setNextPosition(m_closestHero, dt);
	else
		this->m_nextPosition = m_goalPosition;
	

	FLOAT3 avDir = FLOAT3(0,0,0);
	ServerEntity *_static = EntityHandler::getClosestStatic(this);
	if(_static != NULL)
	{
		FLOAT3 statPos = _static->getPosition();
	
		avDir = this->checkStatic(dt,statPos);
		if((m_closestStatic->getPosition()-m_position).length() > 3 )
		{
			FLOAT3 te = (this->m_nextPosition - this->m_position);
		
			te = te/15;
		
			m_dir.y = 0;
			m_dir = m_dir*500;
		

			this->m_dir =this->m_dir+ te;
		
			m_dir = m_dir/m_dir.length();

			//this->m_dir =m_dir+ te;
		}
	
		if((m_closestStatic->getPosition()-m_position).length() > 50)
		{
			m_dir = m_dir + (this->m_nextPosition - this->m_position)/2;
			//m_dir = m_dir/m_dir.length();
		}
	}
	

	while(this->m_messageQueue->incomingQueueEmpty() == false)
	{
		m = this->m_messageQueue->pullIncomingMessage();

		if(m->type == Message::Collision)
		{
			CollisionMessage *cm = (CollisionMessage*)m;
			ServerEntity *se = EntityHandler::getServerEntity(cm->affectedDudeId);
			if(se != NULL && se->getType() == ServerEntity::HeroType && this->m_attackCooldown <= 0.0f)
			{
				//EntityHandler::addEntity(new MeleeAttack(this->m_position, 10.0f, cm->affectedDudeId));
				this->dealDamage(se, 0, 10);
				this->m_attackCooldown = 1.0f;
			}
		}

		delete m;
	}

	if(this->m_attackCooldown > 0.0f)
	{
		this->m_attackCooldown = this->m_attackCooldown - dt;
	}

	if(this->m_reachedPosition == false)
	{
		//m_dir = m_dir+ (this->m_nextPosition - this->m_position);
		//m_dir = (this->m_nextPosition - this->m_position);
		//m_dir = m_dir/m_dir.length();
		if((m_nextPosition - m_position).length() >this->m_movementSpeed * dt)

		{
			this->m_dir = this->m_dir + avDir/5;
			this->m_dir = this->m_dir / this->m_dir.length();
			
			this->m_position = this->m_position + this->m_dir * this->m_movementSpeed * dt;
		}
		
		else
		{
			this->m_position = this->m_nextPosition;
			this->m_reachedPosition = true;
		}

		//this->m_rotation.x = atan2(-m_dir.x, -m_dir.z);
	}
	else
	{
		//Check if there's a new position in the path
		if(this->m_currentPoint < this->m_path.nrOfPoints)
		{
			this->m_currentPoint++;
			this->m_goalPosition = FLOAT3(this->m_path.points[this->m_currentPoint].x, 0.0f, this->m_path.points[this->m_currentPoint].y);
			this->m_reachedPosition = false;
		}
	}

	if(this->m_health <= 0)
	{
		this->m_messageQueue->pushOutgoingMessage(new RemoveServerEntityMessage(0, EntityHandler::getId(), this->m_id));
	}

	this->m_obb->Center = XMFLOAT3(this->m_position.x, this->m_position.y, this->m_position.z);
}

void Enemy::setNextPosition(int index, float dt)
{
	Hero *hero = (Hero*)(EntityHandler::getAllHeroes()[index]);

	FLOAT3 _playerDirection= hero->getDirection();

	FLOAT3 targetPosition = hero->getPosition() + _playerDirection*3*dt;
	
	

	this->m_nextPosition = targetPosition;
	this->m_reachedPosition = false;
}

void Enemy::checkPursue()
{
	float currDistToHero;
	if(m_closestHero < EntityHandler::getAllHeroes().size())
		currDistToHero = (this->m_position - (EntityHandler::getAllHeroes()[m_closestHero])->getPosition()).length();
	
	else 
		currDistToHero = 99999.0f;

		

	if(currDistToHero > this->m_aggroRange*1.5f)
	{	
		m_willPursue = false;
	}
	
	if(!m_willPursue)
	{
		for(int i = 0; i < EntityHandler::getAllHeroes().size(); i++)
		{
			ServerEntity* _hero = EntityHandler::getAllHeroes()[i];
			if((this->m_position-_hero->getPosition()).length() <= this->m_aggroRange )
			{
				m_willPursue = true; 
				this->m_closestHero = i;
				break;
			}
		}
	}
	
}

FLOAT3 Enemy::checkStatic(float dt, FLOAT3 _pPos)
{
	
	FLOAT3 avoidDir = FLOAT3(0,0,0);
	FLOAT3 currDir = this->m_dir;
	currDir = currDir / currDir.length();

	FLOAT3 cross = this->crossProduct(FLOAT3(0,1,0), currDir);
	cross = cross/cross.length();
	cross = cross;
	float avoidBuffer = 1.0f;

	FLOAT3 temp1 = FLOAT3(0,0,0);
	FLOAT3 temp2 = FLOAT3(0,0,0);
	
		for(int i = 1; i < 15; i++)
		{
			
			
			temp1 = m_position + currDir*i+ (cross);

			temp2 = m_position + currDir*i - (cross);
			

			float test = (EntityHandler::getClosestSuperStatic(temp1)->getPosition() - temp1).length();

			if(test < avoidBuffer)
			{
				
				m_closestStatic = EntityHandler::getClosestSuperStatic(temp1);
				avoidBuffer = test;
				avoidDir = FLOAT3(0,0,0) -cross/(i);;
			}

			test = (EntityHandler::getClosestSuperStatic(temp2)->getPosition() - temp2).length();

			if(test< avoidBuffer)
			{
				m_closestStatic = EntityHandler::getClosestSuperStatic(temp2);
				avoidBuffer = test;
				avoidDir =  cross/(i);;
			}

			if(avoidBuffer < 1.0f)
			{
				avoidDir = avoidDir/(0.1f*i);
				return avoidDir;
			}
		}
	
	//avoidDir = m_nextPosition - m_position;
	return avoidDir;

}


FLOAT3 Enemy::crossProduct(FLOAT3 _first, FLOAT3 _second)
{
	float x = _first.y*_second.z - _first.z*_second.y;
	float y = 0;//_first.z*_second.x - _first.x*_second.z;
	float z = _first.x*_second.y - _first.y*_second.x;

	return FLOAT3(x,y,z);
}