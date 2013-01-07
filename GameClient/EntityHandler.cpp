#include "EntityHandler.h"

vector<ServerEntity*> EntityHandler::m_entities;	
unsigned int EntityHandler::m_nextId = 0;

EntityHandler::EntityHandler()
{
	//this->m_messageQueue = new MessageQueue();
}

//EntityHandler::EntityHandler(/*MessageHandler* _messageHandler*/)
//{
//	//this->m_messageQueue = new MessageQueue();
//	//this->m_messageHandler = _messageHandler;
//}

EntityHandler::~EntityHandler()
{
	//delete this->m_messageQueue;
}

void EntityHandler::removeAllEntities()
{
	for(int i = 0; i < this->m_entities.size(); i++)
	{
		delete this->m_entities[i];
	}
}

void EntityHandler::update(float dt)
{
	for(int i = 0; i < EntityHandler::m_entities.size(); i++)
	{
		EntityHandler::m_entities[i]->update(dt);
	}
}

void EntityHandler::addEntity(ServerEntity *_entity)
{
	_entity->setId(EntityHandler::m_nextId);
	EntityHandler::m_nextId++;
	EntityHandler::m_entities.push_back(_entity);
	//this->m_messageHandler->addQueue(_entity->getMessageQueue());
}

bool EntityHandler::removeEntity(ServerEntity *_entity)
{
	bool found = false;

	for(int i = 0; i < EntityHandler::m_entities.size(); i++)
	{
		if(EntityHandler::m_entities[i] == _entity)
		{
			delete EntityHandler::m_entities[i];
			EntityHandler::m_entities.erase(EntityHandler::m_entities.begin() + i);
			found = true;
			i = EntityHandler::m_entities.size();
		}
	}

	return found;
}

vector<ServerEntity*> EntityHandler::getEntities()
{
	return EntityHandler::m_entities;
}

ServerEntity* EntityHandler::getClosestEntity(ServerEntity *entity)
{
	float shortestDistance;
	int shortestIndex = -1;

	if(EntityHandler::m_entities[0] == entity && EntityHandler::m_entities.size() > 1)
	{
		shortestDistance = abs((entity->getPosition() - EntityHandler::m_entities[1]->getPosition()).length());
		shortestIndex = 1;
	}
	else
	{
		shortestDistance = abs((entity->getPosition() - EntityHandler::m_entities[0]->getPosition()).length());
		shortestIndex = 0;
	}

	for(int i = shortestIndex; i < EntityHandler::m_entities.size(); i++)
	{
		if(EntityHandler::m_entities[i] != entity && abs((entity->getPosition() - EntityHandler::m_entities[i]->getPosition()).length()) < shortestDistance)
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
			i = EntityHandler::m_entities.size();
			result = EntityHandler::m_entities[i];
		}
	}

	return result;
}