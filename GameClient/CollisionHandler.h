#ifndef COLLISION_HANDLER_H
#define COLLISION_HANDLER_H

#include "EntityHandler.h"

//Detect collision and send collision messages to the affected non-static entities
class CollisionHandler
{
private:
	MessageQueue* m_myMessages;

	void addCollision(ServerEntity *_ent1, ServerEntity *_ent2);
public:
	CollisionHandler();
	~CollisionHandler();

	void update();
};

#endif