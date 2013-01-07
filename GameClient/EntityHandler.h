#ifndef ENTITY_HANDLER_H
#define ENTITY_HANDLER_H

#include <vector>
#include "ServerEntity.h"
#include"MessageHandler.h"

using namespace std;

class EntityHandler
{
private:
	static vector<ServerEntity*> m_entities;
	static unsigned int m_nextId;
public:
	EntityHandler();
	~EntityHandler();

	void update(float dt);
	void removeAllEntities();

	static void addEntity(ServerEntity *_entity);
	static bool removeEntity(ServerEntity *_entity);

	static vector<ServerEntity*> getEntities();

	static ServerEntity* getClosestEntity(ServerEntity *entity);
	static ServerEntity* getServerEntity(unsigned int id);
};

#endif