#pragma once
#include "networkmessage.h"
class NetworkInitEntityMessage :
	public NetworkMessage
{
	//id,modelid,pos,rot,scale,type
private:
	unsigned short type;
	unsigned short id;
	unsigned short modelid;
	float xPos;
	float zPos;
	float sx,sz,ex,ez;
	float yRot;
	float scale;
	int  health;
	float movementspeed;
public:
	NetworkInitEntityMessage(void);
	NetworkInitEntityMessage(unsigned short type, unsigned short modelid, unsigned short id, float xPos, float zPos, float yRot, float scale,int health,float sx, float sy,float ex,float ey,float movementspeed);
	~NetworkInitEntityMessage(void);

	int getType();
	int getID();
	int getModelID();
	float getXPos();
	float getZPos();
	float getYRot();
	float getScale();
	int getHealth();
	float getStartX();
	float getStartZ();
	float getEndX();
	float getEndZ();
	float getMovementSpeed();
	friend sf::Packet& operator<<(sf::Packet& packet,const NetworkInitEntityMessage& e);
	friend sf::Packet& operator>>(sf::Packet& packet, NetworkInitEntityMessage& e);
};

