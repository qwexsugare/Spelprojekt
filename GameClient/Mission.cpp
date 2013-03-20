#include "Mission.h"


Mission::Mission(void)
{
	this->startWave=0;
	this->endWave=0;
	this->missionType=MissionType::BBB;
	this->missionTime=0.0f;
	this->missionComplete=false;
	this->missionRunning=false;
	this->missionStarted=false;
	this->m_visible = false;
	this->bossId=0;
	this->addedToEntityHandler=false;
}


Mission::~Mission(void)
{
	ServerEntity *boss = EntityHandler::getServerEntity(this->bossId);

	if(boss != NULL)
	{
		EntityHandler::removeEntity(boss);
	}
}
void Mission::createMission(string type, float x, float z, int startwave, int endwave,string missionName)
{
	this->startWave=startwave;
	this->endWave=endwave;
	this->m_position=FLOAT3(x,0.0f,z);
	this->missionName=missionName;

	if(EntityHandler::getServerEntity(this->bossId) != NULL)
	{
		if(type=="bigBadBoss")
		{
			this->missionType=MissionType::BBB;
		}
	}
}

//void Mission::update(float dt)
//{
//	this->currentTime+=dt;
//	this->missionRunning=(this->currentTime>this->startTime && this->currentTime<this->endTime);
//
//	//if the mission is running and the boss is dead, the mission
//	//counts as completed, and the mission stops to run
//	if(this->missionRunning && EntityHandler::getServerEntity(this->bossId) == NULL)
//	{
//		this->missionComplete=true;
//		this->missionRunning=false;
//	}
//}

bool Mission::handle(int atWave)
{
	ServerEntity *boss = EntityHandler::getServerEntity(this->bossId);

	if(atWave>=this->startWave&&atWave<=this->endWave&&!this->missionStarted&&!missionRunning)
	{
		this->missionStarted=true;
		this->missionRunning=true;
		this->startMission();
	}
	if(boss != NULL && EntityHandler::getServerEntity(this->bossId)->getHealth()<=0)
	{
		this->missionComplete=true;
		if(boss != NULL)
		{
			boss->tellBossToDropGold();
			boss->getMessageQueue()->pushOutgoingMessage(new RemoveServerEntityMessage(0, EntityHandler::getId(), boss->getId()));
			this->m_messageQueue->pushOutgoingMessage(new MissionMessage(this->missionName,"completed"));

			this->m_messageQueue->pushOutgoingMessage(new CreateActionMessage(Skill::DEATH, this->m_id, this->m_position));				
		
		}
	}
	if(this->missionRunning)
	{
		//missionTime+=dt;
		if(atWave>=this->endWave)
		{
			this->missionRunning=false;
			//if the enemy died 
		
			this->missionTime=0.0f;
			ServerEntity *boss = EntityHandler::getServerEntity(this->bossId);
			if(boss != NULL)
			{
				boss->getMessageQueue()->pushOutgoingMessage(new RemoveServerEntityMessage(0, EntityHandler::getId(), boss->getId()));
				this->m_messageQueue->pushOutgoingMessage(new MissionMessage(this->missionName,"failed"));
			}
		}
	}
	return missionStarted;
}
bool Mission::startMission()
{
		if(this->missionType==MissionType::BBB)
		{
			BigBadBoss *boss = new BigBadBoss(this->m_position);
			EntityHandler::addEntity(boss);
			this->bossId = boss->getId();
			boss->getMessageQueue()->pushOutgoingMessage(new CreateActionMessage(Skill::IDLE, boss->getId(), boss->getPosition()));
		}
	return this->missionStarted;
}
float Mission::getTheTimeItTookToFinnishTheMission()
{
	return this->missionTime;
}
bool Mission::isMissionRunning()
{
	return this->missionRunning;
}
bool Mission::isMissionComplete()
{
	return this->missionComplete;
}

string Mission::getMissionName()
{
	return this->missionName;
}

bool Mission::isAddedToEntityHandler()
{
	return this->addedToEntityHandler;
}
void Mission::addToEntityHandler()
{
	this->addedToEntityHandler=true;
}