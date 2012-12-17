#include "ServerThread.h"

ServerThread::ServerThread() : sf::Thread()
{
	this->m_messageHandler = new MessageHandler();
	this->m_network = new Server(this->m_messageHandler);
	this->m_entities.push_back(new ServerEntity());
	this->m_running = false;
}

ServerThread::~ServerThread()
{
	this->m_running = false;
	this->Wait();

	delete this->m_messageHandler;

	this->m_network->shutDown();
	delete this->m_network;

	for(int i = 0; i < this->m_entities.size(); i++)
	{
		delete this->m_entities[i];
	}
}

void ServerThread::Run()
{
	this->m_running = true;
	this->m_network->start(1337);
	EntityMessage e = EntityMessage();

	this->m_messageHandler->addQueue(this->m_entities[0]->getMessageQueue());

	while(this->m_running == true)
	{
		//Update the entities
		this->m_messageHandler->update();
		this->m_entities[0]->update();

		//Send information to the clients
		e = this->m_entities[0]->getUpdate();
		this->m_network->broadcast(e);
	}
}