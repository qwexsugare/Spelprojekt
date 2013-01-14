#include "Client.h"

Client::Client()
{
}

Client::~Client()
{
}

bool Client::connect(sf::IPAddress ip, int port)
{
	//connects to the server
	if(this->hostSocket.Connect(port,ip)!=sf::Socket::Done)
	{
		cout << "error connecting"<<endl;
		return false;
	}
	
	this->hostSocket.SetBlocking(false);
	//launches the thread that listen to messages from the server
	this->Launch();
	
	this->hostPort=port;
	this->hostIp=ip;
	
	return this->hostSocket.IsValid();
}

void Client::disconnect()
{
	if(this->hostSocket.IsValid())
		this->hostSocket.Close();
}

void Client::tellServer(string msg)
{
	sf::Packet packet;
	packet << msg;
	if(this->hostSocket.IsValid())
		this->hostSocket.Send(packet);
}

void Client::Run()
{
	while(this->hostSocket.IsValid())
	{
		sf::Packet packet;
		if (this->hostSocket.Receive(packet) == sf::Socket::Done)
		{
			string prot;
			packet >>prot;
			if(prot=="disconnect")
			{
				this->disconnect();
			}
			else if(prot=="ENT")
			{
				this->m_mutex.Lock();

				EntityMessage ent;
				packet >> ent;
				this->entityQueue.push(ent);

				
				if(this->entityQueue.size() > 100)
				{
					this->entityQueue.pop();
				}

				this->m_mutex.Unlock();
			}
			else if(prot=="MSG")
			{
				Msg msg;
				packet >> msg;
				this->msgQueue.push(msg);
			}
			else if(prot == "REMOVE")
			{
				RemoveEntityMessage rem;
				packet >> rem;
				this->removeEntityQueue.push(rem);
			}
		}
	}
}

bool Client::isConnected()
{
	return this->hostSocket.IsValid();
}


void Client::sendEntity(EntityMessage ent)
{
	if(this->isConnected())
	{
		sf::Packet packet;
		packet << ent;

		this->hostSocket.Send(packet);
	}
}

void Client::sendMsg(Msg m)
{
	if(this->isConnected())
	{
		sf::Packet packet;
		packet << m;
		this->hostSocket.Send(packet);
	}
}

void Client::sendAttackMessage(AttackMessage am)
{
	if(this->isConnected())
	{
		sf::Packet packet;
		packet << am;
		this->hostSocket.Send(packet);
	}
}

void Client::sendAttackEntityMessage(AttackEntityMessage aem)
{
	if(this->isConnected())
	{
		sf::Packet packet;
		packet << aem;
		this->hostSocket.Send(packet);
	}
}

bool Client::msgQueueEmpty()
{
	return this->msgQueue.empty();
}

bool Client::entityQueueEmpty()
{
	return this->entityQueue.empty();
}

bool Client::removeEntityQueueEmpty()
{
	return this->removeEntityQueue.empty();
}

Msg Client::msgQueueFront()
{
	Msg ret = this->msgQueue.front();
	this->msgQueue.pop();
	return ret;
}

EntityMessage Client::entityQueueFront()
{
	this->m_mutex.Lock();

	EntityMessage ret= this->entityQueue.front();
	this->entityQueue.pop();

	this->m_mutex.Unlock();
	return ret;
}

RemoveEntityMessage Client::removeEntityQueueFront()
{
	this->m_mutex.Lock();

	RemoveEntityMessage ret = this->removeEntityQueue.front();
	this->removeEntityQueue.pop();

	this->m_mutex.Unlock();

	return ret;
}