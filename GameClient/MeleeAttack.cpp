#include "MeleeAttack.h"

MeleeAttack::MeleeAttack(FLOAT3 _position, float _damage, unsigned int _targetId) : ServerEntity()
{
	this->m_positon = _position;
	this->m_damage = _damage;
	this->m_targetId = _targetId;
	this->m_visible = false;

	this->m_obb = new BoundingOrientedBox(XMFLOAT3(this->m_positon.x, this->m_positon.y, this->m_positon.z), XMFLOAT3(0.7f, 0.7f, 0.7f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
}

MeleeAttack::~MeleeAttack()
{

}

void MeleeAttack::update(float dt)
{
	Message *m;

	while(this->m_messageQueue->incomingQueueEmpty() == false)
	{
		m = this->m_messageQueue->pullIncomingMessage();

		if(m->type == Message::Collision)
		{
			CollisionMessage *cm = (CollisionMessage*)m;

			if(cm->affectedDudeId == this->m_targetId)
			{
				ServerEntity *se = EntityHandler::getServerEntity(cm->affectedDudeId);

				if(se != NULL)
				{
					se->takeDamage(this->m_damage);
				}
			}
		}

		delete m;
	}

	this->m_messageQueue->pushOutgoingMessage(new RemoveServerEntityMessage(0, EntityHandler::getId(), this->m_id));
}