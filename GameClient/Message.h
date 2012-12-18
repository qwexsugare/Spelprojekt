#pragma once

#include "DataStructures.h"
#include <string>

enum MessageTypes{Start, Ready};

struct Message
{
	MessageTypes type;
	int senderId;
	int reciverId;
};

struct ReadyMessage
{
	int playerId;
	bool ready;
};

struct StartMessage
{
	int playerId;
};