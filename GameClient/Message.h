#pragma once

#include "DataStructures.h"
#include <string>

struct Message
{
	int type;
	int senderId;
	int reciverId;
};

struct MoveMessage : public Message
{
	FLOAT3 position;
};