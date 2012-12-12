#include "ServerThread.h"

ServerThread::ServerThread() : sf::Thread()
{
	this->m_network = new Server();

}

void ServerThread::Run()
{
	this->m_network->start(1337);
	EntityMessage e = EntityMessage();
	FLOAT3 pos = FLOAT3(0.0f, 0.0f, 0.0f);
	e.setPosition(pos);

	while(true)
	{
		pos.x = pos.x + 0.00001f;
		e.setPosition(pos);
		this->m_network->broadcast(e);
		//Sleep(100);

	}
}