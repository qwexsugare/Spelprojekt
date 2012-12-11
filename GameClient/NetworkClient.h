#ifndef NETWORK_CLIENT_H
#define NETWORK_CLIENT_H

#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <queue>

using namespace std;

class NetworkClient :public sf::Thread
{
private:
	//data for the host
	sf::IPAddress hostIp;
	sf::SocketTCP hostSocket;
	int hostPort;
	queue<string> messageQueue;

	//a threaded function that will recive messages from the server
	virtual void Run();
	
public:
	NetworkClient();
	~NetworkClient();
	bool connect(sf::IPAddress, int port);
	bool isConnected();
	void disconnect();
	void tellServer(string msg);
	string getMessage();
};

#endif // CLIENT_H
