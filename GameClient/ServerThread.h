#ifndef SERVER_THREAD_H
#define SERVER_THREAD_H

#include <SFML\System.hpp>
#include "NetworkServer.h"

class ServerThread : public sf::Thread
{
private:
	NetworkServer *m_network;

	void Run();
public:
	ServerThread();
};

#endif