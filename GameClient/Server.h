#ifndef SERVER_H
#define SERVER_H

#include "NetworkMessage.h"
#include "NetworkEntityMessage.h"
#include "NetworkDisconnectMessage.h"
#include "NetworkRemoveEntityMessage.h"
#include "NetworkUseActionMessage.h"
#include "NetworkUseActionPositionMessage.h"
#include "NetworkCreateActionMessage.h"
#include "NetworkCreateActionPositionMessage.h"
#include "NetworkCreateActionTargetMessage.h"
#include "NetworkRemoveActionTargetMessage.h"
#include "NetworkSkillBoughtMessage.h"
#include "NetworkHeroSelectedMessage.h"
#include "NetworkSelectHeroMessage.h"
#include "NetworkReadyMessage.h"
#include "NetworkStartGameMessage.h"
#include "NetworkSkillUsedMessage.h"
#include "NetworkInitEntityMessage.h"
#include "NetworkHeroInitMessage.h"
#include "NetworkUpdateEntityHealth.h"
#include "NetworkEndGameMessage.h"

#include <iostream>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <queue>
#include <vector>
#include "MessageHandler.h"
#include "Player.h"
#include "Statistics.h"
#define MAXPLAYERS 4

using namespace std;
class Server : private sf::Thread
{
private:
	MessageHandler *m_messageHandler;
	MessageQueue *m_messageQueue;

	sf::Mutex m_mutex;

	Player* m_players[MAXPLAYERS];

	sf::SelectorTCP selector;
	sf::SocketTCP listener;
	sf::SocketTCP clients[MAXPLAYERS];
	int nrOfPlayers;
	int nextEmptyArrayPos;
	virtual void Run();
	void goThroughSelector();
	void handleMessages();
	bool handleClientInData(int socketIndex, sf::Packet packet, NetworkMessage::MESSAGE_TYPE type);
public:
	Server(MessageHandler *_messageHandler);
	~Server();
	bool start(int port);
	void shutDown();
	void broadcast(NetworkUpdateEntityHealth networkMessage);
	void broadcast(NetworkEntityMessage networkMessage);
	void broadcast(NetworkRemoveEntityMessage networkMessage);
	void broadcast(NetworkCreateActionMessage networkMessage);
	void broadcast(NetworkCreateActionPositionMessage networkMessage);
	void broadcast(NetworkCreateActionTargetMessage networkMessage);
	void broadcast(NetworkRemoveActionTargetMessage networkMessage);
	void broadcast(NetworkStartGameMessage networkMessage);
	void broadcast(NetworkHeroSelectedMessage networkMessage);
	void broadcast(NetworkSkillUsedMessage networkMessage);
	void broadcast(NetworkSkillBoughtMessage networkMessage);
	void broadcast(NetworkInitEntityMessage networkMessage);
	void broadcast(NetworkHeroInitMessage networkMessage);
	void broadcast(NetworkEndGameMessage networkMessage);

	bool isRunning();

	vector<Player*> getPlayers();
};

#endif // SERVER_H
