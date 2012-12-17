#pragma once

#include "EntityHandler.h"
#include <SFML\System.hpp>
#include "Server.h"
//#include "MessageHandler.h"
#include "Player.h"
#include "ServerEntity.h"

class ServerThread : public sf::Thread
{
private:
	Server *m_network;
	//MessageHandler *m_messageHandler;
	EntityHandler *m_entityHandler;

	bool m_running;

	void Run();
public:
	 ServerThread();
	 ~ServerThread();
};