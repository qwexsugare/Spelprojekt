#ifndef PLAYER_H
#define PLAYER_H

#include "DataStructures.h"
#include "EntityMessage.h"
#include "Msg.h"
#include "AttackMessage.h"
#include "MessageQueue.h"
#include "EntityHandler.h"
#include "Hero.h"
#include "Projectile.h"
#include "AttackEntityMessage.h"
#include "UseSkillMessage.h"
#include "UsePositionalSkillMessage.h"
#include "Skills.h"
#include "Tower.h"

#include "NetworkUseActionMessage.h"
#include "NetworkUseActionPositionMessage.h"
#include "NetworkUseActionTargetMessage.h"
#include "NetworkBuySkillMessage.h"

class Player
{
private:
	unsigned int m_id;
	unsigned int m_resources;

	bool m_ready;
	MessageQueue *m_messageQueue;
	Hero *m_hero;
public:
	Player(unsigned int id);
	~Player();

	void handleEntityMessage(EntityMessage e);
	void handleMsgMessage(Msg m);
	void handleAttackMessage(AttackMessage am);
	void handleEntityAttackMessage(AttackEntityMessage eam);
	void handleUseActionPositionMessage(NetworkUseActionPositionMessage usm);
	void handleUseActionMessage(NetworkUseActionMessage usm);
	void handleUseActionTargetMessage(NetworkUseActionTargetMessage usm);
	void handleBuySkillMessage(NetworkBuySkillMessage bsm);
	void update(float _dt);
	MessageQueue *getMessageQueue();

	bool getReady();
};

#endif