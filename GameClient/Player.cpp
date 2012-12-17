#include "Player.h"

Player::Player(unsigned int id)
{
	this->m_id = id;
	this->m_messageQueue = new MessageQueue();
}

Player::~Player()
{
	delete this->m_messageQueue;
}

void Player::handleEntityMessage(EntityMessage e)
{
	MoveMessage *m = new MoveMessage();

	m->position = e.getPos();
	m->reciverId = 0;
	m->type = 1;

	this->m_messageQueue->pushOutgoingMessage(m);
}

void Player::update()
{

}

MessageQueue *Player::getMessageQueue()
{
	return this->m_messageQueue;
}