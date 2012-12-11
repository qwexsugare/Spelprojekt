#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>

using namespace std;
class NetworkServer : private sf::Thread
{
private:
	sf::SelectorTCP selector;
	sf::SocketTCP listener;
	sf::SocketTCP clients[4];
	int clientArrPos;
	virtual void Run();
	void goThroughSelector();
public:
	NetworkServer();
	~NetworkServer();
	bool start(int port);
	void shutDown();
	void broadcast(string msg);
	bool isRunning();

};

#endif // SERVER_H
