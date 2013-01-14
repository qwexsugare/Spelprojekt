#include "Player.h"

Player::Player(unsigned int id)
{
	this->m_id = id;
	this->m_messageQueue = new MessageQueue();
	this->m_hero = new Hero();
	this->m_hero->setPosition(FLOAT3(50.0f, 0.0f, 50.0f));
	this->m_hero->setNextPosition(FLOAT3(50.0f, 0.0f, 50.0f));

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
		EntityHandler::addEntity(new Projectile(this->m_hero->getPosition(), direction, 2, 10.0f));
	}
}

void Player::handleEntityAttackMessage(AttackEntityMessage eam)
{
	ServerEntity *se = EntityHandler::getServerEntity(eam.getTargetId());

	if(se != NULL && se->getType() == ServerEntity::EnemyType)
	{
		FLOAT3 direction = se->getPosition() - this->m_hero->getPosition();
		EntityHandler::addEntity(new Projectile(this->m_hero->getPosition(), direction, 2, 10.0f));
	}
}

void Player::update()
{

}
//
//MessageQueue *Player::getMessageQueue()
//{
//	return this->m_messageQueue;
//}

bool Player::getReady()
{
	return this->m_ready;
}

MessageQueue *Player::getMessageQueue()
{
	return this->m_messageQueue;
}