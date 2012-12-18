#include "Player.h"

Player::Player(unsigned int id)
{
	this->m_id = id;
	//this->m_messageQueue = new MessageQueue();
	this->m_hero = new Hero();

	EntityHandler::addEntity(m_hero);
}

Player::~Player()
{
	//delete this->m_messageQueue;
}

void Player::handleEntityMessage(EntityMessage e)
{
	//MoveMessage *m = new MoveMessage();

	//m->position = e.getPos();
	//m->reciverId = 0;
	//m->type = MessageTypes::MoveEntity;

	//this->m_messageQueue->pushOutgoingMessage(m);

	this->m_hero->setNextPosition(e.getPos());
}

void Player::update()
{

}
//
//MessageQueue *Player::getMessageQueue()
//{
//	return this->m_messageQueue;
//}