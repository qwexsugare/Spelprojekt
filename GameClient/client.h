#ifndef CLIENT_H
#define CLIENT_H

#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <queue>
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
#include "NetworkHeroSelectedMessage.h"
#include "NetworkReadyMessage.h"
#include "NetworkReadyMessageToClient.h"
#include "NetworkSelectHeroMessage.h"
#include "NetworkStartGameMessage.h"
#include "NetworkSkillUsedMessage.h"
#include "NetworkInitEntityMessage.h"
#include "NetworkHeroInitMessage.h"
#include "NetworkUpdateEntityHealth.h"
#include "NetworkWelcomeMessage.h"
#include "NetworkEndGameMessage.h"
#include "NetworkPlayerJoinedMessage.h"
#include "NetworkTextMessage.h"

using namespace std;

class Client : private sf::Thread
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
	queue<NetworkStartGameMessage> m_startGameQueue;
	queue<NetworkHeroSelectedMessage> m_heroSelectedQueue;
	queue<NetworkSkillUsedMessage> m_skillUsedQueue;
	queue<NetworkInitEntityMessage> m_initEntityMessage;
	queue<NetworkHeroInitMessage> m_heroInitQueue;
	queue<NetworkUpdateEntityHealth> m_updateHealthMessage;
	queue<NetworkWelcomeMessage> m_welcomeMessage;
	queue<NetworkEndGameMessage> m_endGameMessageQueue;
	queue<NetworkPlayerJoinedMessage> m_playerJoinedMessageQueue;
	queue<NetworkReadyMessageToClient> m_readyMessageToClientQueue;
	queue<NetworkTextMessage> m_textMessageQueue;
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
	void sendMessage(NetworkSelectHeroMessage _usm);
	void sendMessage(NetworkReadyMessage _usm);
	void sendMessage(NetworkHeroInitMessage _usm);
	void sendMessage(NetworkEndGameMessage _negm);
	void sendMessage(NetworkPlayerJoinedMessage _msg);
	void sendMessage(NetworkTextMessage _msg);
	void sendPacket(sf::Packet p);

	NetworkEntityMessage entityQueueFront();
	NetworkRemoveEntityMessage removeEntityQueueFront();
	NetworkCreateActionMessage createActionQueueFront();
	NetworkCreateActionPositionMessage createActionPositionQueueFront();
	NetworkCreateActionTargetMessage createActionTargetQueueFront();
	NetworkSkillBoughtMessage skillBoughtQueueFront();
	NetworkRemoveActionTargetMessage removeActionTargetQueueFront();
	NetworkStartGameMessage startGameQueueFront();
	NetworkHeroSelectedMessage heroSelectedQueueFront();
	NetworkSkillUsedMessage skillUsedQueueFront();
	NetworkInitEntityMessage initEntityMessageFront();
	NetworkHeroInitMessage heroInitQueueFront();
	NetworkUpdateEntityHealth updateEntityHealthFront();
	NetworkWelcomeMessage networkWelcomeMessageFront();
	NetworkEndGameMessage endGameQueueFront();
	NetworkPlayerJoinedMessage playerJoinedMessageQueueFront();
	NetworkReadyMessageToClient readyMessageToClientQueueFront();
	NetworkTextMessage networkTextMessageFront();

	bool networkTextMessageQueueEmpty();
	bool updateEntityHealthEmpty();
	bool entityQueueEmpty();
	bool removeEntityQueueEmpty();
	bool createActionQueueEmpty();
	bool createActionPositionQueueEmpty();
	bool createActionTargetQueueEmpty();
	bool skillBoughtQueueEmpty();
	bool removeActionTargetQueueEmpty();
	bool startGameQueueEmpty();
	bool skillUsedQueueEmpty();
	bool heroSelectedQueueEmpty();
	bool initEntityMessageEmpty();
	bool heroInitQueueEmpty();
	bool networkWelcomeMessageEmpty();
	bool endGameQueueEmpty();
	bool playerJoinedMessageQueueEmpty();
	bool readyMessageToClientQueueEmpty();
};

#endif // CLIENT_H
