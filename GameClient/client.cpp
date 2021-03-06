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
	sf::Packet packet;
	packet << (int)NetworkMessage::Disconnect;
	this->m_hostSocket.Send(packet);
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
			NetworkHeroSelectedMessage nhsm;
			NetworkInitEntityMessage iem;
			NetworkHeroInitMessage nhim;
			NetworkUpdateEntityHealth nueh;
			NetworkStartGameMessage nstm;
			NetworkEndGameMessage negm;
			NetworkWelcomeMessage nwm;
			NetworkPlayerJoinedMessage npjm;
			NetworkTextMessage ntm;
			NetworkReadyMessageToClient nrmtc;
			NetworkEntityAttributeMessage nea;
			NetworkMissionStarted nms;
			
			int type;
			packet >> type;

			switch(type)
			{
			case NetworkMessage::READY_TO_CLIENT:
				packet >> nrmtc;
				this->m_mutex.Lock();

				this->m_readyMessageToClientQueue.push(nrmtc);
				if(this->m_readyMessageToClientQueue.size() > 1337)
				{
					this->m_readyMessageToClientQueue.pop();
				}

				this->m_mutex.Unlock();
				break;

			case NetworkMessage::Entity:
				packet >> em;
				this->m_mutex.Lock();

				this->m_entityMessageQueue.push(em);

				if(this->m_entityMessageQueue.size() > 200)
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
				packet >> nstm;
				this->m_startGameQueue.push(nstm);

				if(this->m_startGameQueue.size() > 50)
				{
					this->m_startGameQueue.pop();
				}

				this->m_mutex.Unlock();
				break;

			case NetworkMessage::HeroSelected:
				packet >> nhsm;
				this->m_mutex.Lock();
				this->m_heroSelectedQueue.push(nhsm);

				if(this->m_heroSelectedQueue.size() > 50)
					this->m_heroSelectedQueue.pop();

				this->m_mutex.Unlock();
				break;

			case NetworkMessage::initEntities:
				packet >> iem;
				this->m_mutex.Lock();
				this->m_initEntityMessage.push(iem);
				if(this->m_initEntityMessage.size() > 50)
					this->m_initEntityMessage.pop();
				this->m_mutex.Unlock();
				break;
			case NetworkMessage::HeroInit:
				packet >> nhim;
				this->m_mutex.Lock();
				this->m_heroInitQueue.push(nhim);

				if(this->m_heroInitQueue.size() > 50)
					this->m_heroInitQueue.pop();

				this->m_mutex.Unlock();
				break;

			case NetworkMessage::updateEntityHealth:
				packet >> nueh;
				this->m_mutex.Lock();
				this->m_updateHealthMessage.push(nueh);

				if(this->m_updateHealthMessage.size()>50)
					this->m_updateHealthMessage.pop();
				this->m_mutex.Unlock();
				break;
			case NetworkMessage::welcomeMessage:
				packet >>nwm;
				this->m_mutex.Lock();
				this->m_welcomeMessage.push(nwm);
				this->m_mutex.Unlock();
				break;

			case NetworkMessage::EndGame:
				packet >> negm;
				this->m_mutex.Lock();
				m_endGameMessageQueue.push(negm);
				this->m_mutex.Unlock();
				break;

			case NetworkMessage::PLAYER_JOINED:
				packet >> npjm;
				this->m_mutex.Lock();
				m_playerJoinedMessageQueue.push(npjm);
				this->m_mutex.Unlock();
				break;
			case NetworkMessage::TXTMSG:
				packet >> ntm;
				this->m_mutex.Lock();
				m_textMessageQueue.push(ntm);
				this->m_mutex.Unlock();
				break;
			case NetworkMessage::UpdateEntityAttribute:
				packet >> nea;
				this->m_mutex.Lock();
				this->m_entityAttributeMessageQueue.push(nea);
				this->m_mutex.Unlock();
				break;
			case NetworkMessage::Mission:
				packet >> nms;
				this->m_mutex.Lock();
				this->m_missionQueue.push(nms);
				this->m_mutex.Unlock();
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

bool Client::networkWelcomeMessageEmpty()
{
	return this->m_welcomeMessage.empty();
}

NetworkWelcomeMessage Client::networkWelcomeMessageFront()
{
	this->m_mutex.Lock();
	NetworkWelcomeMessage ret;
	ret = m_welcomeMessage.front();
	this->m_welcomeMessage.pop();
	this->m_mutex.Unlock();
	return ret;
}

NetworkEntityMessage Client::entityQueueFront()
{
	this->m_mutex.Lock();

	NetworkEntityMessage ret = this->m_entityMessageQueue.front();
	this->m_entityMessageQueue.pop();

	this->m_mutex.Unlock();

	return ret;
}

NetworkInitEntityMessage Client::initEntityMessageFront()
{
	this->m_mutex.Lock();
	NetworkInitEntityMessage ret = this->m_initEntityMessage.front();
	this->m_initEntityMessage.pop();

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

NetworkHeroInitMessage Client::heroInitQueueFront()
{
	this->m_mutex.Lock();

	NetworkHeroInitMessage ret = this->m_heroInitQueue.front();
	this->m_heroInitQueue.pop();

	this->m_mutex.Unlock();

	return ret;
}
NetworkUpdateEntityHealth Client::updateEntityHealthFront()
{
	this->m_mutex.Lock();

	NetworkUpdateEntityHealth ret = this->m_updateHealthMessage.front();
	this->m_updateHealthMessage.pop();

	this->m_mutex.Unlock();

	return ret;
}

NetworkEndGameMessage Client::endGameQueueFront()
{
	this->m_mutex.Lock();

	NetworkEndGameMessage ret = this->m_endGameMessageQueue.front();
	this->m_endGameMessageQueue.pop();

	this->m_mutex.Unlock();

	return ret;
}

NetworkPlayerJoinedMessage Client::playerJoinedMessageQueueFront()
{
	this->m_mutex.Lock();

	NetworkPlayerJoinedMessage ret = m_playerJoinedMessageQueue.front();
	this->m_playerJoinedMessageQueue.pop();

	this->m_mutex.Unlock();

	return ret;
}
NetworkTextMessage Client::networkTextMessageFront()
{
	this->m_mutex.Lock();

	NetworkTextMessage ret = this->m_textMessageQueue.front();
	this->m_textMessageQueue.pop();

	this->m_mutex.Unlock();

	return ret;
}

NetworkReadyMessageToClient Client::readyMessageToClientQueueFront()
{
	this->m_mutex.Lock();

	NetworkReadyMessageToClient ret = m_readyMessageToClientQueue.front();
	this->m_readyMessageToClientQueue.pop();

	this->m_mutex.Unlock();

	return ret;
}

NetworkMissionStarted Client::missionQueueFront()
{
	this->m_mutex.Lock();
	NetworkMissionStarted ret = m_missionQueue.front();
	this->m_missionQueue.pop();
	this->m_mutex.Unlock();
	return ret;
}

NetworkEntityAttributeMessage Client::entityAttributeFront()
{
	this->m_mutex.Lock();

	NetworkEntityAttributeMessage ret = this->m_entityAttributeMessageQueue.front();
	this->m_entityAttributeMessageQueue.pop();

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

void Client::sendMessage(NetworkTextMessage _msg)
{
	if(this->isConnected())
	{
		sf::Packet packet;
		packet << _msg;
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
void Client::sendPacket(sf::Packet p)
{
	if(this->isConnected())
	{
		this->m_hostSocket.Send(p);
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

void Client::sendMessage(NetworkHeroInitMessage _usm)
{
	if(this->isConnected())
	{
		sf::Packet packet;
		packet << _usm;
		this->m_hostSocket.Send(packet);
	}
}

void Client::sendMessage(NetworkEndGameMessage _negm)
{
	if(this->isConnected())
	{
		sf::Packet packet;
		packet << _negm;
		this->m_hostSocket.Send(packet);
	}
}

void Client::sendMessage(NetworkPlayerJoinedMessage _msg)
{
	if(this->isConnected())
	{
		sf::Packet packet;
		packet << _msg;
		this->m_hostSocket.Send(packet);
	}
}

bool Client::entityAttributeQueueEmpty()
{
	return this->m_entityAttributeMessageQueue.empty();
}

bool Client::startGameQueueEmpty()
{
	return m_startGameQueue.empty();
}

bool Client::heroSelectedQueueEmpty()
{
	return m_heroSelectedQueue.empty();
}

bool Client::initEntityMessageEmpty()
{
	return this->m_initEntityMessage.empty();
}
bool Client::heroInitQueueEmpty()
{
	return m_heroInitQueue.empty();
}

bool Client::updateEntityHealthEmpty()
{
	return m_updateHealthMessage.empty();
}

bool Client::endGameQueueEmpty()
{
	return m_endGameMessageQueue.empty();
}

bool Client::playerJoinedMessageQueueEmpty()
{
	return m_playerJoinedMessageQueue.empty();
}

bool Client::readyMessageToClientQueueEmpty()
{
	return m_readyMessageToClientQueue.empty();
}

bool Client::networkTextMessageQueueEmpty()
{
	return this->m_textMessageQueue.empty();
}

bool Client::missionQueueEmpty()
{
	return this->m_missionQueue.empty();
}
