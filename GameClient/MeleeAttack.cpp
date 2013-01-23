#include "MeleeAttack.h"

MeleeAttack::MeleeAttack(FLOAT3 _position, float _damage, unsigned int _targetId) : ServerEntity()
{
	this->m_position = _position;
	this->m_damage = _damage;
	this->m_targetId = _targetId;
	this->m_visible = false;
	this->m_range = 2.0f;

	this->m_obb = new BoundingOrientedBox(XMFLOAT3(this->m_position.x, this->m_position.y, this->m_position.z), XMFLOAT3(0.7f, 0.7f, 0.7f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
}

MeleeAttack::~MeleeAttack()
{

}

void MeleeAttack::update(float dt)
{
	Message *m;

	ServerEntity *se = EntityHandler::getServerEntity(this->m_targetId);

	if(se != NULL && (se->getPosition() - this->m_position).length() <= this->m_range)
	{
		se->takeDamage(this->m_damage, true);
	}

	this->m_messageQueue->pushOutgoingMessage(new RemoveServerEntityMessage(0, EntityHandler::getId(), this->m_id));
}