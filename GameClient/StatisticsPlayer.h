#pragma once
#include "Skill.h"
#include "Hero.h"
class StatisticsPlayer
{
private:
	
	Hero::HERO_TYPE hero;
	int m_id;
	int physicalDamageDealth;
	int mentalDamageDealth;
	int physicalDamageRecived;
	int mentalDamageRecived;
	int deathCounter;
	int skillMentalDamageDealth;
	int skillPhysicalDamageDealth;
	int skillsUsed[Skill::SKILLS::NR_OF_SKILLS];
public:
	void addSkillMentalDamageDealth(int d);
	void addSkillMentalPhysicalDamageDealth(int d);
	int getSkillMentalDamageDealth();
	int getSkillPhysicalDamageDealth();
	StatisticsPlayer(void);
	StatisticsPlayer(int id, Hero::HERO_TYPE hero);
	~StatisticsPlayer(void);
	int getPlayerId();
	Hero::HERO_TYPE getPlayerHero();
	int getPhysicalDamageDealth();
	int getMentalDamageDealth();
	int getPhysicalDamageRecived();
	int getMentalDamageRecived();
	int getTotalDamageDealth();
	void addPhysicalDamageDealth(int d);
	void addMentalDamageDealth(int d);
	void addPhysicalDamageRecived(int d);
	void addMentalDamageRecived(int d);
	void increaseDeathCount();
	void useSkill(Skill::SKILLS skill);
	int getNrOfTimesSkillUsed(Skill::SKILLS skill);
};

