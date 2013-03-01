#pragma once
#include "Skill.h"

enum HERO_TYPE {OFFICER, RED_KNIGHT, ENGINEER, DOCTOR, THE_MENTALIST};
class StatisticsPlayer
{
private:
	enum SKILLS {
		IDLE,
		DEATH,
		MOVE, 
		ATTACK, 
		MELEE_ATTACK,
		RANGED_ATTACK,
		AOE_MELEE_ATTACK,
		AOE_ATTACK,
		TOWER,
		STRENGTH,
		AGILITY,
		WITS,
		FORTITUDE,
		AIM,
		DEADLY_STRIKE, 
		GREED, 
		LIFESTEALING_STRIKE, 
		MENTAL_RESISTANCE, 
		PHYSICAL_RESISTANCE, 
		POISON_STRIKE, 
		TURRET_LIFE,
		CHAIN_STRIKE, 
		STUNNING_STRIKE, 
		CLOUD_OF_DARKNESS, 
		HEALING_TOUCH,
		DEMONIC_PRESENCE,
		TELEPORT,
		WALL,
		ENIGMATIC_PRESENCE,
		SWIFT_AS_A_CAT_POWERFUL_AS_A_BEAR,
		COURAGE_HONOR_VALOR,
		READY_AIM_FIRE,
		TIME_IS_MONEY,
		ENHANCED_DEVELOPMENT,
		LIFE_REGEN,
		SIMONS_EVIL,
		TESLA_CHAIN_TURRET,
		FROST_TURRET,
		POISON_ATTACK,
		HYPNOTIC_STARE,
		DEATH_PULSE_TURRET,
		POISON_TURRET,
		FROST_TURRET_PROJECTILE,
		NR_OF_SKILLS	//just equals the number of the last enum, to initiate arrays
		};
	
	HERO_TYPE hero;
	int m_id;
	int physicalDamageDealth;
	int mentalDamageDealth;
	int physicalDamageRecived;
	int mentalDamageRecived;
	int deathCounter;
	int skillMentalDamageDealth;
	int skillPhysicalDamageDealth;
	int skillsUsed[SKILLS::NR_OF_SKILLS];
public:
	void addSkillMentalDamageDealth(int d);
	void addSkillMentalPhysicalDamageDealth(int d);
	int getSkillMentalDamageDealth();
	int getSkillPhysicalDamageDealth();
	StatisticsPlayer(void);
	StatisticsPlayer(int id, HERO_TYPE hero);
	~StatisticsPlayer(void);
	int getPlayerId();
	HERO_TYPE getPlayerHero();
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
	void useSkill(SKILLS skill);
	int getNrOfTimesSkillUsed(SKILLS skill);
};

