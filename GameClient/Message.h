#pragma once

#include "DataStructures.h"
#include <string>

struct Message
{
	enum Type{Start, Ready};

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