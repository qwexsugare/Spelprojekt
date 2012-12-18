#include "GraphicsHandler.h"

GraphicsHandler::GraphicsHandler()
{

}

GraphicsHandler::GraphicsHandler(HWND _hWnd, ConfigFile* _configFile)
{
	this->m_deviceHandler = new DeviceHandler(_hWnd, _configFile->getWindowed(), _configFile->getScreenSize());
	RECT rc;
	GetWindowRect(_hWnd, &rc);
	this->m_realScreenSize = INT2(rc.right-rc.left, rc.bottom-rc.top);
	this->m_world = new World(this->m_deviceHandler);
	this->m_resourceHolder = new ResourceHolder(this->m_deviceHandler->getDevice());
}

GraphicsHandler::~GraphicsHandler()
{
	delete this->m_world;
	delete this->m_resourceHolder;
	delete this->m_deviceHandler;
}
	
Terrain* GraphicsHandler::createTerrain(FLOAT3 _v1, FLOAT3 _v2, vector<string> _textures, vector<string> _blendMaps)
{
	// Pre-define a shitload of vars
	D3DXVECTOR3 v1(_v1.x, _v1.y, _v1.z);
	D3DXVECTOR3 v2(_v2.x, _v2.y, _v2.z);
	vector<ID3D10ShaderResourceView*> textures;
	for(int i = 0; i < _textures.size(); i++)
		textures.push_back(this->m_resourceHolder->getTextureHolder()->getTexture(_textures[i]));
	vector<ID3D10ShaderResourceView*> blendMaps;
	for(int i = 0; i < _blendMaps.size(); i++)
		blendMaps.push_back(this->m_resourceHolder->getTextureHolder()->getTexture(_blendMaps[i]));

	// Shove that heap of trash vars into the terrains crappy constructor.
	Terrain* terrain = new Terrain(this->m_deviceHandler->getDevice(), v1, v2, 8, 8, textures, blendMaps);
	
	this->m_world->addTerrain(terrain);

	return terrain;
}

bool GraphicsHandler::removeTerrain(Terrain* _terrain)
{
	return this->m_world->removeTerrain(_terrain);
}

Text* GraphicsHandler::createText(string _text, INT2 _pos, int _size, D3DXCOLOR _color)
{
	Text* text = new Text(this->m_deviceHandler->createFont(_size), _text, _pos, _color);

	this->m_world->addText(text);

	return text;
}
	

bool GraphicsHandler::removeText(Text* _text)
{
	return this->m_world->removeText(_text);
}

Camera *GraphicsHandler::getCamera()
{
	return this->m_world->getCamera();
}

INT2 GraphicsHandler::getScreenSize()
{
	return this->m_realScreenSize;
}

Model* GraphicsHandler::createModel(string _filename, FLOAT3 _position)
{
	Model* model = NULL;
	Mesh* mesh = this->m_resourceHolder->getMesh(_filename);

	if(mesh != NULL)
	{
		model = new Model(this->m_deviceHandler->getDevice(), mesh, D3DXVECTOR3(_position.x, _position.y, _position.z));

		// If the world failed to add the model, delete the model;
		if(!this->m_world->addModel(model))
		{
			delete model;
			model = NULL;
		}
	}

	return model;
}

bool GraphicsHandler::removeModel(Model* _model)
{
	return this->m_world->removeModel(_model);
}

Sprite *GraphicsHandler::createSprite(string filename, INT2 position, INT2 size, int layer)
{
	Sprite *sprite = new Sprite(this->m_deviceHandler, FLOAT2(position.x, position.y), FLOAT2(size.x, size.y), this->m_resourceHolder->getTextureHolder()->getTexture(filename), layer);
	this->m_world->addSprite(sprite);

	return sprite;
}

bool GraphicsHandler::removeSprite(Sprite *sprite)
{
	return this->m_world->removeSprite(sprite);
}

SpriteSheet *GraphicsHandler::createSpriteSheet(string filename, INT2 position, INT2 size, INT2 nrOfFrames, int layer)
{
	SpriteSheet *s = new SpriteSheet(this->m_deviceHandler, this->m_resourceHolder->getTextureHolder()->getTexture(filename), position, size, nrOfFrames, layer);
	this->m_world->addSprite(s);
	return s;
}

bool GraphicsHandler::removeSpriteSheet(SpriteSheet *spriteSheet)
{
	return this->m_world->removeSprite(spriteSheet);
}

void GraphicsHandler::render()
{
	this->m_world->render();
}

void GraphicsHandler::update(float dt)
{
	this->m_world->update(dt);
}