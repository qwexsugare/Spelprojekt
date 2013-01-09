#pragma once

#include "DataStructures.h"
#include <string>

struct Message
{
	enum Type{Start, Ready, Collision, Attack, RemoveEntity};

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
};

struct StartMessage : Message
{

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