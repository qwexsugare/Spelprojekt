#ifndef ENTITY_HANDLER_H
#define ENTITY_HANDLER_H

#include <vector>
#include "ServerEntity.h"
//#include"MessageHandler.h"

using namespace std;

class EntityHandler
{
private:
	//MessageQueue *m_messageQueue;
	//MessageHandler *m_messageHandler;
	static vector<ServerEntity*> m_entities;
	static unsigned int m_nextId;
public:
	EntityHandler();
	//EntityHandler(/*MessageHandler* _messageHandler*/);
	~EntityHandler();

	void update();
	void removeAllEntities();

	void addEntity(ServerEntity *_entity);
	bool removeEntity(ServerEntity *_entity);

	vector<ServerEntity*> getEntities();
};

#endif