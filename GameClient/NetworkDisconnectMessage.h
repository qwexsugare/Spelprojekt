#ifndef NETWORK_DISCONNECT_MESSAGE_H
#define NETWORK_DISCONNECT_MESSAGE_H

#include "NetworkMessage.h"
#include <string>

class NetworkDisconnectMessage : public NetworkMessage
{
private:
	std::string m_message;
public:
	NetworkDisconnectMessage();
	NetworkDisconnectMessage(std::string _message);
	~NetworkDisconnectMessage();

	std::string getMessage();

	friend sf::Packet& operator<<(sf::Packet& packet,const NetworkDisconnectMessage& e);
	friend sf::Packet& operator>>(sf::Packet& packet, NetworkDisconnectMessage& e);
};

#endif