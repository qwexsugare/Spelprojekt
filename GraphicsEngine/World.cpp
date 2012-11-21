#include "World.h"

World::World()
{

}

World::World(DeviceHandler* _deviceHandler)
{
	this->m_deviceHandler = _deviceHandler;
	this->m_models = vector<Model*>();
	this->m_camera = new Camera(this->m_deviceHandler->getScreenSize().x, this->m_deviceHandler->getScreenSize().y);
}

World::~World()
{
	delete this->m_camera;
}

void World::render()
{
	//Init render stuff
	this->m_camera->updateViewMatrix();

	//Render all models


	//Finish render
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

Camera *World::getCamera()
{
	return this->m_camera;
}