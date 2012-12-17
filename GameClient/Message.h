#pragma once

#include "DataStructures.h"
#include <string>

enum MessageTypes{AddEntity, RemoveEntity, MoveEntity};

struct Message
{
	MessageTypes type;
	int senderId;
	int reciverId;
};

struct AddEntityMessage : public Message
{
	FLOAT3 position;
};

struct MoveMessage : public Message
{
	FLOAT3 position;
};