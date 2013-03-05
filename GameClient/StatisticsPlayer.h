#pragma once
#include "Skill.h"
class StatisticsPlayer
{
public:
	static enum HERO_TYPE {OFFICER, RED_KNIGHT, ENGINEER, DOCTOR, THE_MENTALIST, NONE};
private:
	HERO_TYPE hero;
	int m_id;
	int physicalDamageDealth;
	int mentalDamageDealth;
	int physicalDamageRecived;
	int mentalDamageRecived;
	int deathCounter;
	int skillMentalDamageDealth;
	int skillPhysicalDamageDealth;
	int skillsUsed[Skill::SKILLS::NR_OF_SKILLS];
	int deamonsKilled;
	int goldCollected;
	string playerName;
	int healedAmount;
public:
	void setId(int id);
	void setHeroType(StatisticsPlayer::HERO_TYPE hero);
	void addSkillMentalDamageDealth(int d);
	void addSkillMentalPhysicalDamageDealth(int d);
	int getSkillMentalDamageDealth();
	int getSkillPhysicalDamageDealth();
	StatisticsPlayer(void);
	~StatisticsPlayer(void);
	int getPlayerId();
	StatisticsPlayer::HERO_TYPE getPlayerHero();
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
	int getNrOfTimesSkillUsed(int i);
	void setPlayerName(string name);
	string getPlayerName();
	int getDeamonsKilled();
	void increaseDeamonsKilled();
	int getDeathCount();
	void increaseGoldCollected(int g);
	int getGoldCollected();
	void increaseHealdAmount(int h);
	int getHealedAmount();
};

