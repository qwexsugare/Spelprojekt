#include "Teleport.h"
#include "EntityHandler.h"
#include "Hero.h"
#include "TeleportEffect.h"
#include "Graphics.h"

extern Pathfinder* g_pathfinder;

const float Teleport::COOLDOWN = 30.0f;

Teleport::Teleport() : Skill(Skill::TELEPORT, COOLDOWN)
{
	Model* temp = g_graphicsEngine->createModel("Char", FLOAT3(0.0f, 0.0f, 0.0f));
	m_obbOffset = temp->getObb()->Center;
	m_obb = *temp->getObb();
	g_graphicsEngine->removeModel(temp);
}

Teleport::~Teleport()
{

}

bool Teleport::activate(FLOAT3 _position, unsigned int _senderId)
{
	ServerEntity* caster = EntityHandler::getServerEntity(_senderId);
	
	if(this->getCurrentCooldown() == 0 && (caster->getPosition() - _position).length() <= RANGE)
	{
		m_obb.Center = XMFLOAT3(_position.x+m_obbOffset.x, _position.y+m_obbOffset.y, _position.z+m_obbOffset.z);
		if(!EntityHandler::intersects(m_obb))
		{
			if(g_pathfinder->isValidPos(FLOAT2(_position.x, _position.z)))
			{
				((Hero*)caster)->setPosition(_position);
				((Hero*)caster)->setNextPosition(((Hero*)caster)->getPosition());
				((Hero*)caster)->getMessageQueue()->pushOutgoingMessage(((Hero*)caster)->getUpdateEntityMessage());
				this->resetCooldown();
				EntityHandler::addEntity(new TeleportEffect(_senderId));
			}

			return true;
		}
		else
			return false;
	}
	else
		return false;
}

void Teleport::updateSpecificSkill(float _dt)
{

}

int Teleport::getCost()
{
	return Teleport::COST;
}