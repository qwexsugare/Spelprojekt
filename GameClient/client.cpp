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
	if(this->m_hostSocket.Connect(port,ip)!=sf::Socket::Done)
	{
		cout << "error connecting"<<endl;
		return false;
	}
	
	this->m_hostSocket.SetBlocking(false);
	//launches the thread that listen to messages from the server
	this->Launch();
	
	this->m_hostPort=port;
	this->m_hostIp=ip;
	
	return this->m_hostSocket.IsValid();
}

void Client::disconnect()
{
	//if(this->hostSocket.IsValid())
	this->m_hostSocket.Close();
}

void Client::tellServer(string msg)
{
	sf::Packet packet;
	packet << msg;
	if(this->m_hostSocket.IsValid())
		this->m_hostSocket.Send(packet);
}

void Client::Run()
{
	while(this->m_hostSocket.IsValid())
	{
		sf::Packet packet;
		if (this->m_hostSocket.Receive(packet) == sf::Socket::Done)
		{
			NetworkEntityMessage em;
			NetworkRemoveEntityMessage rem;

			int type;
			packet >> type;

			switch(type)
			{
			case NetworkMessage::Entity:
				packet >> em;
				this->m_mutex.Lock();
				this->m_entityMessageQueue.push(em);

				if(this->m_entityMessageQueue.size() > 50)
				{
					this->m_entityMessageQueue.pop();
				}

				this->m_mutex.Unlock();
				break;

			case NetworkMessage::RemoveEntity:
				packet >> rem;

				this->m_mutex.Lock();
				this->m_removeEntityMessageQueue.push(rem);

				if(this->m_removeEntityMessageQueue.size() > 50)
				{
					this->m_removeEntityMessageQueue.pop();
				}

				this->m_mutex.Unlock();
				break;

			case NetworkMessage::Disconnect:
				this->disconnect();
				break;
			}
		}
	}
}

bool Client::isConnected()
{
	return this->m_hostSocket.IsValid();
}

bool Client::entityMessageQueueEmpty()
{
	return this->m_entityMessageQueue.empty();
}

bool Client::removeEntityMessageQueueEmpty()
{
	return this->m_removeEntityMessageQueue.empty();
}

NetworkEntityMessage Client::entityMessageQueueFront()
{
	this->m_mutex.Lock();

	NetworkEntityMessage ret = this->m_entityMessageQueue.front();
	this->m_entityMessageQueue.pop();

	this->m_mutex.Unlock();

	return ret;
}

NetworkRemoveEntityMessage Client::removeEntityMessageQueueFront()
{
	this->m_mutex.Lock();

	NetworkRemoveEntityMessage ret = this->m_removeEntityMessageQueue.front();
	this->m_removeEntityMessageQueue.pop();

	this->m_mutex.Unlock();

	return ret;
}

void Client::sendMessage(NetworkUseActionMessage _usm)
{
	if(this->isConnected())
	{
		sf::Packet packet;
		packet << _usm;
		this->m_hostSocket.Send(packet);
	}
}

void Client::sendMessage(NetworkUseActionPositionMessage _usm)
{
	if(this->isConnected())
	{
		sf::Packet packet;
		packet << _usm;
		this->m_hostSocket.Send(packet);
	}
}

void Client::sendMessage(NetworkUseActionTargetMessage _usm)
{
	if(this->isConnected())
	{
		sf::Packet packet;
		packet << _usm;
		this->m_hostSocket.Send(packet);
	}
}