#ifndef REMOVE_ENTITY_MESSAGE_H
#define REMOVE_ENTITY_MESSAGE_H

#include <SFML\Network.hpp>

class RemoveEntityMessage
{
private:
	unsigned int m_id;
public:
	RemoveEntityMessage();
	RemoveEntityMessage(unsigned int _id);
	~RemoveEntityMessage();

	void setId(unsigned int _id);
	unsigned int getId();

	friend sf::Packet& operator<<(sf::Packet& packet,const RemoveEntityMessage& e);
	friend sf::Packet& operator>>(sf::Packet& packet, RemoveEntityMessage& e);	
};

#endif