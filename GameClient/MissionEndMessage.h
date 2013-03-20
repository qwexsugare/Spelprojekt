#pragma once
#include <vector>
#include <string>

using namespace std;
class MissionEndMessage
{
private:
	vector<string> missionNames;
	vector<string> missionStatus;
public:
	MissionEndMessage(void);
	~MissionEndMessage(void);
	int nrOfMissions();
	void addMission(string mname, string status);
	void setStatusForMission(string m, string s);
	string getMissionName(int i);
	string getMissionStatus(int i);
};

