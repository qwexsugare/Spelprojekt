#include "Projectile.h"

Projectile::Projectile(FLOAT3 _position, FLOAT3 _direction, float _lifetime, float _movementSpeed) : ServerEntity()
{
	this->m_positon = _position;
	this->m_obb = new BoundingOrientedBox(XMFLOAT3(this->m_positon.x, this->m_positon.y, this->m_positon.z), XMFLOAT3(0.5f, 0.5f, 0.5f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	this->m_direction = _direction / _direction.length();
	this->m_lifetime = _lifetime;
	this->m_movementSpeed = _movementSpeed;
	this->m_type = Type::ProjectileType;
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

			if(se != NULL && se->getType() == Type::EnemyType)
			{
				this->m_lifetime = 0;
				se->takeDamage(10);
			}
		}

		delete m;
	}

	this->m_positon = this->m_positon + this->m_direction * dt * this->m_movementSpeed;
	this->m_obb->Center = XMFLOAT3(this->m_positon.x, this->m_positon.y, this->m_positon.z);
	this->m_lifetime = this->m_lifetime - dt;

	if(this->m_lifetime <= 0)
	{
		this->m_messageQueue->pushOutgoingMessage(new RemoveServerEntityMessage(0, EntityHandler::getId(), this->m_id));
	}
}