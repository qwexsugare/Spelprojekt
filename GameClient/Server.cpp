#include "Server.h"

Server::Server(MessageHandler *_messageHandler)
{
	this->clientArrPos=0;
	this->m_messageHandler = _messageHandler;
	this->m_messageQueue = new MessageQueue();
	this->m_messageHandler->addQueue(this->m_messageQueue);
}

Server::~Server()
{
	for(int i = 0; i < this->m_players.size(); i++)
	{
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
	unsigned int itemsInSelector= this->selector.Wait();
	
	if(this->isRunning())
	for(unsigned int i =0;i<itemsInSelector;i++)
	{
		//fetches a ready socket from the selector
		sf::SocketTCP sock = this->selector.GetSocketReady(i);
		
		if(sock==this->listener)
		{
			sf::IPAddress ip;
			sf::SocketTCP incSocket;
			//accept the new socket
			this->listener.Accept(incSocket, &ip);
			cout << "client connected: " << ip.ToString()<<endl;
			//and add it to the selector
			this->selector.Add(incSocket);
			this->clients[this->clientArrPos++]=incSocket;

			Player *p = new Player(this->m_players.size());
			this->m_players.push_back(p);
			this->m_messageHandler->addQueue(p->getMessageQueue());
		}
		//else its a client socket who wants to sent a message
		else
		{
			sf::Packet packet;
			if (sock.Receive(packet) == sf::Socket::Done)
			{
				// Extract what type of data sent by the client
				string prot;
				packet >> prot;

				int socketIndex = 0;

				for(int j = 1; j < this->clientArrPos; j++)
				{
					if(sock == this->clients[j])
					{
						socketIndex = j;
					}
				}

				//handles the protocols, what should be done if the server recives a MSG, ENT etc
				this->handleClientInData(socketIndex, packet,prot);
			}
			else
			{
				// if done wasnt completed, the socket will be removed from the selector
				if(this->listener.IsValid())
				{
					this->selector.Remove(sock);
					cout<<"A client disconnected!"<<endl;
					for(int i=0;i<this->clientArrPos;i++)
					{
						if(this->clients[i]==sock)
						{
							this->clients[i]=this->clients[--this->clientArrPos];
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

	while(this->m_messageQueue->incomingQueueEmpty() == false)
	{
		m = this->m_messageQueue->pullIncomingMessage();

		if(m->type == Message::RemoveEntity)
		{
			RemoveServerEntityMessage *rsem = (RemoveServerEntityMessage*)m;			
			RemoveEntityMessage rem = RemoveEntityMessage(rsem->removedId);
			this->broadcast(rem);
		}

		delete m;
	}
}

void Server::shutDown()
{


	for(int i=0;i<this->clientArrPos;i++)
	{
		sf::Packet msg;
		msg << "disconnect";
		if(this->clients[i].IsValid())
		{
			this->clients[i].Send(msg);
			this->clients[i].Close();
		}
	}
	if(this->listener.IsValid())
	{
		this->listener.Close();
	}

	this->Wait();
}

void Server::broadcast(string msg)
{
	sf::Packet packet;
	packet<<msg;

	this->m_mutex.Lock();

	for(int i=0;i<this->clientArrPos;i++)
	{
		this->clients[i].Send(packet);
	}

	this->m_mutex.Unlock();
}

void Server::broadcast(EntityMessage ent)
{
	sf::Packet packet;
	packet<<ent;

	this->m_mutex.Lock();

	for(int i=0;i<this->clientArrPos;i++)
	{
		this->clients[i].Send(packet);
	}

	this->m_mutex.Unlock();
}

void Server::broadcast(Msg msg)
{
	sf::Packet packet;
	packet<<msg;

	this->m_mutex.Lock();

	for(int i=0;i<this->clientArrPos;i++)
	{
		this->clients[i].Send(packet);
	}

	this->m_mutex.Unlock();
}

void Server::broadcast(RemoveEntityMessage rem)
{
	sf::Packet packet;
	packet<<rem;

	this->m_mutex.Lock();

	for(int i=0;i<this->clientArrPos;i++)
	{
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

		for(int i = 0; i < this->m_players.size(); i++)
		{
			this->m_players[i]->update(dt);
		}
	}
}

bool Server::isRunning()
{
	return this->listener.IsValid();
}

bool Server::handleClientInData(int socketIndex, sf::Packet packet, string prot)
{
	bool protFound=false;

	if(prot=="ENT")
	{
		EntityMessage ent;
		packet >> ent;
		this->m_mutex.Lock();

		this->m_players[socketIndex]->handleEntityMessage(ent);

		this->m_mutex.Unlock();

		protFound=true;
	}
	else if(prot=="MSG")
	{
		Msg msg;
		packet >> msg;
		this->m_mutex.Lock();

		this->m_players[socketIndex]->handleMsgMessage(msg);

		this->m_mutex.Unlock();
		protFound=true;
	}
	else if(prot=="ATTACK")
	{
		AttackMessage msg;
		packet >> msg;

		this->m_mutex.Lock();

		this->m_players[socketIndex]->handleAttackMessage(msg);

		this->m_mutex.Unlock();
		protFound = true;
	}
	else if(prot == "ATTACKENTITY")
	{
		AttackEntityMessage msg;
		packet >> msg;

		this->m_mutex.Lock();

		this->m_players[socketIndex]->handleEntityAttackMessage(msg);

		this->m_mutex.Unlock();
		protFound = true;
	}
	else if(prot == "USE_SKILL")
	{
		UseSkillMessage msg;
		packet >> msg;

		this->m_mutex.Lock();

		this->m_players[socketIndex]->handleUseSkillMessage(msg);

		this->m_mutex.Unlock();
		protFound = true;
	}

	return protFound;
}

bool Server::msgQueueEmpty()
{
	return this->msgQueue.empty();
}

bool Server::entityQueueEmpty()
{
	return this->entityQueue.empty();
}

Msg Server::msgQueueFront()
{
	Msg ret = this->msgQueue.front();
	this->msgQueue.pop();
	return ret;
}

EntityMessage Server::entityQueueFront()
{
	this->m_mutex.Lock();

	EntityMessage ret= this->entityQueue.front();
	this->entityQueue.pop();

	this->m_mutex.Unlock();
	return ret;
}

vector<Player*> Server::getPlayers()
{
	return this->m_players;
}