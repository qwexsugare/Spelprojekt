#pragma once
#include "NetworkMessage.h"
#include <string>

using namespace std;
class NetworkWelcomeMessage :public NetworkMessage
{
private:
	string mapName;
public:
	NetworkWelcomeMessage(void);
	NetworkWelcomeMessage(string msg);
	~NetworkWelcomeMessage(void);
	string getMapName();
	friend sf::Packet& operator<<(sf::Packet& packet,const NetworkWelcomeMessage& e);
	friend sf::Packet& operator>>(sf::Packet& packet, NetworkWelcomeMessage& e);
};

