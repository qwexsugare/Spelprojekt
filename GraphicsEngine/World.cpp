#include "World.h"

World::World()
{

}

World::World(DeviceHandler* _deviceHandler)
{
	this->m_deviceHandler = _deviceHandler;
	this->m_models = vector<Model*>();
}

World::~World()
{

}

void World::render()
{

}

void World::addModel(Model *_model)
{
	this->m_models.push_back(_model);
}

bool World::removeModel(Model *_model)
{
	// we do not know HOW to write this code
	return true;
}