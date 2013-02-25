#include "ServerThread.h"
#include "TowerPlacer.h"
#include "NetworkHeroInitMessage.h"

ServerThread::ServerThread(int _port) : sf::Thread()
{
	this->m_port = _port;
	this->m_messageHandler = new MessageHandler();
	this->m_messageQueue = new MessageQueue();
	this->m_messageHandler->addQueue(this->m_messageQueue);
	this->m_network = new Server(this->m_messageHandler);
	this->m_entityHandler = new EntityHandler(this->m_messageHandler);
	this->m_mapHandler = new MapHandler();
	this->m_mapHandler->loadMap("maps/levelone/levelone.txt");
	// I crapped in ass
	this->m_network->broadcast(NetworkEntityMessage());
	TowerPlacer::init();
}

ServerThread::~ServerThread()
{
	this->m_state = State::EXIT;
	this->Wait();

	this->m_network->shutDown();
	delete this->m_network;
	delete this->m_mapHandler;
	delete this->m_messageQueue;
	delete this->m_messageHandler;
	this->m_entityHandler->removeAllEntities();
	delete this->m_entityHandler;
	TowerPlacer::release();
}

void ServerThread::Run()
{
	Text* fpsText = g_graphicsEngine->createText("", INT2(5, 20), 20, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	float fpsTimer = 0.0f;

	__int64 cntsPerSec = 0;
	QueryPerformanceFrequency((LARGE_INTEGER*)&cntsPerSec);
	float secsPerCnt = 1.0f / (float)cntsPerSec;

	__int64 prevTimeStamp = 0;
	QueryPerformanceCounter((LARGE_INTEGER*)&prevTimeStamp);

	this->m_state = State::LOBBY;
	this->m_network->start(this->m_port);

	EntityHandler::addEntity(new Tower(FLOAT3(60.0f, 0.0f, 50.0f)));

	while(this->m_state != State::EXIT)
	{
		__int64 currTimeStamp = 0;
		QueryPerformanceCounter((LARGE_INTEGER*)&currTimeStamp);
		float dt = (currTimeStamp - prevTimeStamp) * secsPerCnt;
		prevTimeStamp = currTimeStamp;

		fpsTimer = fpsTimer + dt;

		if(fpsTimer > 1.0f)
		{
			stringstream ss;
			ss << "Server fps:" << 1.0f / dt << " Entities: " << EntityHandler::getEntities().size();
			fpsTimer = 0.0f;
			fpsText->setString(ss.str());
		}

		this->update(dt);

		//if(dt < 0.015f)
		//{
		//	sf::Sleep(0.015f - dt);
		//}
	}
}

void ServerThread::update(float dt)
{
	vector<ServerEntity*> entities;
	this->m_messageHandler->update();

	if(this->m_state == State::LOBBY)
	{
		vector<Player*> players = this->m_network->getPlayers();

		while(this->m_messageQueue->incomingQueueEmpty() == false)
		{
			Message *m = this->m_messageQueue->pullIncomingMessage();

			if(m->type == Message::Type::SelectHero)
			{
				int senderIndex = -1;
				bool okToSelect = true;
				for(int i = 0; i < players.size(); i++)
				{
					if(m->senderId == players[i]->getId())
					{
						senderIndex = i;
					}
					else if(players[i]->hasChosenHero())
					{
						if(players[i]->getSelectedHeroType() == ((SelectHeroMessage*)m)->heroId)
						{
							okToSelect = false;
						}
					}
				}

				if(okToSelect)
				{
					m_network->broadcast(NetworkHeroSelectedMessage(((SelectHeroMessage*)m)->heroId, senderIndex));
					players[senderIndex]->assignHero(Hero::HERO_TYPE(((SelectHeroMessage*)m)->heroId), Hero::WEAPON_TYPE(((SelectHeroMessage*)m)->weaponId));
				}
			}

			delete m;
		}
		if(players.empty() == false)//Wait for all players to become ready
		{
			bool start = true;

			for(int i = 0; i < players.size(); i++)
			{
				if(!players[i]->hasChosenHero() || players[i]->getReady() == false)
				{
					i = players.size();
					start = false;
				}
			}

			if(start == true)
			{
				this->m_state = State::GAME;
				m_network->broadcast(NetworkStartGameMessage());
				
				vector<unsigned int> ids;
				vector<Hero::HERO_TYPE> heroTypes;
				for(int i = 0; i < players.size(); i++)
				{
					players[i]->spawnHero();
					ids.push_back(players[i]->getHero()->getId());
					heroTypes.push_back(players[i]->getHero()->getHeroType());
				}

				m_network->broadcast(NetworkHeroInitMessage(ids, heroTypes));
			}
		}
	}
	else if(this->m_state == State::GAME)
	{
		MapHandler::State s = this->m_mapHandler->getState();

		//Check if the map is finished
		if(s == MapHandler::VICTORY)
		{
			//this->m_state = ServerThread::VICTORY;
		}
		if(s == MapHandler::DEFEAT)
		{
			//this->m_state = ServerThread::DEFEAT;
		}


		//Update the map and units on it
		this->m_entityHandler->update(dt);
		this->m_mapHandler->update(dt);

		entities = this->m_entityHandler->getEntities();

		for(int i = 0; i < entities.size(); i++)
		{
			if(entities[i]->getVisible() == true && (entities[i]->getType() != ServerEntity::Type::StaticType && entities[i]->getType() != ServerEntity::Type::HeroType && entities[i]->getType() != ServerEntity::Type::TowerType && entities[i]->getType() != ServerEntity::Type::EnemyType))
			{
				this->m_network->broadcast(entities[i]->getUpdate());
			}
		}

		while(this->m_messageQueue->incomingQueueEmpty() == false)
		{
			Message *m = this->m_messageQueue->pullIncomingMessage();

			if(m->type == Message::Type::EnemyDied)
			{
				EnemyDiedMessage *edm = (EnemyDiedMessage*)m;

				for(int i = 0; i < this->m_network->getPlayers().size(); i++)
				{
					if(this->m_network->getPlayers()[i]->getHero()->getId() == edm->killerId)
					{
						this->m_network->getPlayers()[i]->addResources(edm->resources);
						i = 5;
					}
				}
			}

			if(m->type == Message::Type::EnemyReachedGoal)
			{
				EnemyReachedGoalMessage *edm = (EnemyReachedGoalMessage*)m;
				this->m_mapHandler->enemyDied();
			}

			delete m;
		}
	}
	if(this->m_state == State::VICTORY)
	{
		g_graphicsEngine->createText("VICTORY!", INT2(300, 200), 40 ,D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		this->m_state = ServerThread::EXIT;
	}
	else if(this->m_state == State::DEFEAT)
	{

	}
}