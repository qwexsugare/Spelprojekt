#ifndef CLIENT_ENTITY_HANDLER_H
#define CLIENT_ENTITY_HANDLER_H

#include <vector>
#include "Entity.h"

using namespace std;

class ClientEntityHandler
{
private:
	static vector<Entity*> m_entities;
public:
	ClientEntityHandler();
	~ClientEntityHandler();

	void removeAllEntities();

	static void addEntity(Entity *_entity);
	static bool removeEntity(Entity *_entity);

	static vector<Entity*> getEntities();

	static Entity* getEntity(unsigned int id);
	
	static vector<Entity*> getAllEnemies();
	static int getNrOfEnemies();
	static vector<Entity*> getAllHeroes();
	static vector<Entity*> getAllStaticObjects();
};

#endif