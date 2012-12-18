#include "Player.h"

Player::Player(unsigned int id)
{
	this->m_id = id;
	this->m_messageQueue = new MessageQueue();
	this->m_hero = new Hero();

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
		StartMessage *m;
		m->type = Message::Type::Start;
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