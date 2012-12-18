#pragma once

#include "EntityHandler.h"
#include <SFML\System.hpp>
#include "Server.h"
#include "MessageHandler.h"
#include "Player.h"
#include "ServerEntity.h"

class ServerThread : public sf::Thread
{
private:
	enum State { LOBBY, GAME, END, EXIT };

	Server *m_network;
	MessageHandler *m_messageHandler;
	EntityHandler *m_entityHandler;

	MessageQueue *m_messageQueue;
	State m_state;

	void Run();
public:
	 ServerThread();
	 ~ServerThread();
};