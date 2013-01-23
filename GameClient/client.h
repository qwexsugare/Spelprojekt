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

using namespace std;

class Client :private sf::Thread
{
private:
	sf::Mutex m_mutex;

	//data for the host
	sf::IPAddress hostIp;
	sf::SocketTCP hostSocket;
	int hostPort;

	//a threaded function that will recive messages from the server
	virtual void Run();
	queue<Msg> msgQueue;
	queue<EntityMessage> entityQueue;
	queue<RemoveEntityMessage> removeEntityQueue;
public:
	Client();
	~Client();
	bool connect(sf::IPAddress, int port);
	bool isConnected();
	void disconnect();
	void tellServer(string msg);
	void sendEntity(EntityMessage ent);
	void sendMsg(Msg m);
	void sendAttackMessage(AttackMessage am);
	void sendAttackEntityMessage(AttackEntityMessage aem);

	Msg msgQueueFront();
	EntityMessage entityQueueFront();
	RemoveEntityMessage removeEntityQueueFront();
	bool msgQueueEmpty();
	bool entityQueueEmpty();
	bool removeEntityQueueEmpty();
};

#endif // CLIENT_H
