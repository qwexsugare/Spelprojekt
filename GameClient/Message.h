#pragma once

#include "DataStructures.h"
#include <string>

struct Message
{
	int senderId;
	int reciverId;

	Message(int reciverId)
	{
		this->reciverId = reciverId;
	}

	~Message(void)
	{

	}
};

