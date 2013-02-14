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
			NetworkCreateActionMessage cam;
			NetworkCreateActionPositionMessage capm;
			NetworkCreateActionTargetMessage catm;
			NetworkSkillBoughtMessage sbm;
			NetworkRemoveActionTargetMessage rat;
			NetworkSkillUsedMessage sum;

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

			case NetworkMessage::CreateAction:
				packet >> cam;

				this->m_mutex.Lock();
				this->m_createActionQueue.push(cam);

				if(this->m_createActionQueue.size() > 50)
				{
					this->m_createActionQueue.pop();
				}

				this->m_mutex.Unlock();
				break;

			case NetworkMessage::CreateActionPos:
				packet >> capm;

				this->m_mutex.Lock();
				this->m_createActionPositionQueue.push(capm);

				if(this->m_createActionPositionQueue.size() > 50)
				{
					this->m_createActionPositionQueue.pop();
				}

				this->m_mutex.Unlock();
				break;

			case NetworkMessage::CreateActionTarget:
				packet >> catm;

				this->m_mutex.Lock();
				this->m_createActionTargetQueue.push(catm);

				if(this->m_createActionTargetQueue.size() > 50)
				{
					this->m_createActionTargetQueue.pop();
				}

				this->m_mutex.Unlock();
				break;

			case NetworkMessage::SkillBought:
				packet >> sbm;

				this->m_mutex.Lock();
				this->m_skilllBoughtQueue.push(sbm);

				if(this->m_skilllBoughtQueue.size() > 50)
				{
					this->m_skilllBoughtQueue.pop();
				}

				this->m_mutex.Unlock();
				break;

			case NetworkMessage::RemoveActionTarget:
				packet >> rat;

				this->m_mutex.Lock();
				this->m_removeActionTargetQueue.push(rat);

				if(this->m_removeActionTargetQueue.size() > 50)
				{
					this->m_removeActionTargetQueue.pop();
				}

				this->m_mutex.Unlock();
				break;

			case NetworkMessage::SkillUsed:
				packet >> sum;

				this->m_mutex.Lock();
				this->m_skillUsedQueue.push(sum);

				if(this->m_skillUsedQueue.size() > 50)
				{
					this->m_skillUsedQueue.pop();
				}

				this->m_mutex.Unlock();
				break;

			case NetworkMessage::Disconnect:
				this->disconnect();
				break;

			case NetworkMessage::Start:
				this->m_mutex.Lock();
				this->m_startGameQueue.push(NetworkStartGameMessage());

				if(this->m_startGameQueue.size() > 50)
				{
					this->m_startGameQueue.pop();
				}

				this->m_mutex.Unlock();
				break;
			}
		}
	}
}

bool Client::isConnected()
{
	return this->m_hostSocket.IsValid();
}

bool Client::entityQueueEmpty()
{
	return this->m_entityMessageQueue.empty();
}

bool Client::removeEntityQueueEmpty()
{
	return this->m_removeEntityMessageQueue.empty();
}

bool Client::createActionQueueEmpty()
{
	return this->m_createActionQueue.empty();
}

bool Client::createActionPositionQueueEmpty()
{
	return this->m_createActionPositionQueue.empty();
}

bool Client::createActionTargetQueueEmpty()
{
	return this->m_createActionTargetQueue.empty();
}

bool Client::skillBoughtQueueEmpty()
{
	return this->m_skilllBoughtQueue.empty();
}

bool Client::removeActionTargetQueueEmpty()
{
	return this->m_removeActionTargetQueue.empty();
}

bool Client::skillUsedQueueEmpty()
{
	return this->m_skillUsedQueue.empty();
}

NetworkEntityMessage Client::entityQueueFront()
{
	this->m_mutex.Lock();

	NetworkEntityMessage ret = this->m_entityMessageQueue.front();
	this->m_entityMessageQueue.pop();

	this->m_mutex.Unlock();

	return ret;
}

NetworkRemoveEntityMessage Client::removeEntityQueueFront()
{
	this->m_mutex.Lock();

	NetworkRemoveEntityMessage ret = this->m_removeEntityMessageQueue.front();
	this->m_removeEntityMessageQueue.pop();

	this->m_mutex.Unlock();

	return ret;
}

NetworkCreateActionMessage Client::createActionQueueFront()
{
	this->m_mutex.Lock();

	NetworkCreateActionMessage ret = this->m_createActionQueue.front();
	this->m_createActionQueue.pop();

	this->m_mutex.Unlock();

	return ret;
}

NetworkCreateActionPositionMessage Client::createActionPositionQueueFront()
{
	this->m_mutex.Lock();

	NetworkCreateActionPositionMessage ret = this->m_createActionPositionQueue.front();
	this->m_createActionPositionQueue.pop();

	this->m_mutex.Unlock();

	return ret;
}

NetworkCreateActionTargetMessage Client::createActionTargetQueueFront()
{
	this->m_mutex.Lock();

	NetworkCreateActionTargetMessage ret = this->m_createActionTargetQueue.front();
	this->m_createActionTargetQueue.pop();

	this->m_mutex.Unlock();

	return ret;
}

NetworkSkillBoughtMessage Client::skillBoughtQueueFront()
{
	this->m_mutex.Lock();

	NetworkSkillBoughtMessage ret = this->m_skilllBoughtQueue.front();
	this->m_skilllBoughtQueue.pop();

	this->m_mutex.Unlock();

	return ret;
}

NetworkRemoveActionTargetMessage Client::removeActionTargetQueueFront()
{
	this->m_mutex.Lock();

	NetworkRemoveActionTargetMessage ret = this->m_removeActionTargetQueue.front();
	this->m_removeActionTargetQueue.pop();

	this->m_mutex.Unlock();

	return ret;
}

NetworkStartGameMessage Client::startGameQueueFront()
{
	this->m_mutex.Lock();

	NetworkStartGameMessage ret = this->m_startGameQueue.front();
	this->m_startGameQueue.pop();

	this->m_mutex.Unlock();

	return ret;
}

NetworkHeroSelectedMessage Client::heroSelectedQueueFront()
{
	this->m_mutex.Lock();

	NetworkHeroSelectedMessage ret = this->m_heroSelectedQueue.front();
	this->m_heroSelectedQueue.pop();

	this->m_mutex.Unlock();

	return ret;
}

NetworkSkillUsedMessage Client::skillUsedQueueFront()
{
	this->m_mutex.Lock();

	NetworkSkillUsedMessage ret = this->m_skillUsedQueue.front();
	this->m_skillUsedQueue.pop();

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

void Client::sendMessage(NetworkBuySkillMessage _usm)
{
	if(this->isConnected())
	{
		sf::Packet packet;
		packet << _usm;
		this->m_hostSocket.Send(packet);
	}
}

void Client::sendMessage(NetworkSelectHeroMessage _usm)
{
	if(this->isConnected())
	{
		sf::Packet packet;
		packet << _usm;
		this->m_hostSocket.Send(packet);
	}
}

void Client::sendMessage(NetworkReadyMessage _usm)
{
	if(this->isConnected())
	{
		sf::Packet packet;
		packet << _usm;
		this->m_hostSocket.Send(packet);
	}
}

bool Client::startGameQueueEmpty()
{
	return m_startGameQueue.empty();
}