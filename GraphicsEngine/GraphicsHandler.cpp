#include "GraphicsHandler.h"

GraphicsHandler::GraphicsHandler()
{

}

GraphicsHandler::GraphicsHandler(HWND _hWnd, ConfigFile* _configFile)
{
	this->m_deviceHandler = new DeviceHandler(_hWnd, _configFile->getWindowed(), _configFile->getScreenSize());
	this->m_world = new World(this->m_deviceHandler);
	this->m_resourceHolder = new ResourceHolder(this->m_deviceHandler->getDevice());

	this->m_world->addSprite(new Sprite(this->m_deviceHandler->getDevice(), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(1.0f, 1.0f), this->m_resourceHolder->getTextureHolder()->getTexture("Ship4Texture.dds")));
}

GraphicsHandler::~GraphicsHandler()
{
	delete this->m_world;
	delete this->m_resourceHolder;
	delete this->m_deviceHandler;
}

Text* GraphicsHandler::createText(string _text, INT2 _pos, int _size, D3DXCOLOR _color)
{
	Text* text = new Text(this->m_deviceHandler->createFont(_size), _text, _pos, _color);

	this->m_world->addText(text);

	return text;
}

Camera *GraphicsHandler::getCamera()
{
	return this->m_world->getCamera();
}

Model* GraphicsHandler::createModel(string _filename)
{
	Model* model = NULL;
	Mesh* mesh = this->m_resourceHolder->getMesh(_filename);

	if(mesh != NULL)
	{
		model = new Model(mesh, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		this->m_world->addModel(model);
	}

	return model;
}

bool GraphicsHandler::removeModel(Model* _model)
{
	return this->m_world->removeModel(_model);
}

Sprite *GraphicsHandler::createSprite(string filename)
{
	Sprite *sprite = NULL;
	//sprite = new Sprite(

	return sprite;
}

bool GraphicsHandler::remove(Sprite *sprite)
{
	return this->m_world->removeSprite(sprite);
}

void GraphicsHandler::render()
{
	this->m_world->render();
}

void GraphicsHandler::update(float dt)
{
	//Uppdatera animationer?
}