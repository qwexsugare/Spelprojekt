#pragma once
#include "NetworkMessage.h"
#include <string>

using namespace std;
class NetworkWelcomeMessage :public NetworkMessage
{
private:
	string mapName;
	int playerId;
public:
	NetworkWelcomeMessage(void);
	NetworkWelcomeMessage(string msg);
	~NetworkWelcomeMessage(void);
	string getMapName();
	int getPlayerId();
	void setPlayerId(int _playerId);
	friend sf::Packet& operator<<(sf::Packet& packet,const NetworkWelcomeMessage& e);
	friend sf::Packet& operator>>(sf::Packet& packet, NetworkWelcomeMessage& e);
};

