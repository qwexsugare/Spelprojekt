#include "Server.h"

Server::Server()
{
	this->clientArrPos=0;
}

Server::~Server()
{
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
			this->m_players.push_back(new Player(this->m_players.size()));
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
}

void Server::broadcast(string msg)
{
	sf::Packet packet;
	packet<<msg;
	for(int i=0;i<this->clientArrPos;i++)
	{
		this->clients[i].Send(packet);
	}
}

void Server::broadcast(EntityMessage ent)
{
	sf::Packet packet;
	packet<<ent;
	for(int i=0;i<this->clientArrPos;i++)
	{
		this->clients[i].Send(packet);
	}
}

void Server::broadcast(Msg msg)
{
	sf::Packet packet;
	packet<<msg;
	for(int i=0;i<this->clientArrPos;i++)
	{
		this->clients[i].Send(packet);
	}
}

void Server::Run()
{
	while(this->listener.IsValid())
	{
		this->goThroughSelector();
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
		//this->entityQueue.push(ent);

		//if(this->entityQueue.size() > 1000)
		//{
		//	this->entityQueue.pop();
		//}

		this->m_players[socketIndex]->handleEntityMessage(ent);

		this->m_mutex.Unlock();

		protFound=true;
	}
	if(prot=="MSG")
	{
		Msg msg;
		packet >> msg;
		this->m_mutex.Lock();
		this->msgQueue.push(msg);

		if(this->msgQueue.size() > 1000)
		{
			this->msgQueue.pop();
		}

		this->m_mutex.Unlock();
		protFound=true;
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