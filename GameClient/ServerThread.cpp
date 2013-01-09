#include "ServerThread.h"

ServerThread::ServerThread() : sf::Thread()
{
	this->m_messageHandler = new MessageHandler();
	this->m_messageQueue = new MessageQueue();
	this->m_messageHandler->addQueue(this->m_messageQueue);
	this->m_network = new Server(this->m_messageHandler);
	this->m_entityHandler = new EntityHandler(this->m_messageHandler);
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
	__int64 cntsPerSec = 0;
	QueryPerformanceFrequency((LARGE_INTEGER*)&cntsPerSec);
	float secsPerCnt = 1.0f / (float)cntsPerSec;

	__int64 prevTimeStamp = 0;
	QueryPerformanceCounter((LARGE_INTEGER*)&prevTimeStamp);

	//this->m_state = State::LOBBY;
	this->m_state = State::LOBBY;
	this->m_network->start(1338);

	while(this->m_state != State::EXIT)
	{
		__int64 currTimeStamp = 0;
		QueryPerformanceCounter((LARGE_INTEGER*)&currTimeStamp);
		float dt = (currTimeStamp - prevTimeStamp) * secsPerCnt;
		prevTimeStamp = currTimeStamp;

		this->update(dt);
	}
}

void ServerThread::update(float dt)
{
	vector<ServerEntity*> entities;
	this->m_messageHandler->update();

	if(this->m_state == State::LOBBY)
	{
		//Wait for all players to become ready, change hero when needed	
		Message *m;

		while(this->m_messageQueue->incomingQueueEmpty() == false)
		{
			m = this->m_messageQueue->pullIncomingMessage();

			if(m->type == Message::Type::Start)
			{
				vector<Player*> players = this->m_network->getPlayers();
				bool start = true;

				for(int i = 0; i < players.size(); i++)
				{
					if(players[i]->getReady() == false)
					{
						i = players.size();
						start = false;
					}

					if(start == true)
					{
						this->m_state = State::GAME;
					}
				}
			}

			delete m;
		}
	}

	if(this->m_state == State::GAME)
	{
		//Check if the map is finished

		//Update the map and units on it
		this->m_entityHandler->update(dt);

		entities = this->m_entityHandler->getEntities();

		for(int i = 0; i < entities.size(); i++)
		{
			this->m_network->broadcast(entities[i]->getUpdate());
		}
	}

	if(this->m_state == State::END)
	{
		//Wait for the server to be shut down
	}
}