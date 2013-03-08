#ifndef UNIT_ENTITY_H
#define UNIT_ENTITY_H

#include "ServerEntity.h"
#include "Skill.h"
#include "SkillIdHolder.h"
#include "Statistics.h"

class UnitEntity : public ServerEntity
{
protected:
	sf::Mutex m_mutex;

	vector<Skill*> m_skills;
	Skill* m_regularAttack;

	unsigned int m_lastDamageDealer;

	int m_health;
	int m_maxHealth;

	int m_strength;
	int m_agility;
	int m_wits;
	int m_fortitude;
	int m_turretConstruction;

	int m_turretDuration;
	float m_greed;
	float m_movementSpeedChange;
	float m_baseMovementSpeed;
	float m_movementSpeed;
	float m_baseAttackSpeed;
	float m_attackSpeedChange;
	float m_attackSpeed;
	float m_attackCooldown;
	float m_physicalDamage;
	float m_baseMentalDamage;
	float m_mentalDamageChange;
	float m_mentalDamage;
	float m_physicalResistance;
	float m_physicalResistanceChange;
	float m_basePhysicalResistance;
	float m_mentalResistance;
	float m_mentalResistanceChange;
	float m_baseMentalResistance;
	unsigned int m_lifeStealChance;
	int m_poisonChance;
	float m_stunTimer;
	unsigned int m_poisonCounter;
	unsigned int m_deadlyStrikeChance;
	bool m_swiftAsACatPowerfulAsABear;
	float m_frostTurretSlowEffectTimer;
	float m_frostTurretSlowEffectValue;
	int m_poisonStacks;
public:
	static const int MAX_STRENGTH = 20;
	static const int MAX_AGILITY = 20;
	static const int MAX_WITS = 20;
	static const int MAX_FORTITUDE = 20;
	static const int MAX_TURRET_CONSTRUCTION = 20;

	UnitEntity();
	UnitEntity(FLOAT3 pos);
	virtual ~UnitEntity();

	void addPoisonStack();
	void applyFrostTurretSlowEffect(float _value);
	
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
	void increaseTurretConstruction(int _turretConstruction);
	bool isSlowedByFrostTurret();
	
	void alterAttackSpeed(float _value);
	void alterMentalDamage(float _value);
	void alterMovementSpeed(float _value);
	void alterPhysicalResistance(float _value);
	void alterTurretDuration(int _turretDuration);
	void setGreed(float _greed);
	void setMaxHealth(int _maxHealth);
	void setMovementSpeed(float _movementSpeed);
	void setAttackSpeed(float _attackSpeed);
	void setPhysicalDamage(float _physicalDamage);
	void setMentalDamage(float _mentalDamage);
	void setPhysicalResistance(float _physicalResistance);
	void setMentalResistance(float _mentalResistance);
	void setSwiftAsACatPowerfulAsABear(bool _val) { m_swiftAsACatPowerfulAsABear = _val; }
	void setPoisonCounter(int _poisonCounter);
	void stun(float _time);

	int getStrength();
	int getAgility();
	int getWits();
	int getFortitude();
	int getPoisonStacks()const;
	int getHealth();
	int getMaxHealth();
	int getTurretConstruction();
	float getMovementSpeed();
	float getAttackSpeed();
	float getPhysicalDamage();
	float getMentalDamage();
	float getPhysicalResistance();
	float getMentalResistance();
	float getGreed();
	int getTurretDuration();
	int getPoisonCounter();

	unsigned int getLastDamageDealer();

	void takeDamage(unsigned int damageDealerId, int physicalDamage, int mentalDamage);
	void dealDamage(ServerEntity* target, int physicalDamage, int mentalDamage);
	void heal(int health);
	void attack(unsigned int target);
};

#endif