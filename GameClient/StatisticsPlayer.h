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
	int getSkillMentalDamageDealth() const;
	int getSkillPhysicalDamageDealth() const;
	StatisticsPlayer(void);
	~StatisticsPlayer(void);
	int getPlayerId() const;
	StatisticsPlayer::HERO_TYPE getPlayerHero() const;
	int getPhysicalDamageDealth() const;
	int getMentalDamageDealth() const;
	int getPhysicalDamageRecived() const;
	int getMentalDamageRecived() const;
	int getTotalDamageDealth() const;
	void addPhysicalDamageDealth(int d);
	void addMentalDamageDealth(int d);
	void addPhysicalDamageRecived(int d);
	void addMentalDamageRecived(int d);
	void increaseDeathCount();
	void useSkill(Skill::SKILLS skill);
	int getNrOfTimesSkillUsed(int i) const;
	void setPlayerName(string name);
	string getPlayerName() const;
	int getDeamonsKilled() const;
	void increaseDeamonsKilled();
	int getDeathCount() const;
	void increaseGoldCollected(int g);
	int getGoldCollected() const;
	void increaseHealdAmount(int h);
	int getHealedAmount() const;
};

