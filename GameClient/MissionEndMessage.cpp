#include "MissionEndMessage.h"


MissionEndMessage::MissionEndMessage(void)
{
}


MissionEndMessage::~MissionEndMessage(void)
{
}
int MissionEndMessage::nrOfMissions()
{
	return this->missionNames.size();
}
void MissionEndMessage::addMission(string mname, string status)
{
	this->missionNames.push_back(mname);
	this->missionStatus.push_back(status);
}
void MissionEndMessage::setStatusForMission(string m, string s)
{
	for(int i=0;i<this->missionNames.size();i++)
	{
		if(this->missionNames[i]==m)
		{
			this->missionStatus[i]=s;
		}
	}
}
string MissionEndMessage::getMissionName(int i)
{
	return this->missionNames[i];
}
string MissionEndMessage::getMissionStatus(int i)
{
	return this->missionStatus[i];
}