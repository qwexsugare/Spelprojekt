#include "EntityHandler.h"

sf::Mutex EntityHandler::m_mutex;
vector<ServerEntity*> EntityHandler::m_entities;	
unsigned int EntityHandler::m_nextId = 0;
MessageQueue *EntityHandler::m_messageQueue;
MessageHandler *EntityHandler::m_messageHandler;

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

	EntityHandler::m_mutex.Unlock();
}

void EntityHandler::addEntity(ServerEntity *_entity)
{
	EntityHandler::m_mutex.Lock();
	_entity->setId(EntityHandler::m_nextId);
	EntityHandler::m_nextId++;
	EntityHandler::m_entities.push_back(_entity);
	EntityHandler::m_messageHandler->addQueue(_entity->getMessageQueue());
	EntityHandler::m_mutex.Unlock();
}

bool EntityHandler::removeEntity(ServerEntity *_entity)
{
	bool found = false;
	EntityHandler::m_mutex.Lock();

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

	EntityHandler::m_mutex.Unlock();

	return found;
}

vector<ServerEntity*> EntityHandler::getEntities()
{
	EntityHandler::m_mutex.Lock();
	vector<ServerEntity*> result = EntityHandler::m_entities;
	EntityHandler::m_mutex.Unlock();
	
	return result;
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

ServerEntity* EntityHandler::getClosestEnemy(ServerEntity *entity)
{
	float shortestDistance = 9999999999.3f;
	int shortestIndex = -1;

	for(int i = 0; i < EntityHandler::m_entities.size(); i++)
	{
		if(EntityHandler::m_entities[i] != entity && (entity->getPosition() - EntityHandler::m_entities[i]->getPosition()).length() < shortestDistance && EntityHandler::m_entities[i]->getType() == ServerEntity::EnemyType)
		{
			shortestDistance = abs((entity->getPosition() - EntityHandler::m_entities[i]->getPosition()).length());
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

// Remember to delete the return value after usage when calling this function
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