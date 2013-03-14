#include "NetworkTextMessage.h"


NetworkTextMessage::NetworkTextMessage(void) : NetworkMessage(NetworkMessage::MESSAGE_TYPE::TXTMSG)
{
	this->text="";
}

NetworkTextMessage::NetworkTextMessage(string txt) : NetworkMessage(NetworkMessage::MESSAGE_TYPE::TXTMSG)
{
	this->text=txt;
}
NetworkTextMessage::~NetworkTextMessage(void)
{
}
string NetworkTextMessage::getTxtMessage()
{
	return this->text;
}
sf::Packet& operator<<(sf::Packet& packet,const NetworkTextMessage& e)
{
	return packet << *((int*)&e.m_type) << e.text;
}

sf::Packet& operator>>(sf::Packet& packet, NetworkTextMessage& e)
{
	return packet >> e.text;
}