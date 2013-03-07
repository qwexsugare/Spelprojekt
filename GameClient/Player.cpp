#include "Player.h"
#include "Heroes.h"
#include "TowerPlacer.h"

Player::Player(unsigned int id)
{
	this->m_id = id;
	this->m_resources = 50000;
	this->m_messageQueue = new MessageQueue();
	m_hero = NULL;
	this->m_ready = false;
	m_selectedHeroType = Hero::NONE;
	this->m_attributesBought = 0;
	this->m_nrOfDeaths = 0;
	this->m_respawnTimer = 0.0f;
}

Player::~Player()
{
	delete this->m_messageQueue;
}

void Player::assignHero(Hero::HERO_TYPE _type, Hero::WEAPON_TYPE _weaponType)
{
	m_selectedHeroType = _type;
	m_selectedWeaponType = _weaponType;
}

void Player::spawnHero(FLOAT3 _position)
{
	switch(m_selectedHeroType)
	{
	case Hero::ENGINEER:
		this->m_hero = new Engineer(this->m_messageQueue->getId(), m_selectedWeaponType);
		break;
	case Hero::DOCTOR:
		this->m_hero = new Doctor(this->m_messageQueue->getId(), m_selectedWeaponType);
		break;
	case Hero::RED_KNIGHT:
		this->m_hero = new RedKnight(this->m_messageQueue->getId(), m_selectedWeaponType);
		break;
	case Hero::THE_MENTALIST:
		this->m_hero = new TheMentalist(this->m_messageQueue->getId(), m_selectedWeaponType);
		break;
	case Hero::OFFICER:
		this->m_hero = new Officer(this->m_messageQueue->getId(), m_selectedWeaponType);
		break;
	}
	
	this->m_heroSpawnLocation = _position;
	this->m_hero->setPosition(_position);

	vector<Skill*> skills = this->m_hero->getSkills();

	for(int i = 0; i < skills.size(); i++)
	{
		this->m_messageQueue->pushOutgoingMessage(new SkillBoughtMessage(skills[i]->getId(), this->m_id, this->m_resources));
	}

	EntityHandler::addEntity(m_hero);

	this->m_messageQueue->pushOutgoingMessage(new CreateActionMessage(Skill::IDLE, this->m_hero->getId(), this->m_hero->getPosition()));

	m_hero->activateAllPassiveSkills();
}

Hero::HERO_TYPE Player::getSelectedHeroType()const
{
	return m_selectedHeroType;
}

Hero* Player::getHero()
{
	return this->m_hero;
}

int Player::getId()const
{
	return this->m_id;
}

void Player::handleBuySkillMessage(NetworkBuySkillMessage bsm)
{
	if(this->m_hero->getNrOfSkills() < 6 || bsm.getActionId() == Skill::STRENGTH || bsm.getActionId() == Skill::AGILITY || bsm.getActionId() == Skill::WITS || bsm.getActionId() == Skill::FORTITUDE || bsm.getActionId() == Skill::TURRET_CONSTRUCTION)
	{
		bool skillBought = false;
		Skill* a = NULL;
		int attributeCost = 100 * (pow(1.5f, this->m_attributesBought));

		switch(bsm.getActionId())
		{
		case Skill::STRENGTH:
			if(this->m_resources >= attributeCost && this->m_hero->getStrength() < Hero::MAX_STRENGTH)
			{
				this->m_hero->increaseStrength(1);
				this->m_attributesBought++;
				this->m_resources = this->m_resources - attributeCost;
				this->m_messageQueue->pushOutgoingMessage(new SkillBoughtMessage(Skill::STRENGTH, this->m_id, this->m_resources));
			}
			break;

		case Skill::AGILITY:
			if(this->m_resources >= attributeCost && this->m_hero->getAgility() < Hero::MAX_AGILITY)
			{
				this->m_hero->increaseAgility(1);
				this->m_attributesBought++;
				this->m_resources = this->m_resources - attributeCost;
				this->m_messageQueue->pushOutgoingMessage(new SkillBoughtMessage(Skill::AGILITY, this->m_id, this->m_resources));
			}
			break;

		case Skill::WITS:
			if(this->m_resources >= attributeCost && this->m_hero->getWits() < Hero::MAX_WITS)
			{
				this->m_hero->increaseWits(1);
				this->m_attributesBought++;
				this->m_resources = this->m_resources - attributeCost;
				this->m_messageQueue->pushOutgoingMessage(new SkillBoughtMessage(Skill::WITS, this->m_id, this->m_resources));
			}
			break;

		case Skill::FORTITUDE:
			if(this->m_resources >= attributeCost && this->m_hero->getFortitude() < Hero::MAX_FORTITUDE)
			{
				this->m_hero->increaseFortitude(1);
				this->m_attributesBought++;
				this->m_resources = this->m_resources - attributeCost;
				this->m_messageQueue->pushOutgoingMessage(new SkillBoughtMessage(Skill::FORTITUDE, this->m_id, this->m_resources));
			}	
			break;

		case Skill::TURRET_CONSTRUCTION:
			if(this->m_resources >= attributeCost && this->m_hero->getTurretConstruction() < Hero::MAX_TURRET_CONSTRUCTION)
			{
				this->m_hero->increaseTurretConstruction(1);
				this->m_attributesBought++;
				this->m_resources = this->m_resources - attributeCost;
				this->m_messageQueue->pushOutgoingMessage(new SkillBoughtMessage(Skill::TURRET_CONSTRUCTION, this->m_id, this->m_resources));
			}	
			break;

		case Skill::AIM:
			if(this->m_resources >= Aim::COST)
			{
				a = new Aim(this->m_hero->getId());
				this->m_resources = this->m_resources - Aim::COST;
				skillBought = true;
			}

			break;

		case Skill::DEADLY_STRIKE:
			if(this->m_resources >= DeadlyStrike::COST)
			{
				a = new DeadlyStrike();
				this->m_resources = this->m_resources - DeadlyStrike::COST;
				skillBought = true;
			}

			break;

		case Skill::TURRET_LIFE:
			if(this->m_resources >= TurretLifetime::COST)
			{
				a = new TurretLifetime();
				a->activate(this->m_hero->getId());
				this->m_resources = this->m_resources - TurretLifetime::COST;
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
				this->m_resources = this->m_resources - LifestealingStrike::COST;
				skillBought = true;
			}

			break;

		case Skill::PHYSICAL_RESISTANCE:
			if(this->m_resources >= Greed::COST)
			{
				a = new PhysicalResistance(this->m_hero->getId());
				this->m_resources = this->m_resources - PhysicalResistance::COST;
				skillBought = true;
			}

			break;

		case Skill::MENTAL_RESISTANCE:
			if(this->m_resources >= MentalResistance::COST)
			{
				a = new MentalResistance(this->m_hero->getId());
				this->m_resources = this->m_resources - MentalResistance::COST;
				skillBought = true;
			}

			break;

		case Skill::POISON_STRIKE:
			if(this->m_resources >= PoisonStrike::COST)
			{
				a = new PoisonStrike();
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
			if(this->m_resources >= Teleport::COST)
			{
				a = new Teleport();
				this->m_resources = this->m_resources - Teleport::COST;
				skillBought = true;
			}

			break;

		case Skill::WALL:
			if(this->m_resources >= Wall::COST)
			{
				a = new Wall();
				this->m_resources = this->m_resources - Wall::COST;
				skillBought = true;
			}

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
	while(this->m_messageQueue->incomingQueueEmpty() == false)
	{
		Message *m = this->m_messageQueue->pullIncomingMessage();

		if(m->type == Message::HeroDied)
		{
			this->m_nrOfDeaths++;
			this->m_respawnTimer = this->m_nrOfDeaths * 5.0f;
		}

		delete m;
	}

	if(this->m_respawnTimer > 0.0f)
	{
		this->m_respawnTimer = this->m_respawnTimer - _dt;

		if(this->m_respawnTimer <= 0.0f)
		{
			this->m_hero->respawn(this->m_heroSpawnLocation);
		}
	}
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
	if(this->m_hero->getAlive() == true)
	{
		TimeIsMoney *timeIsMoney;

		switch(usm.getActionId())
		{
		case Skill::MOVE:
			this->m_hero->setNextPosition(usm.getPosition());
			break;
		
		case Skill::DEATH_PULSE_TURRET:
			if(this->m_resources >= DeathPulseTurret::COST && TowerPlacer::place(Skill::SKILLS(usm.getActionId()), usm.getPosition(), m_hero->getPosition(), this->m_hero))
			{
				timeIsMoney = this->getTimeIsMoney();

				if(timeIsMoney != NULL && timeIsMoney->getActive() == true)
				{
					timeIsMoney->setActive(false);
				}
				else
				{
					this->m_resources = this->m_resources - DeathPulseTurret::COST;
				}

				this->m_messageQueue->pushOutgoingMessage(new SkillBoughtMessage(-1, this->m_id, this->m_resources));
				this->m_messageQueue->pushOutgoingMessage(new CreateActionPositionMessage(Skill::DEATH_PULSE_TURRET, this->m_id, usm.getPosition()));
			}
			break;

		case Skill::FROST_TURRET:
			if(this->m_resources >= FrostTurret::COST && TowerPlacer::place(Skill::SKILLS(usm.getActionId()), usm.getPosition(), m_hero->getPosition(), this->m_hero))
			{
				timeIsMoney = this->getTimeIsMoney();

				if(timeIsMoney != NULL && timeIsMoney->getActive() == true)
				{
					timeIsMoney->setActive(false);
				}
				else
				{
					this->m_resources = this->m_resources - FrostTurret::COST;
				}

				this->m_messageQueue->pushOutgoingMessage(new SkillBoughtMessage(-1, this->m_id, this->m_resources));
				this->m_messageQueue->pushOutgoingMessage(new CreateActionPositionMessage(Skill::FROST_TURRET, this->m_id, usm.getPosition()));
			}
			break;

		case Skill::POISON_TURRET:
			if(this->m_resources >= PoisonTurret::COST && TowerPlacer::place(Skill::SKILLS(usm.getActionId()), usm.getPosition(), m_hero->getPosition(), this->m_hero))
			{
				timeIsMoney = this->getTimeIsMoney();

				if(timeIsMoney != NULL && timeIsMoney->getActive() == true)
				{
					timeIsMoney->setActive(false);
				}
				else
				{
					this->m_resources = this->m_resources - PoisonTurret::COST;
				}

				this->m_messageQueue->pushOutgoingMessage(new SkillBoughtMessage(-1, this->m_id, this->m_resources));
				this->m_messageQueue->pushOutgoingMessage(new CreateActionPositionMessage(Skill::POISON_TURRET, this->m_id, usm.getPosition()));
			}
			break;

		case Skill::TESLA_CHAIN_TURRET:
			if(this->m_resources >= TeslaChainTurret::COST && TowerPlacer::place(Skill::SKILLS(usm.getActionId()), usm.getPosition(), m_hero->getPosition(), this->m_hero))
			{
				timeIsMoney = this->getTimeIsMoney();

				if(timeIsMoney != NULL && timeIsMoney->getActive() == true)
				{
					timeIsMoney->setActive(false);
				}
				else
				{
					this->m_resources = this->m_resources - TeslaChainTurret::COST;
				}

				this->m_messageQueue->pushOutgoingMessage(new SkillBoughtMessage(-1, this->m_id, this->m_resources));
				this->m_messageQueue->pushOutgoingMessage(new CreateActionPositionMessage(Skill::TESLA_CHAIN_TURRET, this->m_id, usm.getPosition()));
			}
			break;

		default:
			if(this->m_hero->getSkills().size() > usm.getIndex() && this->m_hero->getSkills()[usm.getIndex()]->getId() == usm.getActionId())
			{
				Skill *s = this->m_hero->getSkills()[usm.getIndex()];
				if(s->activate(usm.getPosition(), m_hero->getId()) == true)
				{
					this->m_messageQueue->pushOutgoingMessage(new SkillUsedMessage(s->getId(), this->m_id, usm.getIndex(), s->getCooldown()));
				}
			}

			break;
		}
	}
}

void Player::handleUseActionMessage(NetworkUseActionMessage usm)
{
	if(this->m_hero->getAlive() == true)
	{
		if(this->m_hero->getSkills().size() > usm.getIndex() && this->m_hero->getSkills()[usm.getIndex()]->getId() == usm.getActionId())
		{
			Skill *s = this->m_hero->getSkills()[usm.getIndex()];
			if(s->activate(m_hero->getId()) == true)
			{
				this->m_messageQueue->pushOutgoingMessage(new SkillUsedMessage(s->getId(), this->m_id, usm.getIndex(), s->getCooldown()));
			}
		}
	}
}

void Player::handleUseActionTargetMessage(NetworkUseActionTargetMessage usm)
{
	if(this->m_hero->getAlive() == true)
	{
		switch(usm.getActionId())
		{
		case Skill::ATTACK:
			this->m_hero->setTarget(usm.getTargetId());
			break;

		default:
			if(this->m_hero->getSkills().size() > usm.getIndex() && this->m_hero->getSkills()[usm.getIndex()]->getId() == usm.getActionId())
			{
				Skill *s = this->m_hero->getSkills()[usm.getIndex()];
				if(s->activate(usm.getTargetId(), m_hero->getId()) == true)
				{
					this->m_messageQueue->pushOutgoingMessage(new SkillUsedMessage(s->getId(), this->m_id, usm.getIndex(), s->getCooldown()));
				}
			}

			break;
		}
	}
}

void Player::handleReadyMessage(NetworkReadyMessage rm)
{
	this->m_ready = rm.isPorn();
}

void Player::handleSelectHeroMessage(NetworkSelectHeroMessage shm)
{
	this->m_messageQueue->pushOutgoingMessage(new SelectHeroMessage(this->m_id, 0, shm.getHeroId(), shm.getWeapon()));
}

void Player::addResources(unsigned int resources)
{
	this->m_resources += resources * this->m_hero->getGreed();
	this->m_messageQueue->pushOutgoingMessage(new SkillBoughtMessage(999, this->m_id, this->m_resources));
}

TimeIsMoney *Player::getTimeIsMoney()
{
	TimeIsMoney *result = NULL;
	vector<Skill*> skills = this->m_hero->getSkills();

	for(int i = 0; i < skills.size(); i++)
	{
		if(skills[i]->getId() == Skill::TIME_IS_MONEY)
		{
			result = (TimeIsMoney*)skills[i];
			i = skills.size();
		}
	}

	return result;
}