#ifndef SERVER_THREAD_H
#define SERVER_THREAD_H

#include <SFML\System.hpp>
#include "Server.h"
#include "MessageHandler.h"
#include "Player.h"
#include "ServerEntity.h"
#include "MessageHandler.h"

class ServerThread : public sf::Thread
{
private:
	Server *m_network;
	MessageHandler *m_messageHandler;

	vector<ServerEntity*> m_entities;
	bool m_running;

	void Run();
public:
	ServerThread();
	~ServerThread();
};

#endif