#pragma once

#include "EntityHandler.h"
#include <SFML\System.hpp>
#include "Server.h"
#include "MessageHandler.h"
#include "Player.h"
#include "Enemy.h"
#include "ServerEntity.h"
#include "MapHandler.h"
#include "CollisionHandler.h"
#include "Tower.h"

class ServerThread : public sf::Thread
{
private:
	enum State { LOBBY, GAME, END, EXIT };

	Server *m_network;
	MessageHandler *m_messageHandler;
	EntityHandler *m_entityHandler;
	MapHandler m_mapHandler;
	CollisionHandler *m_collisionHandler;

	MessageQueue *m_messageQueue;
	State m_state;

	void Run();
	void update(float dt);
public:
	 ServerThread();
	 ~ServerThread();
};