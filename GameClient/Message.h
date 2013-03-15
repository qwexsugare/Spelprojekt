#pragma once

#include "DataStructures.h"
#include <string>

struct Message
{
	enum Type{Start, Ready, Collision, Attack, RemoveEntity, CreateAction, CreateActionPosition, CreateActionTarget, RemoveActionTarget, SkillBought,
		SelectHero, SkillUsed, EnemyDied, EnemyReachedGoal,initEntities,updateEntity,updateEntityHealth, HeroDied, JoinedGame, AttributeUpdate,TXTMSG};

	Type type;
	int senderId;
	int reciverId;

	Message()
	{

	}

	Message(Type _type, int _senderId, int _reciverId)
	{
		this->type = _type;
		this->senderId = _senderId;
		this->reciverId = _reciverId;
	}
};

struct ReadyMessage : Message
{
	bool ready;

	ReadyMessage(int _senderId, int _reciverId, bool _ready)
	{
		this->type = Type::Ready;
		this->senderId = _senderId;
		this->reciverId = _reciverId;
		this->ready = _ready;
	}
};

struct StartMessage : Message
{

};

struct SelectHeroMessage : Message
{
	int heroId;
	int weaponId;

	SelectHeroMessage(int _senderId, int _reciverId, int _heroId, int _weaponId)
	{
		this->type = Type::SelectHero;
		this->senderId = _senderId;
		this->reciverId = _reciverId;
		this->heroId = _heroId;
		this->weaponId = _weaponId;
	}
};

struct CollisionMessage : Message
{
	int affectedDudeId;
};

struct DamageMessage : Message
{
	int damage;
};

struct RemoveServerEntityMessage : Message
{
	int removedId;

	RemoveServerEntityMessage(int _senderId, int _reciverId, int _removedId)
	{
		this->type = Type::RemoveEntity;
		this->senderId = _senderId;
		this->reciverId = _reciverId;
		this->removedId = _removedId;
	}
};

struct CreateActionMessage : Message
{
	unsigned int actionId;
	unsigned int senderId;
	FLOAT3 position;
	float animationSpeed;

	CreateActionMessage(unsigned int _actionId, unsigned int _senderId, FLOAT3 _position, float _animationSpeed = 1.0f)
	{
		this->type = Type::CreateAction;
		this->reciverId = 1;
		this->actionId = _actionId;
		this->senderId = _senderId;
		this->position = _position;
		this->animationSpeed = _animationSpeed;
	}
};

struct CreateActionPositionMessage : Message
{
	unsigned int actionId;
	unsigned int senderId;
	FLOAT3 position;
	float animationSpeed;

	CreateActionPositionMessage(unsigned int _actionId, unsigned int _senderId, FLOAT3 _position, float _animationSpeed = 1.0f)
	{
		this->type = Type::CreateActionPosition;
		this->reciverId = 1;
		this->actionId = _actionId;
		this->senderId = _senderId;
		this->position = _position;
		this->animationSpeed = _animationSpeed;
	}
};

struct CreateActionTargetMessage : Message
{
	unsigned int actionId;
	unsigned int senderId;
	unsigned int targetId;
	FLOAT3 position;
	float animationSpeed;

	CreateActionTargetMessage(unsigned int _actionId, unsigned int _senderId, unsigned int _targetId, FLOAT3 _position, float _animationSpeed = 1.0f)
	{
		this->type = Type::CreateActionTarget;
		this->reciverId = 1;
		this->actionId = _actionId;
		this->senderId = _senderId;
		this->targetId = _targetId;
		this->position = _position;
		this->animationSpeed = _animationSpeed;
	}
};

struct RemoveActionTargetMessage : Message
{
	unsigned int actionId;
	unsigned int senderId;
	unsigned int targetId;
	FLOAT3 position;
	
	RemoveActionTargetMessage(unsigned int _actionId, unsigned int _senderId, unsigned int _targetId, FLOAT3 _position = FLOAT3(0.0f, 0.0f, 0.0f))
	{
		this->type = Type::RemoveActionTarget;
		this->reciverId = 1;
		this->actionId = _actionId;
		this->senderId = _senderId;
		this->targetId = _targetId;
		this->position = _position;
	}
};

struct SkillBoughtMessage : Message
{
	unsigned int actionId;
	unsigned int playerId;
	unsigned int resources;

	SkillBoughtMessage(unsigned int _actionId, unsigned int _playerId, unsigned int _resources)
	{
		this->type = Type::SkillBought;
		this->reciverId = 1;
		this->actionId = _actionId;
		this->playerId = _playerId;
		this->resources = _resources;
	}
};

struct SkillUsedMessage : Message
{
	unsigned int actionId;
	unsigned int playerId;
	unsigned int actionIndex;
	float cooldown;

	SkillUsedMessage(unsigned int _actionId, unsigned int _playerId, unsigned int _actionIndex, float _cooldown)
	{
		this->type = Type::SkillUsed;
		this->reciverId = 1;
		this->actionId = _actionId;
		this->playerId = _playerId;
		this->actionIndex = _actionIndex;
		this->cooldown = _cooldown;
	}
};

struct EnemyDiedMessage : Message
{
	unsigned int victimId;
	unsigned int killerId;
	int resources;

	EnemyDiedMessage(unsigned int _victimId, unsigned int _killerId, int resources)
	{
		this->type = Type::EnemyDied;
		this->reciverId = 0;
		this->victimId = _victimId;
		this->killerId = _killerId;
		this->resources = resources;
	}
};

struct EnemyReachedGoalMessage : Message
{
	unsigned int enemyId;
	FLOAT3 position;

	EnemyReachedGoalMessage(unsigned int _enemyId, FLOAT3 _position)
	{
		this->type = Type::EnemyReachedGoal;
		this->reciverId = 0;
		this->enemyId = _enemyId;
		this->position = _position;
	}
};

struct InitEntityMessage :Message
{
	unsigned short modelid;
	unsigned short id;
	float xPos;
	float zPos;
	float sx;
	float sz;
	float ex;
	float ez;
	float yRot;
	float scale;
	int health;
	unsigned short subtype;
	unsigned short entityType;
	unsigned short weaponType;
	float movementspeed;
	InitEntityMessage(unsigned short ET, unsigned short subtype, unsigned short modelid, unsigned short weaponType,unsigned short id, float xpos, float zpos, float yrot, float scale,int health,float sx, float sz,float ex, float ez,float mms)
	{
		this->subtype = subtype;
		this->id=id;
		this->reciverId=1;
		this->type=Type::initEntities;
		this->modelid=modelid;
		this->weaponType = weaponType;
		this->xPos=xpos;
		this->zPos=zpos;
		this->yRot=yrot;
		this->scale=scale;
		this->entityType=ET;
		this->health=health;
		this->sx=sx;
		this->sz=sz;
		this->ex=ex;
		this->ez=ez;
		this->movementspeed=mms;
	}
};

struct UpdateEntityMessage :Message
{
	unsigned short id;
	float xPos,zPos,yRot,sx,ex,sz,ez;
	float movementspeed;
	UpdateEntityMessage(unsigned short id, float xpos, float zpos, float yrot,float sx,float sz,float ex, float ez,float mms)
	{
		this->type=Type::updateEntity;
		this->reciverId = 1;
		this->id=id;
		this->xPos=xpos;
		this->zPos=zpos;
		this->yRot=yrot;
		this->sx=sx;
		this->sz=sz;
		this->ex=ex;
		this->ez=ez;
		this->movementspeed=mms;
	}
};

struct updateEntityHealth :Message
{
	int id;
	int health;
	updateEntityHealth(int id, int health)
	{
		this->type=Type::updateEntityHealth;
		this->reciverId = 1;
		this->id=id;
		this->health=health;
	}
};

struct HeroDiedMessage : Message
{
	unsigned int heroId;

	HeroDiedMessage(unsigned int _heroId, unsigned int _heroOwner)
	{
		this->type = Type::HeroDied;
		this->reciverId = _heroOwner;
		this->heroId = _heroId;
	}
};

struct JoinedGameMessage : Message
{
	unsigned int id;

	JoinedGameMessage(unsigned int _id)
	{
		this->type = Message::Type::JoinedGame;
		this->id = _id;
		this->reciverId = 0;
	}
};

struct AttributeUpdateMessage : Message
{
	unsigned int id;
	int strength;
	int wits;
	int fortitude;
	int agility;
	int towerConstruction;
	int maxHealth;
	float mentalDamage;
	float physicalDamage;
	float mentalResistance;
	float physicalResistance;

	AttributeUpdateMessage(unsigned int _id, int _strength, int _wits, int _fortitude, int _agility, int _towerConstruction,
		int _maxHealth, float _mentalDamage, float _physicalDamage, float _mentalResistance, float _physicalResistance)
	{
		this->type = Message::Type::AttributeUpdate;
		this->reciverId = 1;

		id = _id;
		strength = _strength;
		wits = _wits;
		fortitude = _fortitude;
		agility = _agility;
		towerConstruction = _towerConstruction;
		maxHealth = _maxHealth;
		mentalDamage = _mentalDamage;
		physicalDamage = _physicalDamage;
		mentalResistance = _mentalResistance;
		physicalResistance = _physicalResistance;
	}
};

struct TextMessage : Message
{
	string text;
	TextMessage(string text)
	{
		this->text=text;
	}
};