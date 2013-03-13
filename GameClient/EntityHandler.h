#ifndef ENTITY_HANDLER_H
#define ENTITY_HANDLER_H

#include <vector>
#include <SFML\System.hpp>
#include "ServerEntity.h"
#include "UnitEntity.h"
#include "MessageHandler.h"
#include "ServerQuadTree.h"

using namespace std;

class EntityHandler
{
private:
	static sf::Mutex m_mutex;
	static vector<ServerEntity*> m_entities;
	static ServerQuadTree* m_quadtree;
	static unsigned int m_nextId;

	static MessageQueue *m_messageQueue;
	static MessageHandler *m_messageHandler;
public:
	EntityHandler();
	EntityHandler(MessageHandler* _messageHandler);
	~EntityHandler();

	void update(float dt);
	void removeAllEntities();

	static void addEntity(ServerEntity *_entity);
	static bool removeEntity(ServerEntity *_entity);
	
	static vector<ServerEntity*> getEntities();
	static vector<ServerEntity*> getEntitiesByType(ServerEntity::Type _type);

	static ServerEntity* getClosestEntity(ServerEntity *entity);
	static ServerEntity* getClosestEntityByType(ServerEntity* _entity, UnitEntity::Type _type);
	static ServerEntity* getClosestStatic(ServerEntity *entity);
	static ServerEntity* getClosestStaticWithExtents(FLOAT3 _pos);
	
	static ServerEntity* getClosestSuperStatic(FLOAT3 _pos);
	static ServerEntity* getServerEntity(unsigned int id);
	
	static vector<ServerEntity*> getAllEnemies();
	static int getNrOfEnemies();
	static vector<ServerEntity*> getAllHeroes();

	static unsigned int getId();
	static void initQuadTree(FLOAT2 _extents);
	static bool intersects(const BoundingSphere& _bs);
	static bool intersects(const BoundingOrientedBox& _obb);
};

#endif