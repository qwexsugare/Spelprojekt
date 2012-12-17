#ifndef SERVER_THREAD_H
#define SERVER_THREAD_H

#include <SFML\System.hpp>
#include "Server.h"
#include "MessageHandler.h"
#include "Player.h"

class ServerThread : public sf::Thread
{
private:
	Server *m_network;

	void Run();
public:
	ServerThread();
};

#endif