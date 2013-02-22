#pragma once
#include "networkmessage.h"
class NetworkUpdateEntityMessage :
	public NetworkMessage
{
private:
	unsigned short id;
	float xPos;
	float zPos;
	float yRot; 
public:
	float getXPos();
	float getZPos();
	float getYRot();
	int getID();
	NetworkUpdateEntityMessage(void);
	NetworkUpdateEntityMessage(int id, float xpos, float zpos, float yrot);
	~NetworkUpdateEntityMessage(void);

	friend sf::Packet& operator<<(sf::Packet& packet,const NetworkUpdateEntityMessage& e);
	friend sf::Packet& operator>>(sf::Packet& packet, NetworkUpdateEntityMessage& e);
};

