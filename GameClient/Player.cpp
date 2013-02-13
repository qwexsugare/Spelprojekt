#include "Player.h"
#include "Heroes.h"

Player::Player(unsigned int id)
{
	this->m_id = id;
	this->m_resources = 20000;
	this->m_messageQueue = new MessageQueue();
	this->m_hero = new Engineer(this->m_id);
	this->m_hero->setPosition(FLOAT3(60.0f, 0.0f, 60.0f));

	EntityHandler::addEntity(m_hero);
}

Player::~Player()
{
	delete this->m_messageQueue;
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
	if(this->m_hero->getNrOfSkills() < 6)
	{
		bool skillBought = false;
		Skill* a = NULL;

		switch(bsm.getActionId())
		{
		case Skill::STRENGTH:

			break;

		case Skill::AGILITY:

			break;

		case Skill::WITS:

			break;

		case Skill::FORTITUDE:

			break;

		case Skill::AIM:
			if(this->m_resources >= Aim::COST)
			{
				a = new Aim();
				a->activate(this->m_hero->getId());
				this->m_resources = this->m_resources - Aim::COST;
				skillBought = true;
			}

			break;

		case Skill::DEADLY_STRIKE:
			if(this->m_resources >= DeadlyStrike::COST)
			{
				a = new DeadlyStrike();
				a->activate(this->m_hero->getId());
				this->m_resources = this->m_resources - DeadlyStrike::COST;
				skillBought = true;
			}

			break;

		case Skill::GREED:
			if(this->m_resources >= Greed::COST)
			{
				a = new Greed();
				a->activate(this->m_hero->getId());
				this->m_resources = this->m_resources - Greed::COST;
				skillBought = true;
			}

			break;

		case Skill::LIFESTEALING_STRIKE:
			if(this->m_resources >= LifestealingStrike::COST)
			{
				a = new LifestealingStrike();
				a->activate(this->m_hero->getId());
				this->m_resources = this->m_resources - LifestealingStrike::COST;
				skillBought = true;
			}

			break;

		case Skill::PHYSICAL_RESISTANCE:
			if(this->m_resources >= Greed::COST)
			{
				a = new PhysicalResistance();
				a->activate(this->m_hero->getId());
				this->m_resources = this->m_resources - PhysicalResistance::COST;
				skillBought = true;
			}

			break;

		case Skill::MENTAL_RESISTANCE:
			if(this->m_resources >= MentalResistance::COST)
			{
				a = new MentalResistance();
				a->activate(this->m_hero->getId());
				this->m_resources = this->m_resources - MentalResistance::COST;
				skillBought = true;
			}

			break;

		case Skill::POISON_STRIKE:
			if(this->m_resources >= PoisonStrike::COST)
			{
				a = new PoisonStrike();
				a->activate(this->m_hero->getId());
				this->m_resources = this->m_resources - PoisonStrike::COST;
				skillBought = true;
			}

			break;

		case Skill::CHAIN_STRIKE:
			if(this->m_resources >= ChainStrike::COST)
			{
				a = new ChainStrike();
				this->m_resources = this->m_resources - ChainStrike::COST;
				skillBought = true;
			}

			break;

		case Skill::STUNNING_STRIKE:
			if(this->m_resources >= StunningStrike::COST)
			{
				a = new StunningStrike();
				this->m_resources = this->m_resources - StunningStrike::COST;
				skillBought = true;
			}

			break;

		case Skill::CLOUD_OF_DARKNESS:
			if(this->m_resources >= CloudOfDarkness::COST)
			{
				a = new CloudOfDarkness();
				this->m_resources = this->m_resources - CloudOfDarkness::COST;
				skillBought = true;
			}

			break;

		case Skill::HEALING_TOUCH:
			if(this->m_resources >= HealingTouch::COST)
			{
				a = new HealingTouch();
				this->m_resources = this->m_resources - HealingTouch::COST;
				skillBought = true;
			}

			break;

		case Skill::DEMONIC_PRESENCE:
			if(this->m_resources >= DemonicPresence::COST)
			{
				a = new DemonicPresence();
				this->m_resources = this->m_resources - DemonicPresence::COST;
				skillBought = true;
			}

			break;

		case Skill::TELEPORT:
			if(this->m_resources >= Greed::TELEPORT)
			{
				a = new Teleport();
				this->m_resources = this->m_resources - Teleport::COST;
				skillBought = true;
			}

			break;

		case Skill::WALL:
			skillBought = true;
			break;
		}

		if(skillBought == true)
		{
			this->m_hero->addSkill(a);
			this->m_messageQueue->pushOutgoingMessage(new SkillBoughtMessage(bsm.getActionId(), this->m_id, this->m_resources));
		}
	}
}

void Player::update(float _dt)
{
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
	switch(usm.getActionId())
	{
	case Skill::MOVE:
		this->m_hero->setNextPosition(usm.getPosition());
		break;

	case Skill::DEATH_TOWER:
		EntityHandler::addEntity(new Tower(usm.getPosition()));
		break;

	default:
		Skill *s = this->m_hero->getSkill(usm.getActionId());

		if(s != NULL)
		{
			s->activate(usm.getPosition(), this->m_hero->getId());
		}

		break;
	}
}

void Player::handleUseActionMessage(NetworkUseActionMessage usm)
{
	Skill *s = this->m_hero->getSkill(usm.getActionId());

	if(s != NULL)
	{
		s->activate(this->m_hero->getId());
	}
}

void Player::handleUseActionTargetMessage(NetworkUseActionTargetMessage usm)
{
	switch(usm.getActionId())
	{
	case Skill::ATTACK:
		this->m_hero->setTarget(usm.getTargetId());
		break;

	default:
		Skill *s = this->m_hero->getSkill(usm.getActionId());

		if(s != NULL)
		{
			s->activate(usm.getTargetId(), m_hero->getId());
		}

		break;
	}
}