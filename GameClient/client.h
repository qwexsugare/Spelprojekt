#ifndef CLIENT_H
#define CLIENT_H

#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <queue>
#include "EntityMessage.h"
#include "AttackMessage.h"
#include "Msg.h"
#include "RemoveEntityMessage.h"
#include "AttackEntityMessage.h"
#include "UseSkillMessage.h"
#include "UsePositionalSkillMessage.h"
#include "NetworkMessage.h"
#include "NetworkEntityMessage.h"
#include "NetworkRemoveEntityMessage.h"
#include "NetworkUseActionMessage.h"
#include "NetworkUseActionPositionMessage.h"
#include "NetworkUseActionTargetMessage.h"
#include "NetworkCreateActionMessage.h"
#include "NetworkCreateActionPositionMessage.h"
#include "NetworkCreateActionTargetMessage.h"
#include "NetworkBuySkillMessage.h"
#include "NetworkSkillBoughtMessage.h"
#include "NetworkRemoveActionTargetMessage.h"

using namespace std;

class Client :private sf::Thread
{
private:
	sf::Mutex m_mutex;

	//data for the host
	sf::IPAddress m_hostIp;
	sf::SocketTCP m_hostSocket;
	int m_hostPort;

	//a threaded function that will recive messages from the server
	virtual void Run();
	NetworkEntityMessage m_lastestMessage;
	bool m_hasMessage;

	queue<NetworkEntityMessage> m_entityMessageQueue;
	queue<NetworkRemoveEntityMessage> m_removeEntityMessageQueue;
	queue<NetworkCreateActionMessage> m_createActionQueue;
	queue<NetworkCreateActionPositionMessage> m_createActionPositionQueue;
	queue<NetworkCreateActionTargetMessage> m_createActionTargetQueue;
	queue<NetworkSkillBoughtMessage> m_skilllBoughtQueue;
	queue<NetworkRemoveActionTargetMessage> m_removeActionTargetQueue;
public:
	Client();
	~Client();
	bool connect(sf::IPAddress, int port);
	bool isConnected();
	void disconnect();
	void tellServer(string msg);

	void sendMessage(NetworkUseActionMessage _usm);
	void sendMessage(NetworkUseActionPositionMessage _usm);
	void sendMessage(NetworkUseActionTargetMessage _usm);
	void sendMessage(NetworkBuySkillMessage _usm);

	NetworkEntityMessage entityQueueFront();
	NetworkRemoveEntityMessage removeEntityQueueFront();
	NetworkCreateActionMessage createActionQueueFront();
	NetworkCreateActionPositionMessage createActionPositionQueueFront();
	NetworkCreateActionTargetMessage createActionTargetQueueFront();
	NetworkSkillBoughtMessage skillBoughtQueueFront();
	NetworkRemoveActionTargetMessage removeActionTargetQueueFront();
	bool entityQueueEmpty();
	bool removeEntityQueueEmpty();
	bool createActionQueueEmpty();
	bool createActionPositionQueueEmpty();
	bool createActionTargetQueueEmpty();
	bool skillBoughtQueueEmpty();
	bool removeActionTargetQueueEmpty();
};

#endif // CLIENT_H
