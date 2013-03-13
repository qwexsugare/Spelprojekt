#include "EntityHandler.h"

sf::Mutex EntityHandler::m_mutex;
vector<ServerEntity*> EntityHandler::m_entities;	
unsigned int EntityHandler::m_nextId = 0;
MessageQueue *EntityHandler::m_messageQueue;
MessageHandler *EntityHandler::m_messageHandler;
ServerQuadTree* EntityHandler::m_quadtree;

EntityHandler::EntityHandler()
{
	EntityHandler::m_messageQueue = new MessageQueue();
}

EntityHandler::EntityHandler(MessageHandler* _messageHandler)
{
	EntityHandler::m_messageQueue = new MessageQueue();
	EntityHandler::m_messageHandler = _messageHandler;
	_messageHandler->addQueue(EntityHandler::m_messageQueue);
}

EntityHandler::~EntityHandler()
{
	delete this->m_messageQueue;
	delete EntityHandler::m_quadtree;
}

void EntityHandler::removeAllEntities()
{
	EntityHandler::m_mutex.Lock();

	for(int i = 0; i < this->m_entities.size(); i++)
	{
		delete this->m_entities[i];
	}

	EntityHandler::m_mutex.Unlock();
}

void EntityHandler::update(float dt)
{
	//handle messages
	Message *m;

	while(this->m_messageQueue->incomingQueueEmpty() == false)
	{
		m = this->m_messageQueue->pullIncomingMessage();

		if(m->type == Message::RemoveEntity)
		{
			RemoveServerEntityMessage *rem = (RemoveServerEntityMessage*)m;
			EntityHandler::removeEntity(EntityHandler::getServerEntity(rem->removedId));		
			this->m_messageQueue->pushOutgoingMessage(new RemoveServerEntityMessage(0, 1, rem->removedId));
		}

		delete m;
	}

	//update the entities
	EntityHandler::m_mutex.Lock();

	for(int i = 0; i < EntityHandler::m_entities.size(); i++)
	{
		EntityHandler::m_entities[i]->update(dt);
	}

	EntityHandler::m_quadtree->updateServerEntities(dt);

	EntityHandler::m_mutex.Unlock();
}

void EntityHandler::addEntity(ServerEntity *_entity)
{
	EntityHandler::m_mutex.Lock();
	_entity->setId(EntityHandler::m_nextId);
	if(_entity->getType() == ServerEntity::StaticType || _entity->getType() == ServerEntity::GoalType)
	{
		if(EntityHandler::m_quadtree->addServerEntity(_entity))
		{
			EntityHandler::m_nextId++;
			EntityHandler::m_messageHandler->addQueue(_entity->getMessageQueue());
		}
		else
			delete _entity;
	}
	else
	{
		EntityHandler::m_entities.push_back(_entity);
		EntityHandler::m_nextId++;
		EntityHandler::m_messageHandler->addQueue(_entity->getMessageQueue());
	}
	EntityHandler::m_mutex.Unlock();

	if(_entity->getVisible() == true)
	{
		EntityHandler::m_messageQueue->pushOutgoingMessage(new InitEntityMessage(_entity->getType(), _entity->getSubType(),_entity->getModelId(), _entity->getWeaponType(),_entity->getId(),_entity->getPosition().x,_entity->getPosition().z,_entity->getRotation().y,1.0,_entity->getHealth(),_entity->getPosition().x,_entity->getPosition().z,_entity->getEndPos().x,_entity->getEndPos().z,_entity->getMovementSpeed()));
	}	
}

bool EntityHandler::removeEntity(ServerEntity *_entity)
{
	bool found = false;

	if(_entity != NULL)
	{
		EntityHandler::m_mutex.Lock();

		if(_entity->getType() == ServerEntity::StaticType ||_entity->getType() == ServerEntity::GoalType )
		{
			found = EntityHandler::m_quadtree->removeServerEntity(_entity);
		}
		else
		{
			for(int i = 0; i < EntityHandler::m_entities.size(); i++)
			{
				if(EntityHandler::m_entities[i] == _entity)
				{
					EntityHandler::m_messageHandler->removeQueue(EntityHandler::m_entities[i]->getMessageQueue()->getId());
					delete EntityHandler::m_entities[i];
					EntityHandler::m_entities.erase(EntityHandler::m_entities.begin() + i);
					found = true;
					i = EntityHandler::m_entities.size();
				}
			}
		}

		EntityHandler::m_mutex.Unlock();
	}

	return found;
}

vector<ServerEntity*> EntityHandler::getEntities()
{
	EntityHandler::m_mutex.Lock();

	vector<ServerEntity*> ses;
	EntityHandler::m_quadtree->getAllServerEntites(ses);

	//ses.resize(EntityHandler::m_entities.size()+ses.size());
	for(int i = 0; i < EntityHandler::m_entities.size(); i++)
		ses.push_back(EntityHandler::m_entities[i]);
	
	EntityHandler::m_mutex.Unlock();

	return ses;
}

vector<ServerEntity*> EntityHandler::getEntitiesByType(ServerEntity::Type _type)
{
	EntityHandler::m_mutex.Lock();

	vector<ServerEntity*> ses;
	if(_type == ServerEntity::StaticType || _type == ServerEntity::StaticType )
		EntityHandler::m_quadtree->getAllServerEntites(ses);
	else
	{
		for(int i = 0; i < EntityHandler::m_entities.size(); i++)
		{
			if(EntityHandler::m_entities[i]->getType() == _type)
			{
				ses.push_back(EntityHandler::m_entities[i]);
			}
		}
	}

	EntityHandler::m_mutex.Unlock();

	return ses;
}

ServerEntity* EntityHandler::getClosestEntity(ServerEntity *entity)
{
	float shortestDistance;
	int shortestIndex = -1;

	if(EntityHandler::m_entities[0] == entity && EntityHandler::m_entities.size() > 1)
	{
		shortestDistance = (entity->getPosition() - EntityHandler::m_entities[1]->getPosition()).length();
		shortestIndex = 1;
	}
	else
	{
		shortestDistance = (entity->getPosition() - EntityHandler::m_entities[0]->getPosition()).length();
		shortestIndex = 0;
	}

	for(int i = shortestIndex; i < EntityHandler::m_entities.size(); i++)
	{
		if(EntityHandler::m_entities[i] != entity && (entity->getPosition() - EntityHandler::m_entities[i]->getPosition()).length() < shortestDistance)
		{
			shortestDistance = (entity->getPosition() - EntityHandler::m_entities[i]->getPosition()).length();
			shortestIndex = i;
		}
	}

	if(shortestIndex > -1)
	{
		return EntityHandler::m_entities[shortestIndex];
	}
	else
	{
		return NULL;
	}
}

ServerEntity* EntityHandler::getClosestEntityByType(ServerEntity* _entity, ServerEntity::Type _type)
{
	ServerEntity* closestEntity = NULL;

	if(_type == ServerEntity::Type::StaticType || _type == ServerEntity::Type::GoalType)
	{
		vector<ServerEntity*> serverEntities;
		EntityHandler::m_quadtree->getAllServerEntites(serverEntities);

		if(serverEntities.size() > 1)
		{
			bool foundMatch = false;
			float shortestDistance;

			for(int i = 0; i < serverEntities.size(); i++)
			{
				if(serverEntities[i] != _entity)
				{
					if(foundMatch)
					{
						if((serverEntities[i]->getPosition()-_entity->getPosition()).length() < shortestDistance)
						{
							shortestDistance = (serverEntities[i]->getPosition()-_entity->getPosition()).length();
							closestEntity = serverEntities[i];
						}
					}
					else
					{
						shortestDistance = (serverEntities[i]->getPosition()-_entity->getPosition()).length();
						closestEntity = serverEntities[i];
						foundMatch = true;
					}
				}
			}
		}
	}
	else
	{
		if(EntityHandler::m_entities.size() > 1)
		{
			bool foundMatch = false;
			float shortestDistance;

			for(int i = 0; i < EntityHandler::m_entities.size(); i++)
			{
				if(EntityHandler::m_entities[i] != _entity && EntityHandler::m_entities[i]->getType() == _type)
				{
					if(foundMatch)
					{
						if((EntityHandler::m_entities[i]->getPosition()-_entity->getPosition()).length() < shortestDistance)
						{
							shortestDistance = (EntityHandler::m_entities[i]->getPosition()-_entity->getPosition()).length();
							closestEntity = EntityHandler::m_entities[i];
						}
					}
					else
					{
						shortestDistance = (EntityHandler::m_entities[i]->getPosition()-_entity->getPosition()).length();
						closestEntity = EntityHandler::m_entities[i];
						foundMatch = true;
					}
				}
			}
		}
	}

	return closestEntity;
}

ServerEntity* EntityHandler::getClosestStatic(ServerEntity *entity)
{
	float shortestDistance = 9999999999.3f;
	int shortestIndex = -1;

	vector<ServerEntity*> entities;
	m_quadtree->getAllServerEntites(entities);

	for(int i = 0; i < entities.size(); i++)
	{
		if(entities[i] != entity && (entity->getPosition() - entities[i]->getPosition()).length() < shortestDistance && entities[i]->getType() == ServerEntity::StaticType)
		{
			shortestDistance = abs((entity->getPosition() - entities[i]->getPosition()).length());
			shortestIndex = i;
		}
	}

	if(shortestIndex > -1)
	{
		return entities[shortestIndex];
	}
	else
	{
		return NULL;
	}
}

ServerEntity* EntityHandler::getClosestStaticWithExtents(FLOAT3 _pos)
{
	float shortestDistance = 9999999999.3f;
	int shortestIndex = -1;

	vector<ServerEntity*> entities;
	m_quadtree->getAllServerEntites(entities);

	for(int i = 0; i < entities.size(); i++)
	{
		if( (_pos - entities[i]->getPosition()).length()-sqrt(entities[i]->getObb()->Extents.x*entities[i]->getObb()->Extents.x + entities[i]->getObb()->Extents.z*entities[i]->getObb()->Extents.z)
			< shortestDistance && entities[i]->getType() == ServerEntity::StaticType)
		{
			shortestDistance = abs((_pos - entities[i]->getPosition()).length());
			shortestIndex = i;
		}
	}

	if(shortestIndex > -1)
	{
		return entities[shortestIndex];
	}
	else
	{
		return NULL;
	}
}

ServerEntity* EntityHandler::getClosestSuperStatic(FLOAT3 _pos)
{
	float shortestDistance = 9999999999.3f;
	int shortestIndex = -1;
	
	vector<ServerEntity*> entities;
	m_quadtree->getAllServerEntites(entities);

	for(int i = 0; i < entities.size(); i++)
	{
		if((_pos - entities[i]->getPosition()).length() -sqrt(entities[i]->getObb()->Extents.x*entities[i]->getObb()->Extents.x + entities[i]->getObb()->Extents.z*entities[i]->getObb()->Extents.z)
			< shortestDistance && entities[i]->getType() == ServerEntity::StaticType)
		{
			shortestDistance = abs((_pos - entities[i]->getPosition()).length());
			shortestIndex = i;
		}

		
	}

	if(shortestIndex > -1)
	{
		return entities[shortestIndex];
	}
	else
	{
		return NULL;
	}
}

ServerEntity* EntityHandler::getServerEntity(unsigned int id)
{
	ServerEntity* result = NULL;

	for(int i = 0; i < EntityHandler::m_entities.size(); i++)
	{
		if(EntityHandler::m_entities[i]->getId() == id)
		{
			result = EntityHandler::m_entities[i];
			i = EntityHandler::m_entities.size();
		}
	}

	return result;
}

vector<ServerEntity*> EntityHandler::getAllEnemies()
{
	vector<ServerEntity*> enemies = vector<ServerEntity*>();
	for(int i = 0; i < EntityHandler::m_entities.size(); i++)
	{
		if(EntityHandler::m_entities[i]->getType() == ServerEntity::Type::EnemyType)
		{
			ServerEntity* enemy = EntityHandler::m_entities[i];
			enemies.push_back(enemy);
		}
	}

	return enemies;
}

int EntityHandler::getNrOfEnemies()
{
	int counter = 0;

	for(int i = 0; i < EntityHandler::m_entities.size(); i++)
	{	
		if(EntityHandler::m_entities[i]->getType() == ServerEntity::Type::EnemyType)
		{
			counter++;
		}
	}

	return counter;
}

vector<ServerEntity*> EntityHandler::getAllHeroes()
{
	vector<ServerEntity*> heroes;
	for(int i = 0; i < EntityHandler::m_entities.size(); i++)
	{
		if(EntityHandler::m_entities[i]->getType() == ServerEntity::HeroType)
		{
			ServerEntity* hero = EntityHandler::m_entities[i];
			heroes.push_back(hero);
		}
	}

	return heroes;
}

unsigned int EntityHandler::getId()
{
	return EntityHandler::m_messageQueue->getId();
}

void EntityHandler::initQuadTree(FLOAT2 _extents)
{
	EntityHandler::m_quadtree = new ServerQuadTree(3, D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(_extents.x, _extents.y));
}

bool EntityHandler::intersects(const BoundingSphere& _bs)
{
	bool ret = false;
	EntityHandler::m_mutex.Lock();
	for(int i = 0; i < EntityHandler::m_entities.size(); i++)
	{
		if(m_entities[i]->intersects(_bs))
		{
			ret = true;
			i = EntityHandler::m_entities.size();
		}
	}
	if(!ret)
	{
		ret = m_quadtree->intersectsWithObject(_bs);
	}
	EntityHandler::m_mutex.Unlock();
	return ret;
}

bool EntityHandler::intersects(const BoundingOrientedBox& _obb)
{
	bool ret = false;
	EntityHandler::m_mutex.Lock();
	for(int i = 0; i < EntityHandler::m_entities.size(); i++)
	{
		if(m_entities[i]->intersects(_obb))
		{
			ret = true;
			i = EntityHandler::m_entities.size();
		}
	}
	if(!ret)
	{
		ret = m_quadtree->intersectsWithObject(_obb);
	}
	EntityHandler::m_mutex.Unlock();
	return ret;
}