#ifndef UNIT_ENTITY_H
#define UNIT_ENTITY_H

#include "ServerEntity.h"
#include "Skill.h"

class UnitEntity : public ServerEntity
{
protected:
	static const int MAX_STRENGTH = 20;
	static const int MAX_AGILITY = 20;
	static const int MAX_WITS = 20;
	static const int MAX_FORTITUDE = 20;

	vector<Skill*> m_skills;

	unsigned int m_lastDamageDealer;

	int m_health;
	int m_maxHealth;

	int m_strength;
	int m_agility;
	int m_wits;
	int m_fortitude;

	float m_turretDuration;
	float m_greed;
	float m_movementSpeedChange;
	float m_baseMovementSpeed;
	float m_movementSpeed;
	float m_baseAttackSpeed;
	float m_attackSpeedChange;
	float m_attackSpeed;
	float m_attackCooldown;
	float m_attackRange;
	float m_minPhysicalDamage;
	float m_baseMentalDamage;
	float m_mentalDamageChange;
	float m_maxMentalDamage;
	float m_physicalResistance;
	float m_physicalResistanceChange;
	float m_basePhysicalResistance;
	float m_mentalResistance;
	unsigned int m_lifeStealChance;
	int m_poisonChance;
	float m_stunTimer;
	unsigned int m_poisonCounter;
	unsigned int m_deadlyStrikeChance;
	bool m_swiftAsACatPowerfulAsABear;
public:
	UnitEntity();
	UnitEntity(FLOAT3 pos);
	~UnitEntity();
	
	void update(float dt);
	virtual void updateSpecificUnitEntity(float dt) = 0;

	void addSkill(Skill *_skill);
	Skill *getSkill(unsigned int _id);
	vector<Skill*> getSkills();
	int getNrOfSkills();
	int getSkillIndex(Skill* _skill);

	virtual NetworkEntityMessage getUpdate();

	void increaseStrength(int _strength);
	void increaseAgility(int _agility);
	void increaseWits(int _wits);
	void increaseFortitude(int _fortitude);
	
	void alterAttackSpeed(float _value);
	void alterMentalDamage(float _value);
	void alterMovementSpeed(float _value);
	void alterPhysicalResistance(float _value);
	void setGreed(float _greed);
	void setTurretDuration(float _turretLife);
	void setMaxHealth(int _maxHealth);
	void setMovementSpeed(float _movementSpeed);
	void setAttackSpeed(float _attackSpeed);
	void setPhysicalDamage(float _minPhysicalDamage, float _maxPhysicalDamage);
	void setMentalDamage(float _minMentalDamage, float _maxMentalDamage);
	void setPhysicalResistance(float _physicalResistance);
	void setMentalResistance(float _mentalResistance);
	void setLifeStealChance(unsigned int _lifeStealChance);
	void setPoisonChance(unsigned int _poisonChance);
	void setDeadlyStrikeChance(unsigned int _deadlyStrikeChance);
	void setSwiftAsACatPowerfulAsABear(bool _val) { m_swiftAsACatPowerfulAsABear = _val; }
	void stun(float _time);

	int getStrength();
	int getAgility();
	int getWits();
	int getFortitude();

	int getHealth();
	int getMaxHealth();
	float getMovementSpeed();
	float getAttackSpeed();
	float getPhysicalDamage();
	float getMentalDamage();
	float getPhysicalResistance();
	float getMentalResistance();
	unsigned int getLifeStealChance();
	unsigned int getPoisonChance( );
	unsigned int getDeadlyStrikeChance();
	float getGreed();
	float getTurretDuration();

	unsigned int getLastDamageDealer();

	void takeDamage(unsigned int damageDealerId, int physicalDamage, int mentalDamage);
	void dealDamage(ServerEntity* target, int physicalDamage, int mentalDamage);
	void heal(int health);
};

#endif