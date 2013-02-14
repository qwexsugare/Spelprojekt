#ifndef PLAYER_H
#define PLAYER_H

#include "DataStructures.h"
#include "MessageQueue.h"
#include "EntityHandler.h"
#include "Hero.h"
#include "Projectile.h"
#include "Skills.h"
#include "Tower.h"

#include "NetworkUseActionMessage.h"
#include "NetworkUseActionPositionMessage.h"
#include "NetworkUseActionTargetMessage.h"
#include "NetworkBuySkillMessage.h"
#include "NetworkReadyMessage.h"
#include "NetworkSelectHeroMessage.h"

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
	
	void assignHero(Hero::HERO_TYPE _type);
	void spawnHero();
	Hero::HERO_TYPE getHeroType()const;
	int getId()const;
	Hero* getHero();
	void handleUseActionPositionMessage(NetworkUseActionPositionMessage usm);
	void handleUseActionMessage(NetworkUseActionMessage usm);
	void handleUseActionTargetMessage(NetworkUseActionTargetMessage usm);
	void handleBuySkillMessage(NetworkBuySkillMessage bsm);
	void handleReadyMessage(NetworkReadyMessage rm);
	void handleSelectHeroMessage(NetworkSelectHeroMessage shm);
	bool hasChosenHero()const { return m_hero; }
	void update(float _dt);
	MessageQueue *getMessageQueue();
	void addResources(unsigned int resources);

	bool getReady();
};

#endif