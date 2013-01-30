#include "Player.h"

Player::Player(unsigned int id)
{
	this->m_id = id;
	this->m_resources = 20000;
	this->m_messageQueue = new MessageQueue();
	this->m_hero = new Hero();
	this->m_hero->setPosition(FLOAT3(50.0f, 0.0f, 50.0f));
	this->m_hero->setNextPosition(FLOAT3(50.0f, 0.0f, 50.0f));
	this->m_chainStrike = new ChainStrike();
	this->m_cloudOfDarkness = new CloudOfDarkness();
	this->m_stunningStrike = new StunningStrike();
	this->m_teleport = new Teleport();
	this->m_healingTouch = new HealingTouch();
	this->m_demonicPresence = new DemonicPresence();

	EntityHandler::addEntity(m_hero);

	this->m_skills.push_back(new PoisonStrike());
	this->m_skills.push_back(new LifestealingStrike());

	this->m_skills[0]->activate(this->m_hero->getId());
	this->m_skills[1]->activate(this->m_hero->getId());

	this->m_messageQueue->pushOutgoingMessage(new SkillBoughtMessage(Skill::AIM, this->m_id, this->m_resources));
	this->m_messageQueue->pushOutgoingMessage(new SkillBoughtMessage(Skill::LIFESTEALING_STRIKE, this->m_id, this->m_resources));
}

Player::~Player()
{
	for(int i = 0; i < this->m_skills.size(); i++)
	{
		delete this->m_skills[i];
	}

	delete this->m_chainStrike;
	delete this->m_cloudOfDarkness;
	delete this->m_stunningStrike;
	delete this->m_messageQueue;
	delete m_teleport;
	delete m_healingTouch;
	delete m_demonicPresence;
}

void Player::handleEntityMessage(EntityMessage e)
{
	this->m_hero->setNextPosition(e.getPos());
}

void Player::handleMsgMessage(Msg m)
{
	if(m.getText() == "Ready")
	{
		this->m_ready = true;
	}
	else if(m.getText() == "Start")
	{
		StartMessage *m = new StartMessage();
		m->type = Message::Type::Start;
		m->reciverId = 0;

		this->m_messageQueue->pushOutgoingMessage(m);
	}
}

void Player::handleAttackMessage(AttackMessage am)
{
	//Create a projectile
	FLOAT3 targetPos = am.getTargetPos();
	FLOAT3 direction = targetPos - this->m_hero->getPosition();
	direction.y = 0.0f;

	if(direction.length() > 0)
	{
		EntityHandler::addEntity(new Projectile(this->m_hero->getPosition(), direction, 2, 10.0f, this->m_hero));
	}
}

void Player::handleEntityAttackMessage(AttackEntityMessage eam)
{
	this->m_hero->setTarget(eam.getTargetId());
}

void Player::handleBuySkillMessage(NetworkBuySkillMessage bsm)
{
	if(this->m_skills.size() < 6)
	{
		bool skillBought = false;

		switch(bsm.getActionId())
		{
		case Skill::AIM:
			if(this->m_resources >= Aim::COST)
			{
				Aim* a = new Aim();
				a->activate(this->m_hero->getId());
				this->m_skills.push_back(a);
				this->m_resources = this->m_resources - Aim::COST;
				skillBought = true;
			}

			break;
		case Skill::CHAIN_STRIKE:
			if(this->m_resources >= ChainStrike::COST)
			{
				this->m_skills.push_back(new ChainStrike());
				this->m_resources = this->m_resources - ChainStrike::COST;
				skillBought = true;
			}

			break;
		case Skill::CLOUD_OF_DARKNESS:
			if(this->m_resources >= CloudOfDarkness::COST)
			{
				this->m_skills.push_back(new CloudOfDarkness());
				this->m_resources = this->m_resources - CloudOfDarkness::COST;
				skillBought = true;
			}

			break;
		case Skill::DEADLY_STRIKE:
			if(this->m_resources >= DeadlyStrike::COST)
			{
				this->m_skills.push_back(new DeadlyStrike());
				this->m_resources = this->m_resources - DeadlyStrike::COST;
				skillBought = true;
			}

			break;
		case Skill::GREED:
			if(this->m_resources >= Greed::COST)
			{
				this->m_skills.push_back(new Greed());
				this->m_resources = this->m_resources - Greed::COST;
				skillBought = true;
			}

			break;
		}

		if(skillBought == true)
		{
			this->m_messageQueue->pushOutgoingMessage(new SkillBoughtMessage(bsm.getActionId(), this->m_id, this->m_resources));
		}
	}
}

void Player::update(float _dt)
{
	m_chainStrike->update(_dt);
	m_cloudOfDarkness->update(_dt);
	m_stunningStrike->update(_dt);
	m_teleport->update(_dt);
	m_healingTouch->update(_dt);
	m_demonicPresence->update(_dt);
}

bool Player::getReady()
{
	return this->m_ready;
}

MessageQueue *Player::getMessageQueue()
{
	return this->m_messageQueue;
}

void Player::handleUseActionPositionMessage(NetworkUseActionPositionMessage usm)
{
	bool usedSomething = false;

	switch(usm.getActionId())
	{
	case Skill::MOVE:
		this->m_hero->setNextPosition(usm.getPosition());
		break;

	case Skill::CLOUD_OF_DARKNESS:
		usedSomething = this->m_cloudOfDarkness->activate(usm.getPosition(), this->m_hero->getId());
		break;

	case Skill::TELEPORT:
		usedSomething = this->m_teleport->activate(usm.getPosition(), this->m_hero->getId());
		break;

	case Skill::DEATH_TOWER:
		EntityHandler::addEntity(new Tower(usm.getPosition()));
		break;

	default:
		//Check if the player has the ability and use it
		break;
	}
	
	if(usedSomething)
	{
		this->m_messageQueue->pushOutgoingMessage(new CreateActionPositionMessage(usm.getActionId(), this->m_hero->getId(), usm.getPosition()));
	}
}

void Player::handleUseActionMessage(NetworkUseActionMessage usm)
{
	bool usedSomething = false;

	switch(usm.getActionId())
	{
	case Skill::STUNNING_STRIKE:
		usedSomething = m_stunningStrike->activate(this->m_hero->getId());
		break;
		
	case Skill::DEMONIC_PRESENCE:
		usedSomething = m_demonicPresence->activate(this->m_hero->getId());
		break;

	default:
		//Check if the player has the ability and use it
		break;
	}

	if(usedSomething)
	{
		this->m_messageQueue->pushOutgoingMessage(new CreateActionMessage(usm.getActionId(), this->m_hero->getId(), this->m_hero->getPosition()));
	}
}

void Player::handleUseActionTargetMessage(NetworkUseActionTargetMessage usm)
{
	bool usedSomething = false;

	switch(usm.getActionId())
	{
	case Skill::ATTACK:
		this->m_hero->setTarget(usm.getTargetId());
		break;

	case Skill::CHAIN_STRIKE:
		usedSomething = m_chainStrike->activate(usm.getTargetId(), m_hero->getId());
		break;

	case Skill::HEALING_TOUCH:
		usedSomething = m_healingTouch->activate(usm.getTargetId(), m_hero->getId());
		break;

	default:
		//Check if the player has the ability and use it
		break;
	}

	if(usedSomething)
	{
		this->m_messageQueue->pushOutgoingMessage(new CreateActionTargetMessage(usm.getActionId(), this->m_hero->getId(), usm.getTargetId(), this->m_hero->getPosition()));
	}
}