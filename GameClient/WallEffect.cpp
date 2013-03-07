#include "WallEffect.h"

WallEffect::WallEffect(unsigned int _senderId, FLOAT3 _position, float rotation, float _duration) : ServerEntity(_position)
{
	this->m_rotation = FLOAT3(0.0f, rotation, 0.0f);
	this->m_duration = _duration;
	this->m_modelId = 9;
	this->m_type = ServerEntity::StaticType;

	Model *temp = g_graphicsEngine->createModel("wall", _position);
	temp->rotate(rotation, 0.0f, 0.0f);
	this->m_obb = new BoundingOrientedBox(*temp->getObb());
	g_graphicsEngine->removeModel(temp);

	this->m_messageQueue->pushOutgoingMessage(new CreateActionPositionMessage(Skill::WALL, _senderId, _position));
}

WallEffect::~WallEffect()
{

}

void WallEffect::update(float dt)
{
	this->m_duration = this->m_duration - dt;

	if(this->m_duration <= 0.0f)
	{
		this->m_messageQueue->pushOutgoingMessage(new RemoveServerEntityMessage(0, EntityHandler::getId(), this->m_id));
		this->m_messageQueue->pushOutgoingMessage(new RemoveActionTargetMessage(Skill::WALL, 0,0, m_position));
	}
}