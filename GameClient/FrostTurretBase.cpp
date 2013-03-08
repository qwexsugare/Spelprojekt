#include "FrostTurretBase.h"
#include "Graphics.h"
#include "EntityHandler.h"

FrostTurretBase::FrostTurretBase(FLOAT3 _pos, float _lifetime) : ServerEntity(_pos)
{
	Model* temp = g_graphicsEngine->createModel("FrostBase", _pos);
	m_obb = new BoundingOrientedBox(*temp->getObb());
	g_graphicsEngine->removeModel(temp);
	m_lifeTime = _lifetime;
	m_modelId = 6;
	m_visible = true;
	m_type = ServerEntity::TowerType;
}

FrostTurretBase::~FrostTurretBase()
{

}

void FrostTurretBase::update(float _dt)
{
	m_lifeTime = max(m_lifeTime - _dt, 0.0f);
	if(this->m_lifeTime == 0.0f)
	{
		this->m_messageQueue->pushOutgoingMessage(new RemoveServerEntityMessage(0, EntityHandler::getId(), this->m_id));
	}
}