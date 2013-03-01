#include "StatisticsPlayer.h"


StatisticsPlayer::StatisticsPlayer(void)
{
	this->hero=StatisticsPlayer::OFFICER;
	this->m_id=-1;
	this->physicalDamageDealth=0;
	this->mentalDamageDealth=0;
	this->physicalDamageRecived=0;
	this->mentalDamageRecived=0;
	this->deathCounter=0;
	this->skillMentalDamageDealth=0;
	this->skillPhysicalDamageDealth=0;
	this->playerName="NONE";
	this->deamonsKilled=0;
	goldCollected=0;
	this->healedAmount=0;
	for(int i=0;i<Skill::SKILLS::NR_OF_SKILLS;i++)
	{
		this->skillsUsed[i]=0;
	}
}

StatisticsPlayer::~StatisticsPlayer(void)
{
}

void StatisticsPlayer::setId(int id)
{
	this->m_id=id;
}
void StatisticsPlayer::setHeroType(StatisticsPlayer::HERO_TYPE hero)
{
	this->hero=hero;
}

void StatisticsPlayer::increaseHealdAmount(int h)
{
	this->healedAmount+=h;
}
int StatisticsPlayer::getHealedAmount()
{
	return this->healedAmount;
}
void StatisticsPlayer::increaseGoldCollected(int p)
{
	this->goldCollected+=p;
}
int StatisticsPlayer::getGoldCollected()
{
	return this->goldCollected;
}

int StatisticsPlayer::getDeamonsKilled()
{
	return this->deamonsKilled;
}
void StatisticsPlayer::increaseDeamonsKilled()
{
	this->deamonsKilled++;
}

void StatisticsPlayer::setPlayerName(string n)
{
	this->playerName=n;
}
string StatisticsPlayer::getPlayerName()
{
	return this->playerName;
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
StatisticsPlayer::HERO_TYPE StatisticsPlayer::getPlayerHero()
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
int StatisticsPlayer::getNrOfTimesSkillUsed(int i)
{
	return this->skillsUsed[i];
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
int StatisticsPlayer::getDeathCount()
{
	return this->deathCounter;
}