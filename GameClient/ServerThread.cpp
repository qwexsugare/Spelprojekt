#include "ServerThread.h"

ServerThread::ServerThread() : sf::Thread()
{
	this->m_messageHandler = new MessageHandler();
	this->m_messageQueue = new MessageQueue();
	this->m_network = new Server();
	this->m_entityHandler = new EntityHandler();

	this->m_messageHandler->addQueue(this->m_messageQueue);
}

ServerThread::~ServerThread()
{
	this->m_state = State::EXIT;
	this->Wait();

	delete this->m_messageQueue;
	delete this->m_messageHandler;
	this->m_network->shutDown();
	delete this->m_network;

	this->m_entityHandler->removeAllEntities();
	delete this->m_entityHandler;
}

void ServerThread::Run()
{
	vector<ServerEntity*> entities;
	//this->m_state = State::LOBBY;
	this->m_state = State::GAME;
	this->m_network->start(1337);

	while(this->m_state == State::LOBBY)
	{
		//Wait for all players to become ready, change hero when needed
	}

	while(this->m_state == State::GAME)
	{
		//Update the map and units on it
		this->m_entityHandler->update();

		entities = this->m_entityHandler->getEntities();

		for(int i = 0; i < entities.size(); i++)
		{
			this->m_network->broadcast(entities[i]->getUpdate());
		}
	}

	while(this->m_state == State::END)
	{
		//Wait for the server to be shut down
	}
}