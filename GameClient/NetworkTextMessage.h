#pragma once
#include "NetworkMessage.h"
#include <string>

using namespace std;

class NetworkTextMessage :public NetworkMessage
{
private:
	string text;
public:
	NetworkTextMessage(void);
	NetworkTextMessage(string text);
	~NetworkTextMessage(void);
	string getTxtMessage();
	friend sf::Packet& operator<<(sf::Packet& packet,const NetworkTextMessage& e);
	friend sf::Packet& operator>>(sf::Packet& packet, NetworkTextMessage& e);
};

