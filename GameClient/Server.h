#ifndef SERVER_H
#define SERVER_H
#include "EntityMessage.h"
#include "Msg.h"

#include <iostream>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>

using namespace std;
class Server : private sf::Thread
{
private:
	sf::SelectorTCP selector;
	sf::SocketTCP listener;
	sf::SocketTCP clients[4];
	int clientArrPos;
	virtual void Run();
	void goThroughSelector();
	bool handleClientInData(sf::Packet packet, string prot);
public:
	Server();
	~Server();
	bool start(int port);
	void shutDown();
	void broadcast(string msg);
	void broadcast(EntityMessage ent);
	void broadcast(Msg msg);
	bool isRunning();

};

#endif // SERVER_H
