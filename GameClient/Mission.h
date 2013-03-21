#pragma once
#include "ServerEntity.h"
#include "Enemy.h"
#include "BigBadBoss.h"

enum MissionType {BBB,BBC};
class Mission : public ServerEntity
{
private:
	int startWave;
	int endWave;
	float missionTime;
	MissionType missionType;
	bool missionRunning;
	bool missionComplete;
	unsigned int bossId;
	bool missionStarted;
	bool startMission();
	string missionName;
	bool addedToEntityHandler;
public:
	Mission(void);
	~Mission(void);
	void createMission(string type, float x, float z, int startwave, int endwave,string missionName);
	MissionType getMissionType();
	//void update(float dt);
	bool isMissionRunning();
	bool isMissionComplete();
	bool handle(int atWave);
	float getTheTimeItTookToFinnishTheMission();
	string getMissionName();
	bool isAddedToEntityHandler();
	void addToEntityHandler();
};

