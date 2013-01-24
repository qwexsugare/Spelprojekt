#include "Projectile.h"

Projectile::Projectile(FLOAT3 _position, FLOAT3 _direction, float _lifetime, float _movementSpeed) : UnitEntity()
{
	this->m_position = _position;
	this->m_obb = new BoundingOrientedBox(XMFLOAT3(this->m_position.x, this->m_position.y, this->m_position.z), XMFLOAT3(0.5f, 0.5f, 0.5f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
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
				this->dealDamage(se, 10, true);
			}
		}

		delete m;
	}

	this->m_position = this->m_position + this->m_direction * dt * this->m_movementSpeed;
	this->m_obb->Center = XMFLOAT3(this->m_position.x, this->m_position.y, this->m_position.z);
	this->m_lifetime = this->m_lifetime - dt;

	if(this->m_lifetime <= 0)
	{
		this->m_messageQueue->pushOutgoingMessage(new RemoveServerEntityMessage(0, EntityHandler::getId(), this->m_id));
	}
}