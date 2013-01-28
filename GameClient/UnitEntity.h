#ifndef UNIT_ENTITY_H
#define UNIT_ENTITY_H

#include "ServerEntity.h"

class UnitEntity : public ServerEntity
{
protected:
	static const int MAX_STRENGTH = 20;
	static const int MAX_AGILITY = 20;
	static const int MAX_WITS = 20;
	static const int MAX_FORTITUDE = 20;

	int m_health;
	int m_maxHealth;

	int m_strength;
	int m_agility;
	int m_wits;
	int m_fortitude;

	float m_turretDuration;
	float m_greed;
	float m_movementSpeed;
	float m_attackSpeed;
	float m_physicalDamage;
	float m_mentalDamage;
	float m_physicalResistance;
	float m_mentalResistance;
	float m_lifeStealChance;
	float m_poisonChance;
	float m_stunTimer;
	unsigned int m_poisonCounter;
	unsigned int m_deadlyStrikeChance;
public:
	UnitEntity();
	UnitEntity(FLOAT3 pos);
	~UnitEntity();
	
	void update(float dt);
	virtual void updateSpecificUnitEntity(float dt) = 0;

	void increaseStrength(int _strength);
	void increaseAgility(int _agility);
	void increaseWits(int _wits);
	void increaseFortitude(int _fortitude);

	void setGreed(float _greed);
	void setTurretDuration(float _turretLife);
	void setMaxHealth(int _maxHealth);
	void setMovementSpeed(float _movementSpeed);
	void setAttackSpeed(float _attackSpeed);
	void setPhysicalDamage(float _physicalDamage);
	void setMentalDamage(float _mentalDamage);
	void setPhysicalResistance(float _physicalResistance);
	void setMentalResistance(float _mentalResistance);
	void setLifeStealChance(float _lifeStealChance);
	void setPoisonChance(float _poisonChance);
	void setDeadlyStrikeChance(unsigned int _deadlyStrikeChance);
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
	float getLifeStealChance();
	float getPoisonChance( );
	unsigned int getDeadlyStrikeChance();
	float getGreed();
	float getTurretDuration();

	void takeDamage(int physicalDamage, int mentalDamage);
	void dealDamage(ServerEntity* target, int physicalDamage, int mentalDamage);
	void heal(int health);
};

#endif