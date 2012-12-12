#include "ServerThread.h"

ServerThread::ServerThread() : sf::Thread()
{
	this->m_network = new NetworkServer();

}

void ServerThread::Run()
{
	/*this->m_network->start(1337);

	while(this->m_network->isRunning() == true)
	{
		this->m_network->broadcast("LOLOLOLOLOLOLOL");
		Sleep(1000);
	}*/
}