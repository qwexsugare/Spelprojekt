#include "GraphicsHandler.h"

GraphicsHandler::GraphicsHandler()
{

}

GraphicsHandler::GraphicsHandler(HWND _hWnd, ConfigFile* _configFile)
{
	this->m_deviceHandler = new DeviceHandler(_hWnd, _configFile->getWindowed(), _configFile->getScreenSize());
	this->m_world = new World(this->m_deviceHandler);
	this->m_resourceHolder = new ResourceHolder(this->m_deviceHandler->getDevice());

	SpriteSheet *s = new SpriteSheet(this->m_deviceHandler, this->m_resourceHolder->getTextureHolder()->getTexture("test.png"), INT2(500, 500), INT2(100, 100), INT2(4, 2));
	this->m_world->addSpriteSheet(s);
	s->playAnimation(INT2(0,0), INT2(3,1), true, 2);
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

Sprite *GraphicsHandler::createSprite(string filename, FLOAT2 position, FLOAT2 size)
{
	Sprite *sprite = new Sprite(this->m_deviceHandler, position, size, this->m_resourceHolder->getTextureHolder()->getTexture(filename));
	this->m_world->addSprite(sprite);

	return sprite;
}

bool GraphicsHandler::removeSprite(Sprite *sprite)
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
	this->m_world->update(dt);
}