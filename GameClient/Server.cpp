#include "Server.h"
#include "DelayedDamage.h"

#include <fstream>
Server::Server(MessageHandler *_messageHandler)
{
	this->nrOfPlayers=0;
	this->m_messageHandler = _messageHandler;
	this->m_messageQueue = new MessageQueue();
	this->m_messageHandler->addQueue(this->m_messageQueue);
	this->nextEmptyArrayPos=0;
	DelayedDamage::text = NULL;
	for(int i=0;i<MAXPLAYERS;i++)
	{
		this->m_players[i]=0;
	}
}

Server::~Server()
{
	for(int i = 0; i < MAXPLAYERS; i++)
	{
		if(this->m_players[i])
			delete this->m_players[i];
	}

	delete this->m_messageQueue;
}

bool Server::start(int port)
{
	//if the server cant listen to the port, return
	if(!this->listener.Listen(port))
		return false;
	
	//otherwise, continue by adding the listening socket to the selector and start selector thread
	this->Launch();
	this->selector.Add(this->listener);
		return true;
}

//the selector is blocking, so runs in a thread
void Server::goThroughSelector()
{
	unsigned int itemsInSelector= this->selector.Wait(0.01f);
	sf::Packet packet;

	if(itemsInSelector > 0)
	{
		if(this->isRunning())
		for(unsigned int i =0;i<itemsInSelector;i++)
		{
			//fetches a ready socket from the selector
			sf::SocketTCP sock = this->selector.GetSocketReady(i);
		
			if(sock==this->listener)
			{
				if(this->nrOfPlayers<MAXPLAYERS)
				{
					sf::IPAddress ip;
					sf::SocketTCP incSocket;
					//accept the new socket
					this->listener.Accept(incSocket, &ip);
					cout << "client connected: " << ip.ToString()<<endl;
					//and add it to the selector
					this->selector.Add(incSocket);

					for(int i=0;i<MAXPLAYERS;i++)
					{
						if(this->m_players[i]==0)
						{
							nextEmptyArrayPos=i;
							break;
						}
					}
					Player *p = new Player(nextEmptyArrayPos);
					this->m_players[nextEmptyArrayPos]=p;
					this->clients[nextEmptyArrayPos]=incSocket;
					this->nrOfPlayers++;
				
					this->m_messageHandler->addQueue(p->getMessageQueue());
				}
			}
			//else its a client socket who wants to sent a message
			else
			{
				if (sock.Receive(packet) == sf::Socket::Done)
				{
					// Extract what type of data sent by the client
					unsigned int type;
					packet >> type;

					int socketIndex = 0;

					for(int j = 1; j < MAXPLAYERS; j++)
					{
						if(sock == this->clients[j])
						{
							socketIndex = j;
						}
					}

					//handles the protocols, what should be done if the server recives a MSG, ENT etc
					this->handleClientInData(socketIndex, packet,(NetworkMessage::MESSAGE_TYPE)type);
				}
				else
				{
					// if done wasnt completed, the socket will be removed from the selector
					//if(this->listener.IsValid())
					{
						for(int i=0;i<MAXPLAYERS;i++)
						{
							if(this->clients[i]==sock&&this->m_players[i]!=0)
							{
								this->m_messageHandler->removeQueue(this->m_players[i]->getMessageQueue()->getId());
								this->clients[i].Close();
								delete this->m_players[i];
								this->m_players[i]=0;
								this->nrOfPlayers--;
								this->selector.Remove(sock);
							}
						}
					}
				}
			}
		}
	}
}

void Server::handleMessages()
{
	//Handle incoming messages
	Message *m;

	NetworkRemoveEntityMessage rem;
	NetworkCreateActionMessage cam;
	NetworkCreateActionPositionMessage capm;
	NetworkCreateActionTargetMessage catm;
	NetworkSkillBoughtMessage sbm;
	NetworkRemoveActionTargetMessage rat;
	NetworkSkillUsedMessage sum;
	NetworkInitEntityMessage iem;
	NetworkEntityMessage nem;
	NetworkUpdateEntityHealth nueh;

	RemoveServerEntityMessage *m1;
	CreateActionMessage *m2;
	CreateActionPositionMessage *m3;
	CreateActionTargetMessage *m4;
	SkillBoughtMessage *m5;
	RemoveActionTargetMessage *m6;
	SkillUsedMessage *m7;
	InitEntityMessage *m8;
	UpdateEntityMessage *m9;
	updateEntityHealth *m10;


	while(this->m_messageQueue->incomingQueueEmpty() == false)
	{
		sf::Packet packet;
		m = this->m_messageQueue->pullIncomingMessage();

		switch(m->type)
		{
		case Message::RemoveEntity:
			m1 = (RemoveServerEntityMessage*)m;			
			rem = NetworkRemoveEntityMessage(m1->removedId);
			this->broadcast(rem);
			break;

		case Message::CreateAction:
			m2 = (CreateActionMessage*)m;			
			cam = NetworkCreateActionMessage(m2->actionId, m2->senderId, m2->position);
			this->broadcast(cam);
			break;

		case Message::CreateActionPosition:
			m3 = (CreateActionPositionMessage*)m;			
			capm = NetworkCreateActionPositionMessage(m3->actionId, m3->senderId, m3->position);
			this->broadcast(capm);
			break;

		case Message::CreateActionTarget:
			m4 = (CreateActionTargetMessage*)m;			
			catm = NetworkCreateActionTargetMessage(m4->actionId, m4->senderId, m4->targetId, m4->position);
			this->broadcast(catm);		
			break;

		case Message::SkillBought:
			m5 = (SkillBoughtMessage*)m;
			sbm = NetworkSkillBoughtMessage(m5->actionId, m5->resources);
			packet<<sbm;

			this->m_mutex.Lock();
			if(this->clients[m5->playerId].IsValid())
			this->clients[m5->playerId].Send(packet);
			this->m_mutex.Unlock();

			break;

		case Message::RemoveActionTarget:
			m6 = (RemoveActionTargetMessage*)m;
			rat = NetworkRemoveActionTargetMessage(m6->actionId, m6->targetId);
			this->broadcast(rat);

			break;

		case Message::SkillUsed:
			m7 = (SkillUsedMessage*)m;
			sum = NetworkSkillUsedMessage(m7->actionId, m7->actionIndex, m7->cooldown);
			packet<<sum;

			this->m_mutex.Lock();
			if(this->clients[m7->playerId].IsValid())
			this->clients[m7->playerId].Send(packet);
			this->m_mutex.Unlock();

			break;
			
		case Message::initEntities:
			m8 =(InitEntityMessage*)m;
			iem = NetworkInitEntityMessage(m8->entityType, m8->modelid, m8->weaponType, m8->id,m8->xPos,m8->zPos,m8->yRot,m8->scale,m8->health,m8->sx,m8->sz,m8->ex,m8->ez,m8->movementspeed);
			this->broadcast(iem);
			break;

		case Message::updateEntity:
			m9=(UpdateEntityMessage*)m;
			nem = NetworkEntityMessage(m9->id,m9->xPos,m9->zPos,m9->yRot,m9->sx,m9->sz,m9->ex,m9->ez,m9->movementspeed);
			this->broadcast(nem);
			break;
		case Message::updateEntityHealth:
			m10=(updateEntityHealth*)m;
			nueh = NetworkUpdateEntityHealth(m10->id,m10->health);
			this->broadcast(nueh);
			break;
		}

		delete m;
	}
}

void Server::shutDown()
{
	NetworkDisconnectMessage message = NetworkDisconnectMessage("Server is shutting down");

	for(int i=0;i<MAXPLAYERS;i++)
	{
		sf::Packet packet;
		packet << message;
		if(this->clients[i].IsValid())
		{
			this->clients[i].Send(packet);
			this->clients[i].Close();
		}
	}
	if(this->listener.IsValid())
	{
		this->listener.Close();
	}

	this->Wait();
}

void Server::broadcast(NetworkUpdateEntityHealth networkMessage)
{
	sf::Packet packet;
	packet<<networkMessage;

	this->m_mutex.Lock();

	for(int i=0;i<MAXPLAYERS;i++)
	{
		if(this->clients[i].IsValid())
			this->clients[i].Send(packet);
	}

	this->m_mutex.Unlock();
}

void Server::broadcast(NetworkEntityMessage networkMessage)
{
	sf::Packet packet;
	packet<<networkMessage;

	this->m_mutex.Lock();

	for(int i=0;i<MAXPLAYERS;i++)
	{
		if(this->clients[i].IsValid())
			this->clients[i].Send(packet);
	}

	this->m_mutex.Unlock();
}

void Server::broadcast(NetworkRemoveEntityMessage networkMessage)
{
	sf::Packet packet;
	packet<<networkMessage;

	this->m_mutex.Lock();

	for(int i=0;i<MAXPLAYERS;i++)
	{
		if(this->clients[i].IsValid())
			this->clients[i].Send(packet);
	}

	this->m_mutex.Unlock();
}

void Server::broadcast(NetworkCreateActionMessage networkMessage)
{
	sf::Packet packet;
	packet<<networkMessage;

	this->m_mutex.Lock();

	for(int i=0;i<MAXPLAYERS;i++)
	{
		if(this->clients[i].IsValid())
			this->clients[i].Send(packet);
	}

	this->m_mutex.Unlock();
}

void Server::broadcast(NetworkCreateActionPositionMessage networkMessage)
{
	sf::Packet packet;
	packet<<networkMessage;

	this->m_mutex.Lock();

	for(int i=0;i<MAXPLAYERS;i++)
	{
		if(this->clients[i].IsValid())
			this->clients[i].Send(packet);
	}

	this->m_mutex.Unlock();
}

void Server::broadcast(NetworkCreateActionTargetMessage networkMessage)
{
	sf::Packet packet;
	packet<<networkMessage;

	this->m_mutex.Lock();

	for(int i=0;i<MAXPLAYERS;i++)
	{
		if(this->clients[i].IsValid())
			this->clients[i].Send(packet);
	}

	this->m_mutex.Unlock();
}

void Server::broadcast(NetworkRemoveActionTargetMessage networkMessage)
{
	sf::Packet packet;
	packet<<networkMessage;

	this->m_mutex.Lock();

	for(int i=0;i<MAXPLAYERS;i++)
	{
		if(this->clients[i].IsValid())
			this->clients[i].Send(packet);
	}

	this->m_mutex.Unlock();
}

void Server::broadcast(NetworkStartGameMessage networkMessage)
{
	sf::Packet packet;
	packet<<networkMessage;

	this->m_mutex.Lock();

	for(int i=0;i<MAXPLAYERS;i++)
	{
		if(this->clients[i].IsValid())
			this->clients[i].Send(packet);
	}
	
	this->m_mutex.Unlock();
}

void Server::broadcast(NetworkHeroSelectedMessage networkMessage)
{
	sf::Packet packet;
	packet<<networkMessage;

	this->m_mutex.Lock();

	for(int i=0;i<MAXPLAYERS;i++)
	{
		if(this->clients[i].IsValid())
			this->clients[i].Send(packet);
	}

	this->m_mutex.Unlock();
}

void Server::broadcast(NetworkSkillUsedMessage networkMessage)
{
	sf::Packet packet;
	packet<<networkMessage;

	this->m_mutex.Lock();

	for(int i=0;i<MAXPLAYERS;i++)
	{
		if(this->clients[i].IsValid())
			this->clients[i].Send(packet);
	}

	this->m_mutex.Unlock();
}

void Server::broadcast(NetworkSkillBoughtMessage networkMessage)
{
	sf::Packet packet;
	packet<<networkMessage;

	this->m_mutex.Lock();

	for(int i=0;i<MAXPLAYERS;i++)
	{
		if(this->clients[i].IsValid())
			this->clients[i].Send(packet);
	}

	this->m_mutex.Unlock();
}


void Server::broadcast(NetworkInitEntityMessage networkMessage)
{
	sf::Packet packet;
	packet<<networkMessage;

	this->m_mutex.Lock();

	for(int i=0;i<MAXPLAYERS;i++)
	{
		if(this->clients[i].IsValid())
			this->clients[i].Send(packet);
	}

	this->m_mutex.Unlock();
}
void Server::broadcast(NetworkHeroInitMessage networkMessage)
{
	sf::Packet packet;

	this->m_mutex.Lock();

	for(int i=0;i<MAXPLAYERS;i++)
	{
		networkMessage.setYourId(i);
		packet<<networkMessage;
		if(this->clients[i].IsValid())
			this->clients[i].Send(packet);
	}

	this->m_mutex.Unlock();
}

void Server::Run()
{
	__int64 cntsPerSec = 0;
	QueryPerformanceFrequency((LARGE_INTEGER*)&cntsPerSec);
	float secsPerCnt = 1.0f / (float)cntsPerSec;

	__int64 prevTimeStamp = 0;
	QueryPerformanceCounter((LARGE_INTEGER*)&prevTimeStamp);

	while(this->listener.IsValid())
	{
		__int64 currTimeStamp = 0;
		QueryPerformanceCounter((LARGE_INTEGER*)&currTimeStamp);
		float dt = (currTimeStamp - prevTimeStamp) * secsPerCnt;
		prevTimeStamp = currTimeStamp;

		this->goThroughSelector();
		this->handleMessages();

		for(int i = 0; i < MAXPLAYERS; i++)
		{
			if(this->clients[i].IsValid())
				this->m_players[i]->update(dt);
		}
	}
}

bool Server::isRunning()
{
	return this->listener.IsValid();
}

bool Server::handleClientInData(int socketIndex, sf::Packet packet, NetworkMessage::MESSAGE_TYPE type)
{
	bool protFound=false;

	NetworkUseActionMessage ua;
	NetworkUseActionPositionMessage uap;
	NetworkUseActionTargetMessage uat;
	NetworkBuySkillMessage bs;
	NetworkReadyMessage nrm;
	NetworkSelectHeroMessage nshm;

	switch(type)
	{
	case NetworkMessage::MESSAGE_TYPE::UseAction:		
		packet >> ua;
		this->m_mutex.Lock();
		this->m_players[socketIndex]->handleUseActionMessage(ua);
		this->m_mutex.Unlock();
		break;

	case NetworkMessage::MESSAGE_TYPE::UseActionPos:
		packet >> uap;
		this->m_mutex.Lock();
		this->m_players[socketIndex]->handleUseActionPositionMessage(uap);
		this->m_mutex.Unlock();
		break;

	case NetworkMessage::MESSAGE_TYPE::UseActionTarget:
		packet >> uat;
		this->m_mutex.Lock();
		this->m_players[socketIndex]->handleUseActionTargetMessage(uat);
		this->m_mutex.Unlock();
		break;

	case NetworkMessage::MESSAGE_TYPE::BuySkill:
		packet >> bs;
		this->m_mutex.Lock();
		this->m_players[socketIndex]->handleBuySkillMessage(bs);
		this->m_mutex.Unlock();
		break;

	case NetworkMessage::MESSAGE_TYPE::SelectHero:
		packet >> nshm;
		this->m_mutex.Lock();
		this->m_players[socketIndex]->handleSelectHeroMessage(nshm);
		this->m_mutex.Unlock();
		break;

	case NetworkMessage::MESSAGE_TYPE::Ready:
		packet >> nrm;
		this->m_mutex.Lock();
		this->m_players[socketIndex]->handleReadyMessage(nrm);
		this->m_mutex.Unlock();
		break;
	case NetworkMessage::Disconnect:
		this->selector.Remove(this->clients[socketIndex]);
		this->clients[socketIndex].Close();
		this->m_messageHandler->removeQueue(this->m_players[socketIndex]->getMessageQueue()->getId());
		delete this->m_players[socketIndex];
		this->m_players[socketIndex]=0;
		this->nrOfPlayers--;
		break;
	case NetworkMessage::setPlayerName:
		string pname;
		packet >> pname;
		Statistics::getStatisticsPlayer(socketIndex).setPlayerName(pname);
		break;
	}

	return protFound;
}

vector<Player*> Server::getPlayers()
{
	vector<Player*> p;
	for(int i=0;i<MAXPLAYERS;i++)
	{
		if(this->m_players[i]!=0)
			p.push_back(this->m_players[i]);
	}
	return p;
}