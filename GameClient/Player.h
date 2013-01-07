#ifndef PLAYER_H
#define PLAYER_H

#include "DataStructures.h"
#include "EntityMessage.h"
#include "Msg.h"
#include "MessageQueue.h"
#include "EntityHandler.h"
#include "Hero.h"

class Player
{
private:
	unsigned int m_id;

	bool m_ready;
	MessageQueue *m_messageQueue;
	Hero *m_hero;
public:
	Player(unsigned int id);
	~Player();

	void handleEntityMessage(EntityMessage e);
	void handleMsgMessage(Msg m);
	void update();
	MessageQueue *getMessageQueue();

	bool getReady();
};

#endif