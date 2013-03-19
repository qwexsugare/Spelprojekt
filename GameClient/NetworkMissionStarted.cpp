#include "NetworkMissionStarted.h"

NetworkMissionStarted::NetworkMissionStarted():NetworkMessage()
{
	this->missionName="";
	this->startOrEnd="";
}

NetworkMissionStarted::NetworkMissionStarted(string n,string s):NetworkMessage(NetworkMessage::MESSAGE_TYPE::Mission)
{
	this->missionName=n;
	this->startOrEnd=s;
}


NetworkMissionStarted::~NetworkMissionStarted(void)
{
}
sf::Packet& operator<<(sf::Packet& packet,const NetworkMissionStarted& e)
{
	return packet<<*((int*)&e.m_type)<<e.missionName<<e.startOrEnd;
}

sf::Packet& operator>>(sf::Packet& packet, NetworkMissionStarted& e)
{
	return packet>>e.missionName>>e.startOrEnd;
}
string NetworkMissionStarted::getMissionName()
{
	return this->missionName;
}
string NetworkMissionStarted::getStartOrEnd()
{
	return this->startOrEnd;
}