#pragma once

#include "DataStructures.h"
#include <string>

struct Message
{
	enum Type{Start, Ready, Collision, Attack, RemoveEntity, CreateAction, CreateActionPosition, CreateActionTarget, RemoveActionTarget, SkillBought, SelectHero, SkillUsed, EnemyDied};

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

	SelectHeroMessage(int _senderId, int _reciverId, int _heroId)
	{
		this->type = Type::SelectHero;
		this->senderId = _senderId;
		this->reciverId = _reciverId;
		this->heroId = _heroId;
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

	CreateActionMessage(unsigned int _actionId, unsigned int _senderId, FLOAT3 _position)
	{
		this->type = Type::CreateAction;
		this->reciverId = 1;
		this->actionId = _actionId;
		this->senderId = _senderId;
		this->position = _position;
	}
};

struct CreateActionPositionMessage : Message
{
	unsigned int actionId;
	unsigned int senderId;
	FLOAT3 position;

	CreateActionPositionMessage(unsigned int _actionId, unsigned int _senderId, FLOAT3 _position)
	{
		this->type = Type::CreateActionPosition;
		this->reciverId = 1;
		this->actionId = _actionId;
		this->senderId = _senderId;
		this->position = _position;
	}
};

struct CreateActionTargetMessage : Message
{
	unsigned int actionId;
	unsigned int senderId;
	unsigned int targetId;
	FLOAT3 position;

	CreateActionTargetMessage(unsigned int _actionId, unsigned int _senderId, unsigned int _targetId, FLOAT3 _position)
	{
		this->type = Type::CreateActionTarget;
		this->reciverId = 1;
		this->actionId = _actionId;
		this->senderId = _senderId;
		this->targetId = _targetId;
		this->position = _position;
	}
};

struct RemoveActionTargetMessage : Message
{
	unsigned int actionId;
	unsigned int senderId;
	unsigned int targetId;
	
	RemoveActionTargetMessage(unsigned int _actionId, unsigned int _senderId, unsigned int _targetId)
	{
		this->type = Type::RemoveActionTarget;
		this->reciverId = 1;
		this->actionId = _actionId;
		this->senderId = _senderId;
		this->targetId = _targetId;
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