#include "Wall.h"

const float Wall::COOLDOWN = 90.0f;

Wall::Wall() : Skill(Skill::WALL, Wall::COOLDOWN)
{

}

Wall::~Wall()
{

}

bool Wall::activate(FLOAT3 _position, unsigned int _senderId)
{
	ServerEntity *sender = EntityHandler::getServerEntity(_senderId);
	if(this->getCurrentCooldown() == 0 && sender != NULL)
	{
		FLOAT3 distance = _position - sender->getPosition();
		float rotation = atan2(-distance.x, -distance.z);
		EntityHandler::addEntity(new WallEffect(_senderId, _position, rotation, ((UnitEntity*)sender)->getFortitude() * 30));

		this->resetCooldown();
		return true;
	}
	else
	{
		return false;
	}
}

void Wall::updateSpecificSkill(float _dt)
{

}

int Wall::getCost()
{
	return Wall::COST;
}