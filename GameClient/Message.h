#pragma once

#include "DataStructures.h"
#include <string>

struct Message
{
	enum Type{Start, Ready, Collision};

	Type type;
	int senderId;
	int reciverId;
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