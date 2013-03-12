#pragma once

#include "networkmessage.h"
#include <string>
using namespace std;

class NetworkPlayerJoinedMessage : public NetworkMessage
{
private:
	int m_playerIndex;
	string m_name;
public:
	NetworkPlayerJoinedMessage();
	NetworkPlayerJoinedMessage(int _playerIndex, string _name);
	~NetworkPlayerJoinedMessage();
	
	string getName()const;
	int getPlayerIndex()const;

	friend sf::Packet& operator<<(sf::Packet& packet,const NetworkPlayerJoinedMessage& e);
	friend sf::Packet& operator>>(sf::Packet& packet, NetworkPlayerJoinedMessage& e);
};

