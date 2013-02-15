#ifndef SERVER_H
#define SERVER_H

#define MAXPLAYERS 4
#include "Msg.h"
#include "EntityMessage.h"
#include "AttackMessage.h"
#include "RemoveEntityMessage.h"
#include "AttackEntityMessage.h"
#include "UseSkillMessage.h"

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

#include <iostream>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <queue>
#include <vector>
#include "MessageHandler.h"
#include "Player.h"

using namespace std;
namespace ServerStates
{
	enum State { LOBBY, GAME, END, EXIT };
};
class Server : private sf::Thread
{
private:
	ServerStates::State m_state;
	MessageHandler *m_messageHandler;
	MessageQueue *m_messageQueue;

	sf::Mutex m_mutex;

	queue<Msg> msgQueue;
	queue<EntityMessage> entityQueue;
	queue<AttackMessage> attackMessageQueue;
	queue<AttackEntityMessage> attackEntityMessageQueue;

	vector<Player*> m_players;

	sf::SelectorTCP selector;
	sf::SocketTCP listener;
	sf::SocketTCP clients[MAXPLAYERS];
	int clientArrPos;
	virtual void Run();
	void goThroughSelector();
	void handleMessages();
	bool handleClientInData(int socketIndex, sf::Packet packet, NetworkMessage::MESSAGE_TYPE type);
public:
	Server(MessageHandler *_messageHandler);
	~Server();
	bool start(int port);
	void shutDown();
	void broadcast(NetworkEntityMessage networkMessage);
	void broadcast(NetworkRemoveEntityMessage networkMessage);
	void broadcast(NetworkCreateActionMessage networkMessage);
	void broadcast(NetworkCreateActionPositionMessage networkMessage);
	void broadcast(NetworkCreateActionTargetMessage networkMessage);
	void broadcast(NetworkRemoveActionTargetMessage networkMessage);
	void broadcast(NetworkStartGameMessage networkMessage);
	void broadcast(NetworkHeroSelectedMessage networkMessage);

	bool isRunning();

	Msg msgQueueFront();
	EntityMessage entityQueueFront();
	bool msgQueueEmpty();
	bool entityQueueEmpty();

	vector<Player*> getPlayers();

	void setState(ServerStates::State s);
};

#endif // SERVER_H
