#include "ServerThread.h"
#include "TowerPlacer.h"
#include "NetworkHeroInitMessage.h"

ServerThread::ServerThread(int _port, string _mapName) : sf::Thread()
{
	this->mapName=_mapName;
	this->m_statistics = Statistics();
	this->m_port = _port;
	this->m_messageHandler = new MessageHandler();
	this->m_messageQueue = new MessageQueue();
	this->m_messageHandler->addQueue(this->m_messageQueue);
	this->m_network = new Server(this->m_messageHandler);
	this->m_network->setMapName(this->mapName);
	this->m_entityHandler = new EntityHandler(this->m_messageHandler);
	this->m_mapHandler = new MapHandler();
	this->m_messageHandler->addQueue(this->m_mapHandler->getMessageQueue());
	this->m_mapHandler->loadMap(_mapName);
	// I crapped in ass
	this->m_network->broadcast(NetworkEntityMessage());
	TowerPlacer::init();
}

ServerThread::~ServerThread()
{
	if(this->m_state == State::GAME)
	{
		this->m_state = State::DEFEAT;
	}
	else
	{
		this->m_state = State::EXIT;
	}

	this->Wait();

	this->m_network->shutDown();
	delete this->m_network;
	delete this->m_mapHandler;
	delete this->m_messageQueue;
	delete this->m_messageHandler;
	this->m_entityHandler->removeAllEntities();
	delete this->m_entityHandler;
	TowerPlacer::release();
	Statistics::saveToFile("STATISTICSlastgame.txt");
}

void ServerThread::Run()
{
	Text* fpsText = g_graphicsEngine->createText("", INT2(5, 40), 20, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	float fpsTimer = 0.0f;

	__int64 cntsPerSec = 0;
	QueryPerformanceFrequency((LARGE_INTEGER*)&cntsPerSec);
	float secsPerCnt = 1.0f / (float)cntsPerSec;

	__int64 prevTimeStamp = 0;
	QueryPerformanceCounter((LARGE_INTEGER*)&prevTimeStamp);

	this->m_state = State::LOBBY;
	this->m_network->start(this->m_port);

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
					if(m->senderId == players[i]->getMessageQueue()->getId())
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
			else if(m->type == Message::Type::JoinedGame)
			{
				for(int i = 0; i < players.size(); i++)
				{
					if(players[i]->hasChosenHero() == true)
					{
						this->m_network->broadcast(NetworkHeroSelectedMessage(players[i]->getSelectedHeroType(), players[i]->getId()));
					}
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
				this->m_state = State::LOADING;
				m_network->broadcast(NetworkStartGameMessage(this->mapName));
				
				
				vector<unsigned int> ids;
				vector<Hero::HERO_TYPE> heroTypes;
				for(int i = 0; i < players.size(); i++)
				{
					players[i]->spawnHero(this->m_mapHandler->getPlayerPosition(players[i]->getSelectedHeroType()));
					players[i]->addResources(this->m_mapHandler->getDemonCoins());
					ids.push_back(players[i]->getHero()->getId());
					heroTypes.push_back(players[i]->getHero()->getHeroType());
					players[i]->setReady(false);
				}

				for(int i = 0; i < heroTypes.size(); i++)
				{
					Statistics::getStatisticsPlayer(i).setId(ids[i]);
					Statistics::getStatisticsPlayer(i).setHeroType((StatisticsPlayer::HERO_TYPE)(heroTypes[i]));
				}

				m_network->broadcast(NetworkHeroInitMessage(ids, heroTypes));
			}
		}
	}
	else if(this->m_state == State::LOADING)
	{
		vector<Player*> players = this->m_network->getPlayers();
		bool ready = false;



		for(int i = 0; i < players.size(); i++)
		{
			if(players[i]->getReady() == true)
			{
				ready = true;
			}
		}

		if(ready == true)
		{
			this->m_network->broadcast(NetworkCreateActionMessage(Skill::LIVES_REMAINING, this->m_mapHandler->getLivesLeft(), FLOAT3()));
			this->m_state = State::GAME;
			this->m_network->broadcast(NetworkStartGameMessage("Trolololol"));
		}
	}
	else if(this->m_state == State::GAME)
	{
		MapHandler::State s = this->m_mapHandler->getState();

		//Check if the map is finished
		if(s == MapHandler::VICTORY)
		{
			this->m_state = ServerThread::VICTORY;
		}
		if(s == MapHandler::DEFEAT)
		{
			this->m_state = ServerThread::DEFEAT;
		}


		//Update the map and units on it
		this->m_entityHandler->update(dt);
		this->m_mapHandler->update(dt);

		entities = this->m_entityHandler->getEntities();

		//for(int i = 0; i < entities.size(); i++)
		//{
		//	if(entities[i]->getVisible() == true && (entities[i]->getType() != ServerEntity::Type::StaticType && entities[i]->getType() != ServerEntity::Type::HeroType && entities[i]->getType() != ServerEntity::Type::TowerType && entities[i]->getType() != ServerEntity::Type::EnemyType))
		//	{
		//		this->m_network->broadcast(entities[i]->getUpdate());
		//	}
		//}

		while(this->m_messageQueue->incomingQueueEmpty() == false)
		{
			Message *m = this->m_messageQueue->pullIncomingMessage();

			if(m->type == Message::Type::EnemyDied)
			{
				EnemyDiedMessage *edm = (EnemyDiedMessage*)m;

				for(int i = 0; i < this->m_network->getPlayers().size(); i++)
				{
					this->m_network->getPlayers()[i]->addResources(edm->resources);
					

					if(this->m_network->getPlayers()[i]->getHero()->getId() == edm->killerId)
					{
						Statistics::getStatisticsPlayer(this->m_network->getPlayers()[i]->getId()).increaseDeamonsKilled();
					}
				}
			}

			if(m->type == Message::Type::EnemyReachedGoal)
			{
				EnemyReachedGoalMessage *edm = (EnemyReachedGoalMessage*)m;
				ServerEntity *e = EntityHandler::getServerEntity((edm->enemyId));
				this->m_mapHandler->enemyDied();
				this->m_messageQueue->pushOutgoingMessage(new CreateActionTargetMessage(Skill::CHURCH_REALLY_PENETRATED, edm->enemyId, this->m_mapHandler->getLivesLeft(), edm->position));
			}

			delete m;
		}
	}
	if(this->m_state == State::VICTORY)
	{
		vector<StatisticsPlayer> playerStatistics;

		for(int i = 0; i < EntityHandler::getEntitiesByType(ServerEntity::HeroType).size(); i++)
		{
			playerStatistics.push_back(Statistics::getStatisticsPlayer(i));
		}

		m_network->broadcast(NetworkEndGameMessage(true, Statistics::getTimePlayed(), Statistics::getIsAtWave(), Statistics::getStartLife(), playerStatistics));
		Statistics::resetStatistics();
		this->m_state = ServerThread::EXIT;
	}
	else if(this->m_state == State::DEFEAT)
	{
		vector<StatisticsPlayer> playerStatistics;

		for(int i = 0; i < EntityHandler::getEntitiesByType(ServerEntity::HeroType).size(); i++)
		{
			playerStatistics.push_back(Statistics::getStatisticsPlayer(i));
		}

		m_network->broadcast(NetworkEndGameMessage(false, Statistics::getTimePlayed(), Statistics::getIsAtWave(), Statistics::getStartLife(), playerStatistics));

		this->m_state = ServerThread::EXIT;
	}
}