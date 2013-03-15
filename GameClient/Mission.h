#pragma once
#include "ServerEntity.h"
#include "Enemy.h"
#include "BigBadBoss.h"

enum MissionType {BBB};
class Mission : public ServerEntity
{
private:
	float startTime;
	float endTime;
	float currentTime;
	MissionType missionType;
	bool missionRunning;
	bool missionComplete;
	unsigned int bossId;
	bool missionStarted;
public:
	Mission(void);
	~Mission(void);
	void createMission(string type, float x, float z, float startTime, float endTime);
	MissionType getMissionType();
	void update(float dt);
	bool isMissionRunning();
	bool isMissionComplete();
	void startMission();
};

