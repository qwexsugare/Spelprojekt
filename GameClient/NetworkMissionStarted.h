#pragma once
#include "NetworkMessage.h"
#include <string>

using namespace std;
class NetworkMissionStarted : public NetworkMessage
{
private:
	string missionName;
	string startOrEnd;
public:
	NetworkMissionStarted();
	NetworkMissionStarted(string n,string s);
	~NetworkMissionStarted(void);
	string getMissionName();
	string getStartOrEnd();
	friend sf::Packet& operator<<(sf::Packet& packet,const NetworkMissionStarted& e);
	friend sf::Packet& operator>>(sf::Packet& packet, NetworkMissionStarted& e);
};

