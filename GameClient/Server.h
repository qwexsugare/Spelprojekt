#ifndef SERVER_H
#define SERVER_H
#include "EntityMessage.h"
#include "Msg.h"

#include <iostream>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <queue>
#include <vector>
#include "MessageHandler.h"
#include "Player.h"

using namespace std;
class Server : private sf::Thread
{
private:
	MessageHandler *m_messageHandler;

	sf::Mutex m_mutex;

	queue<Msg> msgQueue;
	queue<EntityMessage> entityQueue;

	vector<Player*> m_players;

	sf::SelectorTCP selector;
	sf::SocketTCP listener;
	sf::SocketTCP clients[4];
	int clientArrPos;
	virtual void Run();
	void goThroughSelector();
	bool handleClientInData(int socketIndex, sf::Packet packet, string prot);
public:
	Server(MessageHandler *_messageHandler);
	~Server();
	bool start(int port);
	void shutDown();
	void broadcast(string msg);
	void broadcast(EntityMessage ent);
	void broadcast(Msg msg);
	bool isRunning();

	Msg msgQueueFront();
	EntityMessage entityQueueFront();
	bool msgQueueEmpty();
	bool entityQueueEmpty();

	vector<Player*> getPlayers();
};

#endif // SERVER_H
