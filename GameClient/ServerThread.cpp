#include "ServerThread.h"

ServerThread::ServerThread() : sf::Thread()
{
	//this->m_messageHandler = new MessageHandler();
	this->m_network = new Server(/*this->m_messageHandler*/);
	this->m_entityHandler = new EntityHandler();
	this->m_running = false;
}

ServerThread::~ServerThread()
{
	this->m_running = false;
	this->Wait();

	//delete this->m_messageHandler;
	this->m_network->shutDown();
	delete this->m_network;

	this->m_entityHandler->removeAllEntities();
	delete this->m_entityHandler;
}

void ServerThread::Run()
{
	vector<ServerEntity*> entities;
	this->m_running = true;
	this->m_network->start(1337);

	while(this->m_running == true)
	{
		//Update the entities
		//this->m_messageHandler->update();
		this->m_entityHandler->update();

		entities = this->m_entityHandler->getEntities();

		for(int i = 0; i < entities.size(); i++)
		{
			this->m_network->broadcast(entities[i]->getUpdate());
		}
	}
}