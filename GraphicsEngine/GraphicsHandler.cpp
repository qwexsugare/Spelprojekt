#include "GraphicsHandler.h"

GraphicsHandler::GraphicsHandler(HWND _hWnd)
{
	this->m_deviceHandler = new DeviceHandler(_hWnd);
	this->m_world = World(this->m_deviceHandler);
	this->m_resourceHolder = ResourceHolder(this->m_deviceHandler->getDevice());
}

GraphicsHandler::~GraphicsHandler()
{
	delete this->m_deviceHandler;
}

Model* GraphicsHandler::createModel(string _filename)
{
	Model* model;

	model = new Model(this->m_resourceHolder.getMesh(_filename));
	int 
	return model;
}

bool GraphicsHandler::removeModel(Model* _model)
{

}

void GraphicsHandler::render()
{
	this->m_world.render();
}

void update(float dt)
{
	//Uppdatera animationer?
}