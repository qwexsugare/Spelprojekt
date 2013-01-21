#include "Enemy.h"

Enemy::Enemy()
{
	m_type = Type::EnemyType;
	this->m_positon = FLOAT3(0.0f, 0.0f, 0.0f);
	this->m_goalPosition = FLOAT3(100.0f, 0.0f, 100.0f);
	this->m_obb = new BoundingOrientedBox(XMFLOAT3(this->m_positon.x, this->m_positon.y, this->m_positon.z), XMFLOAT3(0.5f, 0.5f, 0.5f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	this->m_nextPosition = this->m_positon;
	this->m_reachedPosition = true;
	this->m_modelId = 0;

	this->m_movementSpeed = 3.0f;
	this->m_aggroRange = 10.0f;
	this->m_willPursue = false;
	this->m_closestHero = 999;
}

Enemy::Enemy(FLOAT3 _pos) : ServerEntity(_pos)
{
	m_type = Type::EnemyType;
	this->m_goalPosition = FLOAT3(100.0f, 0.0f, 100.0f);
	this->m_obb = new BoundingOrientedBox(XMFLOAT3(this->m_positon.x, this->m_positon.y, this->m_positon.z), XMFLOAT3(0.5f, 0.5f, 0.5f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	this->m_nextPosition = this->m_positon;
	this->m_reachedPosition = true;
	this->m_modelId = 0;

	this->m_movementSpeed = 3.0f;
	this->m_aggroRange = 10.0f;
	this->m_willPursue = false;
	this->m_closestHero = 999;
}

void Enemy::update(float dt)
{
	//Handle incoming messages
	Message *m;

	this->m_reachedPosition = false;

	this->checkPursue();
	
	if(m_willPursue)
		this->setNextPosition(m_closestHero, dt);
	else
		this->m_nextPosition = m_goalPosition;
	

FLOAT3 avDir = FLOAT3(0,0,0);
	/*ServerEntity *_hero = EntityHandler::getAllHeroes()[0];
	FLOAT3 playerPos = _hero->getPosition();
	if((playerPos-m_positon).length() < 30)
	{
		avDir = this->checkStatic(dt,playerPos);
	}*/
	

	while(this->m_messageQueue->incomingQueueEmpty() == false)
	{
		m = this->m_messageQueue->pullIncomingMessage();

		if(m->type == Message::Collision)
		{
			CollisionMessage *cm = (CollisionMessage*)m;
			ServerEntity *se = EntityHandler::getServerEntity(cm->affectedDudeId);
			if(se != NULL && se->getType() == ServerEntity::HeroType && this->m_attackCooldown <= 0.0f)
			{
				EntityHandler::addEntity(new MeleeAttack(this->m_positon, 10.0f, cm->affectedDudeId));
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
		m_dir = this->m_nextPosition - this->m_positon;
		if(m_dir.length() > this->m_movementSpeed * dt)
		{
			m_dir = m_dir + avDir;
			m_dir = m_dir / m_dir.length();
			
			this->m_positon = this->m_positon + (m_dir * this->m_movementSpeed * dt);
		}
		else
		{
			this->m_positon = this->m_nextPosition;
			this->m_reachedPosition = true;
		}

		this->m_rotation.x = atan2(-m_dir.x, -m_dir.z);
	}

	if(this->m_health <= 0)
	{
		this->m_messageQueue->pushOutgoingMessage(new RemoveServerEntityMessage(0, EntityHandler::getId(), this->m_id));
	}

	this->m_obb->Center = XMFLOAT3(this->m_positon.x, this->m_positon.y, this->m_positon.z);
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
		currDistToHero = (this->m_positon - (EntityHandler::getAllHeroes()[m_closestHero])->getPosition()).length();
	
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
			if((this->m_positon-_hero->getPosition()).length() <= this->m_aggroRange )
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
	FLOAT3 currDir = m_dir;
	currDir = currDir / currDir.length();

	FLOAT3 cross = this->crossProduct(currDir, FLOAT3(0,1,0));
	cross = cross/cross.length();
	float avoidBuffer = 10;

	FLOAT3 temp1 = FLOAT3(0,0,0);
	FLOAT3 temp2 = FLOAT3(0,0,0);
	
		for(int i = 1; i < 10; i++)
		{
			temp1 = m_positon + currDir*i*3 + cross;
			temp2 = m_positon + currDir*i*3 - cross;
			float test = (_pPos-temp1).length();
			if(test < avoidBuffer)
			{
				avoidBuffer = (_pPos-temp1).length();
				avoidDir = FLOAT3(0,0,0) -cross;
			}
			test = (_pPos-temp2).length();
			if(test< avoidBuffer)
			{
				avoidDir =  cross;
			}

			if(avoidBuffer < 10)
			{
				avoidDir = avoidDir*(11-i)*11;
				break;
			}
		}
	

	return avoidDir;

}


FLOAT3 Enemy::crossProduct(FLOAT3 _first, FLOAT3 _second)
{
	float x = _first.y*_second.z - _first.z*_second.y;
	float y = _first.z*_second.x - _first.x*_second.z;
	float z = _first.x*_second.y - _first.y*_second.x;

	return FLOAT3(x,y,z);
}