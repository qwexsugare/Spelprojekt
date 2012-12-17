#include "ServerThread.h"

ServerThread::ServerThread() : sf::Thread()
{
	this->m_network = new Server();

}

void ServerThread::Run()
{
	this->m_network->start(1337);
	EntityMessage e = EntityMessage();
	vector<Player*> players;

	while(this->m_network->isRunning())
	{
		players = this->m_network->getPlayers();

		for(int i = 0; i < players.size(); i++)
		{
			e = players[i]->getUpdate();
			this->m_network->broadcast(e);
		}
		//Sleep(100);
	}
}