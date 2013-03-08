#pragma once

#include "networkmessage.h"
#include <string>

using namespace std;

class NetworkStartGameMessage :
	public NetworkMessage
{
private:
	string mapName;
public:
	string getMapName();
	void setMapName(string n);
	NetworkStartGameMessage();
	NetworkStartGameMessage(string mapName);
	~NetworkStartGameMessage();

	friend sf::Packet& operator<<(sf::Packet& packet,const NetworkStartGameMessage& e);
	friend sf::Packet& operator>>(sf::Packet& packet, NetworkStartGameMessage& e);
};

