#include "Projectile.h"

Projectile::Projectile(FLOAT3 _position, FLOAT3 _direction, float _lifetime, float _movementSpeed) : ServerEntity()
{
	this->m_positon = _position;
	this->m_direction = _direction / _direction.length();
	this->m_lifetime = _lifetime;
	this->m_movementSpeed = _movementSpeed;
}

Projectile::~Projectile()
{

}

void Projectile::update(float dt)
{
	//Handle incoming messages
	Message *m;

	while(this->m_messageQueue->incomingQueueEmpty() == false)
	{
		m = this->m_messageQueue->pullIncomingMessage();

		if(m->type == Message::Collision)
		{
			CollisionMessage *cm = (CollisionMessage*)m;
			ServerEntity *se = EntityHandler::getServerEntity(cm->affectedDudeId);
			this->m_lifetime = 0;
		}

		delete m;
	}

	this->m_positon = this->m_positon + this->m_direction * dt * this->m_movementSpeed;
	this->m_lifetime = this->m_lifetime - dt;

	if(this->m_lifetime <= 0)
	{
		this->m_messageQueue->pushOutgoingMessage(new RemoveServerEntityMessage(0, EntityHandler::getId(), this->m_id));
	}
}