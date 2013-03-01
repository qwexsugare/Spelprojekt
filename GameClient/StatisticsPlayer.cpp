#include "StatisticsPlayer.h"


StatisticsPlayer::StatisticsPlayer(void)
{
	this->hero=Hero::HERO_TYPE::OFFICER;
	this->m_id=0;
	this->physicalDamageDealth=0;
	this->mentalDamageDealth=0;
	this->physicalDamageRecived=0;
	this->mentalDamageRecived=0;
	this->deathCounter=0;
	this->skillMentalDamageDealth=0;
	this->skillPhysicalDamageDealth=0;
	for(int i=0;i<Skill::SKILLS::NR_OF_SKILLS;i++)
	{
		this->skillsUsed[i]=0;
	}
}

StatisticsPlayer::StatisticsPlayer(int id,Hero::HERO_TYPE hero)
{
	this->hero=hero;
	this->m_id=id;
	this->physicalDamageDealth=0;
	this->mentalDamageDealth=0;
	this->physicalDamageRecived=0;
	this->mentalDamageRecived=0;
	this->deathCounter=0;
	this->skillMentalDamageDealth=0;
	this->skillPhysicalDamageDealth=0;
	for(int i=0;i<Skill::SKILLS::NR_OF_SKILLS;i++)
	{
		this->skillsUsed[i]=0;
	}
}

StatisticsPlayer::~StatisticsPlayer(void)
{
}

void StatisticsPlayer::increaseDeathCount()
{
	this->deathCounter++;
}
void StatisticsPlayer::addMentalDamageDealth(int d)
{
	this->mentalDamageDealth+=d;
}
void StatisticsPlayer::addPhysicalDamageDealth(int d)
{
	this->physicalDamageDealth+=d;
}
void StatisticsPlayer::addMentalDamageRecived(int d)
{
	this->mentalDamageRecived+=d;
}
void StatisticsPlayer::addPhysicalDamageRecived(int d)
{
	this->physicalDamageRecived+=d;
}
int StatisticsPlayer::getMentalDamageDealth()
{
	return this->mentalDamageDealth;
}
int StatisticsPlayer::getMentalDamageRecived()
{
	return this->mentalDamageRecived;
}
int StatisticsPlayer::getPhysicalDamageDealth()
{
	return this->physicalDamageDealth;
}
int StatisticsPlayer::getPhysicalDamageRecived()
{
	return this->physicalDamageRecived;
}
Hero::HERO_TYPE StatisticsPlayer::getPlayerHero()
{
	return this->hero;
}
int StatisticsPlayer::getPlayerId()
{
	return this->m_id;
}
int StatisticsPlayer::getTotalDamageDealth()
{
	return this->mentalDamageDealth+this->physicalDamageDealth;
}
void StatisticsPlayer::useSkill(Skill::SKILLS skill)
{
	this->skillsUsed[skill]++;
}
int StatisticsPlayer::getNrOfTimesSkillUsed(Skill::SKILLS skill)
{
	return this->skillsUsed[skill];
}
void StatisticsPlayer::addSkillMentalDamageDealth(int d)
{
	this->skillMentalDamageDealth+=d;
}
void StatisticsPlayer::addSkillMentalPhysicalDamageDealth(int d)
{
	this->skillPhysicalDamageDealth+=d;
}
int StatisticsPlayer::getSkillMentalDamageDealth()
{
	return this->skillMentalDamageDealth;
}
int StatisticsPlayer::getSkillPhysicalDamageDealth()
{
	return this->skillPhysicalDamageDealth;
}