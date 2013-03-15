#include "Mission.h"


Mission::Mission(void)
{
	this->startTime=0.0f;
	this->endTime=0.0f;
	this->missionType=MissionType::BBB;
	this->currentTime=0.0f;
	this->missionComplete=false;
	this->missionRunning=false;
	this->missionStarted=false;
	this->m_visible = false;
	this->bossId=0;
}


Mission::~Mission(void)
{
	ServerEntity *boss = EntityHandler::getServerEntity(this->bossId);

	if(boss != NULL)
	{
		EntityHandler::removeEntity(boss);
	}
}
void Mission::createMission(string type, float x, float z, float st, float et)
{
	this->startTime=st;
	this->endTime=et;
	this->m_position=FLOAT3(x,0.0f,z);

	if(EntityHandler::getServerEntity(this->bossId) != NULL)
	{
		if(type=="bigBadBoss")
		{
			this->missionType=MissionType::BBB;
		}
	}
}
void Mission::update(float dt)
{
	this->currentTime+=dt;
	this->missionRunning=(this->currentTime>this->startTime && this->currentTime<this->endTime);

	//if the mission is running and the boss is dead, the mission
	//counts as completed, and the mission stops to run
	if(this->missionRunning && EntityHandler::getServerEntity(this->bossId) == NULL)
	{
		this->missionComplete=true;
		this->missionRunning=false;
	}
}
void Mission::startMission()
{
	if(!this->missionStarted&&this->currentTime>this->startTime)
	{
		if(this->missionType==MissionType::BBB)
		{
			BigBadBoss *boss = new BigBadBoss(this->m_position);
			EntityHandler::addEntity(boss);
			this->bossId = boss->getId();
		}
		this->missionStarted=true;
	}
}
bool Mission::isMissionRunning()
{
	return this->missionRunning;
}
bool Mission::isMissionComplete()
{
	return this->missionComplete;
}