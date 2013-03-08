#include "UnitEntity.h"
#include "MyAlgorithms.h"

UnitEntity::UnitEntity() : ServerEntity()
{
	this->m_regularAttack = NULL;

	this->m_health = 100;
	this->m_maxHealth = 100;
	this->m_strength = 1;
	this->m_agility = 1;
	this->m_wits = 1;
	this->m_fortitude = 1;
	this->m_turretConstruction = 1;

	this->m_baseAttackSpeed = 2.0f;
	this->m_attackSpeedChange = 0.0f;
	this->m_attackSpeed = m_baseAttackSpeed + m_attackSpeedChange;
	this->m_physicalDamage = 1.0f;
	this->m_mentalDamage = 1.0f;

	this->m_baseMovementSpeed = 2.0f;
	this->m_movementSpeedChange = 0.0f;
	this->m_movementSpeed = m_baseMovementSpeed + m_movementSpeedChange;
	
	this->m_basePhysicalResistance = 1.0f;
	this->m_physicalResistanceChange = 0.0f;
	this->m_physicalResistance = m_basePhysicalResistance + m_physicalResistanceChange;
	
	this->m_baseMentalResistance = 1.0f;
	this->m_mentalResistanceChange = 0.0f;
	this->m_mentalResistance = m_baseMentalResistance + m_mentalResistanceChange;

	this->m_mentalResistance = 1.0f;
	this->m_lifeStealChance = 0;
	this->m_poisonChance = 0;
	this->m_deadlyStrikeChance = 0;
	this->m_poisonCounter = 0;
	this->m_greed = 1.0f;
	this->m_turretDuration = 1;
	this->m_attackCooldown = 0.0f;
	
	m_swiftAsACatPowerfulAsABear = false;
	m_frostTurretSlowEffectTimer = 0.0f;
	m_frostTurretSlowEffectValue = 0.0f;
	m_poisonStacks = 0;
}

UnitEntity::UnitEntity(FLOAT3 pos) : ServerEntity(pos)
{
	this->m_regularAttack = NULL;

	this->m_health = 100;
	this->m_maxHealth = 100;
	this->m_strength = 1;
	this->m_agility = 1;
	this->m_wits = 1;
	this->m_fortitude = 1;

	this->m_baseAttackSpeed = 2.0f;
	this->m_attackSpeedChange = 0.0f;
	this->m_attackSpeed = m_baseAttackSpeed + m_attackSpeedChange;

	this->m_baseMovementSpeed = 2.0f;
	this->m_movementSpeedChange = 0.0f;
	this->m_movementSpeed = m_baseMovementSpeed + m_movementSpeedChange;
	
	this->m_basePhysicalResistance = 1.0f;
	this->m_physicalDamage = 1.0f;
	this->m_mentalDamage = 1.0f;
	this->m_physicalResistanceChange = 0.0f;
	this->m_physicalResistance = m_basePhysicalResistance + m_physicalResistanceChange;
	
	this->m_baseMentalResistance = 1.0f;
	this->m_mentalResistanceChange = 0.0f;
	this->m_mentalResistance = m_baseMentalResistance + m_mentalResistanceChange;
	
	this->m_baseMentalDamage = 1.0f;
	this->m_mentalDamageChange = 0.0f;
	this->m_mentalDamage = m_baseMentalDamage + m_mentalDamageChange;

	this->m_lifeStealChance = 0;
	this->m_poisonChance = 0;
	this->m_deadlyStrikeChance = 0;
	this->m_poisonCounter = 0;
	this->m_greed = 1.0f;
	this->m_turretDuration = 10.0f;
	this->m_attackCooldown = 0.0f;
	
	m_swiftAsACatPowerfulAsABear = false;
	m_frostTurretSlowEffectTimer = 0.0f;
	m_frostTurretSlowEffectValue = 0.0f;
	m_poisonStacks = 0;
}

UnitEntity::~UnitEntity()
{
	for(int i = 0; i < this->m_skills.size(); i++)
	{
		delete this->m_skills[i];
	}

	delete this->m_regularAttack;
}

void UnitEntity::addPoisonStack()
{
	m_poisonStacks++;
}

void UnitEntity::applyFrostTurretSlowEffect(float _value)
{
	// If the unit is already affected, reset his movementspeed debuff before applying the new one
	if(m_frostTurretSlowEffectTimer > 0.0f)
	{
		this->alterMovementSpeed(-m_frostTurretSlowEffectValue);
	}

	m_frostTurretSlowEffectTimer = 10.0f;
	m_frostTurretSlowEffectValue = _value;
	this->alterMovementSpeed(m_frostTurretSlowEffectValue);
}

void UnitEntity::addSkill(Skill *_skill)
{
	this->m_mutex.Lock();
	this->m_skills.push_back(_skill);
	this->m_mutex.Unlock();
}

void UnitEntity::alterMentalDamage(float _value)
{
	m_mentalDamageChange += _value;
	m_mentalDamage = m_baseMentalDamage + m_mentalDamageChange;
}

void UnitEntity::alterAttackSpeed(float _value)
{
	m_attackSpeedChange += _value;
	m_attackSpeed = m_baseAttackSpeed + m_attackSpeedChange;

	if(this->m_attackCooldown > this->m_attackSpeed)
	{
		this->m_attackCooldown = this->m_attackSpeed;
	}
}

void UnitEntity::alterMovementSpeed(float _value)
{
	m_movementSpeedChange += _value;
	m_movementSpeed = m_baseMovementSpeed + m_movementSpeedChange;
}

void UnitEntity::alterPhysicalResistance(float _value)
{
	m_physicalResistanceChange += _value;
	m_physicalResistance = m_basePhysicalResistance + m_physicalResistanceChange;
}

vector<Skill*> UnitEntity::getSkills()
{
	return this->m_skills;
}

Skill *UnitEntity::getSkill(unsigned int _id)
{
	Skill *result = NULL;

	for(int i = 0; i < this->m_skills.size(); i++)
	{
		if(this->m_skills[i]->getId() == _id && this->m_skills[i]->getCurrentCooldown() == 0.0f)
		{
			result = this->m_skills[i];
			i = this->m_skills.size();		
		}
	}

	return result;
}

int UnitEntity::getNrOfSkills()
{
	return this->m_skills.size();
}

int UnitEntity::getSkillIndex(Skill* _skill)
{
	int index = -1;
	
	for(int i = 0; i < this->m_skills.size(); i++)
	{
		if(this->m_skills[i] == _skill)
		{
			index = i;
			i = this->m_skills.size();		
		}
	}

	return index;
}

void UnitEntity::increaseStrength(int _strength)
{
	// Prevents the attribute gain to exceed max and minimizes the gain.
	if(_strength+m_strength > UnitEntity::MAX_STRENGTH)
		_strength = UnitEntity::MAX_STRENGTH - m_strength;
	
	this->m_physicalDamage += _strength * 5;
	m_basePhysicalResistance -= _strength * 0.02f;
	this->m_physicalResistance = m_basePhysicalResistance + m_physicalResistanceChange;
	this->m_strength += _strength;
}

void UnitEntity::increaseAgility(int _agility)
{
	// Prevents the attribute gain to exceed max and minimizes the gain.
	if(_agility+m_agility > UnitEntity::MAX_AGILITY)
		_agility = UnitEntity::MAX_AGILITY - m_agility;
	
	this->m_baseMovementSpeed += _agility * 0.1f;
	this->m_movementSpeed = m_baseMovementSpeed + m_movementSpeedChange;
	this->m_baseAttackSpeed += _agility * 0.05f;
	this->m_attackSpeed = m_baseAttackSpeed + m_attackSpeedChange;
	this->m_agility += _agility;
}

void UnitEntity::increaseWits(int _wits)
{
	// Prevents the attribute gain to exceed max and minimizes the gain.
	if(_wits+this->m_wits > UnitEntity::MAX_WITS)
		_wits = UnitEntity::MAX_WITS - this->m_wits;

	m_baseMentalDamage += _wits * 5;
	m_mentalDamage = m_baseMentalDamage + m_mentalDamageChange;
	this->m_turretDuration += _wits * 0.5f;
	m_wits += _wits;
}

void UnitEntity::increaseFortitude(int _fortitude)
{	
	// Prevents the attribute gain to exceed max and minimizes the gain.
	if(_fortitude+m_fortitude > UnitEntity::MAX_FORTITUDE)
		_fortitude = UnitEntity::MAX_FORTITUDE - m_fortitude;

	m_maxHealth += 100*_fortitude;
	m_health += 100*_fortitude;
	m_baseMentalResistance -= _fortitude * 0.02f;
	m_mentalResistance = m_baseMentalResistance + m_mentalResistanceChange;
	m_fortitude += _fortitude;
}

void UnitEntity::increaseTurretConstruction(int _towerConstruction)
{
	if(_towerConstruction + this->m_turretConstruction > UnitEntity::MAX_TURRET_CONSTRUCTION)
	{
		_towerConstruction = UnitEntity::MAX_TURRET_CONSTRUCTION - this->m_turretConstruction;
	}

	this->m_turretConstruction += _towerConstruction;
}

bool UnitEntity::isSlowedByFrostTurret()
{
	return m_frostTurretSlowEffectTimer > 0.0f;
}

void UnitEntity::setMaxHealth(int _maxHealth)
{
	this->m_maxHealth = _maxHealth;
}

void UnitEntity::setMovementSpeed(float _movementSpeed)
{
	this->m_movementSpeed = _movementSpeed;
}

void UnitEntity::setAttackSpeed(float _attackSpeed)
{
	this->m_attackSpeed = _attackSpeed;
}

void UnitEntity::setPhysicalDamage(float _physicalDamage)
{
	this->m_physicalDamage = _physicalDamage;
}

void UnitEntity::setMentalDamage(float _mentalDamage)
{
	this->m_mentalDamage = _mentalDamage;

}

void UnitEntity::setPhysicalResistance(float _physicalResistance)
{
	this->m_physicalResistance = _physicalResistance;
}

void UnitEntity::setMentalResistance(float _mentalResistance)
{
	this->m_mentalResistance = _mentalResistance;
}

void UnitEntity::setPoisonCounter(int _poisonCounter)
{
	this->m_poisonCounter = _poisonCounter;
}

void UnitEntity::setGreed(float _greed)
{
	this->m_greed = _greed;
}

void UnitEntity::alterTurretDuration(int _turretDuration)
{
	this->m_turretDuration += _turretDuration;
}

int UnitEntity::getStrength()
{
	return this->m_strength;
}

int UnitEntity::getAgility()
{
	return this->m_agility;
}

int UnitEntity::getWits()
{
	return this->m_wits;
}

int UnitEntity::getFortitude()
{
	return this->m_fortitude;
}

int UnitEntity::getTurretConstruction()
{
	return this->m_turretConstruction;
}

int UnitEntity::getPoisonStacks()const
{
	return m_poisonStacks;
}

int UnitEntity::getHealth()
{
	return this->m_health;
}

int UnitEntity::getMaxHealth()
{
	return this->m_maxHealth;
}

float UnitEntity::getMovementSpeed()
{
	return this->m_movementSpeed;
}

float UnitEntity::getAttackSpeed()
{
	return this->m_attackSpeed;
}

float UnitEntity::getPhysicalDamage()
{
	return random(0,m_physicalDamage);
}

float UnitEntity::getMentalDamage()
{
	return random(0, m_mentalDamage);
}

float UnitEntity::getPhysicalResistance()
{
	return this->m_physicalResistance;
}

float UnitEntity::getMentalResistance()
{
	return this->m_mentalResistance;
}

float UnitEntity::getGreed()
{
	return this->m_greed;
}

int UnitEntity::getTurretDuration()
{
	return this->m_turretDuration;
}

unsigned int UnitEntity::getLastDamageDealer()
{
	return this->m_lastDamageDealer;
}

int UnitEntity::getPoisonCounter()
{
	return this->m_poisonCounter;
}

#include <sstream>
void UnitEntity::takeDamage(unsigned int damageDealerId, int physicalDamage, int mentalDamage)
{
	int networkId=Statistics::convertSimonsIdToRealId(damageDealerId);
	if(networkId>=0)
	{
		Statistics::getStatisticsPlayer(networkId).addMentalDamageDealth(mentalDamage* this->m_mentalResistance);
		Statistics::getStatisticsPlayer(networkId).addPhysicalDamageDealth(physicalDamage* this->m_physicalResistance);
	}

	networkId=Statistics::convertSimonsIdToRealId(this->m_id);
	if(networkId>=0)
	{
		Statistics::getStatisticsPlayer(networkId).addMentalDamageRecived(mentalDamage* this->m_mentalResistance);
		Statistics::getStatisticsPlayer(networkId).addPhysicalDamageRecived(physicalDamage* this->m_physicalResistance);
	}

	this->m_health = this->m_health - physicalDamage * this->m_physicalResistance;
	this->m_health = this->m_health - mentalDamage * this->m_mentalResistance;
	this->m_lastDamageDealer = damageDealerId;
	this->m_messageQueue->pushOutgoingMessage(new updateEntityHealth(this->getId(),(float)((float)this->m_health / (float)this->m_maxHealth) * 1000.0f));

	// Dbg
	stringstream ss;
	ss << "Unit with " << m_physicalResistance << " phys res and " << m_mentalResistance << " mental res took damage" << endl;
	OutputDebugString(ss.str().c_str());
}

void UnitEntity::dealDamage(ServerEntity* target, int physicalDamage, int mentalDamage)
{
	if(m_swiftAsACatPowerfulAsABear)
	{
		//G�r saacpaab saker
		if(random(1, 10) == 1)
			target->takeDamage(this->m_id, INT_MAX, INT_MAX);
		else
			physicalDamage*=3;

		m_swiftAsACatPowerfulAsABear = false;
	}

	target->takeDamage(this->m_id, physicalDamage, mentalDamage);
}

void UnitEntity::heal(int health)
{
	int networkId=Statistics::convertSimonsIdToRealId(this->m_id);
	if(networkId>=0)
	{
		Statistics::getStatisticsPlayer(networkId).increaseHealdAmount(health);
	}
	this->m_health = min(m_health+health, m_maxHealth);
	this->m_messageQueue->pushOutgoingMessage(new updateEntityHealth(this->getId(),(float)((float)this->m_health / (float)this->m_maxHealth) * 1000.0f));
}

void UnitEntity::stun(float _time)
{
	m_stunTimer = max(m_stunTimer, _time);
}

void UnitEntity::update(float dt)
{
	this->m_mutex.Lock();

	for(int i = 0; i < this->m_skills.size(); i++)
	{
		this->m_skills[i]->update(dt);
	}

	this->m_mutex.Unlock();

	if(m_frostTurretSlowEffectTimer != 0.0f)
	{
		m_frostTurretSlowEffectTimer = max(m_frostTurretSlowEffectTimer-dt, 0.0f);
		if(m_frostTurretSlowEffectTimer == 0.0f)
		{
			this->alterMovementSpeed(-m_frostTurretSlowEffectValue);
			m_frostTurretSlowEffectValue = 0.0f;
		}
	}

	if(this->m_attackCooldown > 0.0f)
	{
		this->m_attackCooldown = this->m_attackCooldown - dt;
	}

	if(m_stunTimer <= 0.0f)
	{
		this->updateSpecificUnitEntity(dt);
	}
	else
	{
		this->m_stunTimer -= dt;
	}
}

NetworkEntityMessage UnitEntity::getUpdate()
{
	float xdir=this->getDirection().x*this->getMovementSpeed();
	float zdir=this->getDirection().z*this->getMovementSpeed();
	/*
	if(this->getPosition().x==this->getDirection().x&&this->getPosition().z==this->getDirection().z)
	{
		xdir=0;
		zdir=0;
	}*/

	
	NetworkEntityMessage e = NetworkEntityMessage(this->m_id, this->m_position.x, this->m_position.z,this->m_rotation.x,this->m_position.x,this->m_position.z,this->getEndPos().x,this->getEndPos().z,this->getMovementSpeed());


	return e;
}

void UnitEntity::attack(unsigned int target)
{
	if(this->m_regularAttack != NULL)
	{
		SkillIdHolder skillIdHolder = SkillIdHolder();

		for(int i = 0; i < this->m_skills.size(); i++)
		{
			if(skillIdHolder.getActive(this->m_skills[i]->getId()) == false)
			{
				this->m_skills[i]->activate(target, this->m_id);
			}
		}

		this->m_regularAttack->activate(target, this->m_id);
	}
}