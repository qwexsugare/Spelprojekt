#include "ClientEntityHandler.h"

vector<Entity*> ClientEntityHandler::m_entities;

ClientEntityHandler::ClientEntityHandler()
{

}

ClientEntityHandler::~ClientEntityHandler()
{
	for(int i = 0; i < this->m_entities.size(); i++)
	{
		delete this->m_entities[i];
	}
}

void ClientEntityHandler::removeAllEntities()
{
	for(int i = 0; i < this->m_entities.size(); i++)
	{
		delete this->m_entities[i];
	}
}

void ClientEntityHandler::addEntity(Entity *_entity)
{
	ClientEntityHandler::m_entities.push_back(_entity);
}

bool ClientEntityHandler::removeEntity(Entity *_entity)
{
	bool found = false;

	for(int i = 0; i < ClientEntityHandler::m_entities.size(); i++)
	{
		if(ClientEntityHandler::m_entities[i] == _entity)
		{
			delete ClientEntityHandler::m_entities[i];
			ClientEntityHandler::m_entities.erase(ClientEntityHandler::m_entities.begin() + i);
			found = true;
			i = ClientEntityHandler::m_entities.size();
		}
	}

	return found;
}

vector<Entity*> ClientEntityHandler::getEntities()
{
	vector<Entity*> result = ClientEntityHandler::m_entities;
	
	return result;
}

Entity* ClientEntityHandler::getEntity(unsigned int id)
{
	Entity* result = NULL;

	for(int i = 0; i < ClientEntityHandler::m_entities.size(); i++)
	{
		if(ClientEntityHandler::m_entities[i]->m_id == id)
		{
			result = ClientEntityHandler::m_entities[i];
			i = ClientEntityHandler::m_entities.size();
		}
	}

	return result;
}

vector<Entity*> ClientEntityHandler::getAllEnemies()
{
	vector<Entity*> enemies = vector<Entity*>();
	for(int i = 0; i < ClientEntityHandler::m_entities.size(); i++)
	{
		if(ClientEntityHandler::m_entities[i]->m_type == ServerEntity::Type::EnemyType)
		{
			Entity* enemy = ClientEntityHandler::m_entities[i];
			enemies.push_back(enemy);
		}
	}

	return enemies;
}

int ClientEntityHandler::getNrOfEnemies()
{
	int counter = 0;

	for(int i = 0; i < ClientEntityHandler::m_entities.size(); i++)
	{	
		if(ClientEntityHandler::m_entities[i]->m_type == ServerEntity::Type::EnemyType)
		{
			counter++;
		}
	}

	return counter;
}

vector<Entity*> ClientEntityHandler::getAllHeroes()
{
	vector<Entity*> heroes;
	for(int i = 0; i < ClientEntityHandler::m_entities.size(); i++)
	{
		if(ClientEntityHandler::m_entities[i]->m_type == ServerEntity::HeroType)
		{
			Entity* hero = ClientEntityHandler::m_entities[i];
			heroes.push_back(hero);
		}
	}

	return heroes;
}

vector<Entity*> ClientEntityHandler::getAllStaticObjects()
{
	vector<Entity*> staticObjects;
	for(int i = 0; i < ClientEntityHandler::m_entities.size(); i++)
	{
		if(ClientEntityHandler::m_entities[i]->m_type == ServerEntity::StaticType)
		{
			Entity* staticObject = ClientEntityHandler::m_entities[i];
			staticObjects.push_back(staticObject);
		}
	}

	return staticObjects;
}

void ClientEntityHandler::update(float dt)
{
	for(int i = 0; i < ClientEntityHandler::m_entities.size(); i++)
	{
		ClientEntityHandler::m_entities[i]->update(dt);
	}
}