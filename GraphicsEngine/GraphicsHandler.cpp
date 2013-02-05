#include "GraphicsHandler.h"
#include <sstream>

GraphicsHandler::GraphicsHandler()
{

}

GraphicsHandler::GraphicsHandler(HWND _hWnd, ConfigFile* _configFile)
{
	this->m_deviceHandler = new DeviceHandler(_hWnd, _configFile->getWindowed(), _configFile->getScreenSize());
	this->m_world = new World(this->m_deviceHandler, _hWnd, _configFile->getWindowed());
	this->m_resourceHolder = new ResourceHolder(this->m_deviceHandler->getDevice());
	this->m_windowed = _configFile->getWindowed();
	
	this->m_configScreenSize = _configFile->getScreenSize();

	// If we run in windowed, set the real screen size to be config screen size or the bars and crap outside of the window are counted in
	if(_configFile->getWindowed())
	{
		this->m_realScreenSize = _configFile->getScreenSize();
	}
	// Else get the real screen size
	else
	{
		RECT rc;
		GetWindowRect(_hWnd, &rc);
		this->m_realScreenSize = INT2(rc.right-rc.left, rc.bottom-rc.top);
	}
	
	this->m_fpsText = this->createText("", INT2(300, 300), 40, D3DXCOLOR(1.0f, 0.2f, 0.2f, 1.0f));
}

GraphicsHandler::~GraphicsHandler()
{
	delete this->m_world;
	delete this->m_resourceHolder;
	delete this->m_deviceHandler;
}

Road* GraphicsHandler::createRoad(string _texture, FLOAT3 _pos, float _rot)
{
	Road* road = new Road(m_deviceHandler->getDevice(), m_resourceHolder->getTextureHolder()->getTexture("textures/"+_texture), D3DXVECTOR3(_pos.x, _pos.y, _pos.z), _rot);
	m_world->addRoad(road);
	return road;
}

bool GraphicsHandler::removeRoad(Road* _road)
{
	return this->m_world->removeRoad(_road);
}
	
Terrain* GraphicsHandler::createTerrain(FLOAT3 _v1, FLOAT3 _v2, vector<string> _textures, vector<string> _blendMaps, vector<string> _normalMaps)
{
	// Pre-define a shitload of vars
	D3DXVECTOR3 v1(_v1.x, _v1.y, _v1.z);
	D3DXVECTOR3 v2(_v2.x, _v2.y, _v2.z);
	ID3D10ShaderResourceView** textures = new ID3D10ShaderResourceView*[8];
	for(int i = 0; i < _textures.size(); i++)
		textures[i] = this->m_resourceHolder->getTextureHolder()->getTexture(_textures[i]);
	ID3D10ShaderResourceView** blendMaps = new ID3D10ShaderResourceView*[2];
	for(int i = 0; i < _blendMaps.size(); i++)
		blendMaps[i] = this->m_resourceHolder->getTextureHolder()->getTexture(_blendMaps[i]);

	// Shove that heap of trash vars into the terrains crappy constructor.
	Terrain* terrain = new Terrain(this->m_deviceHandler->getDevice(), v1, v2, v2.x / 8, v2.z / 8, textures, _textures.size(), blendMaps, _blendMaps.size(), this->m_resourceHolder->getTextureHolder()->getTexture(_normalMaps[0]));
	
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

MyText* GraphicsHandler::createMyText(string _texture, string _offsetPath, string _offsetFilename, string _text, INT2 _pos, int _size)
{
	MyText* text = new MyText(this->m_deviceHandler->getDevice(), this->m_resourceHolder->getTextureHolder()->getTexture("text/" + _texture),
		_offsetPath, _offsetFilename, this->m_configScreenSize.y, this->m_configScreenSize.x, D3DXVECTOR3(_pos.x, _pos.y, 0.0f), _size);
	text->DrawString(_text);
	this->m_world->addMyText(text);

	return text;
}
	
bool GraphicsHandler::removeMyText(MyText* _text)
{
	return this->m_world->removeMyText(_text);
}

Camera *GraphicsHandler::getCamera()
{
	return this->m_world->getCamera();
}

INT2 GraphicsHandler::getRealScreenSize()
{
	return this->m_realScreenSize;
}

INT2 GraphicsHandler::getScreenSize()
{
	if(this->m_windowed)
		return this->m_configScreenSize;
	else
		return this->m_realScreenSize;
}

Model* GraphicsHandler::createModel(string _filename, FLOAT3 _position)
{
	Model* model = NULL;
	Mesh* mesh = this->m_resourceHolder->getMesh(_filename);
	if(mesh != NULL)
	{
		Animation animation;
		animation = this->m_resourceHolder->getAnimation(_filename);
		animation.setTexturePack(&this->m_resourceHolder->getTextureHolder()->getBoneTexture(_filename));
		model = new Model(this->m_deviceHandler->getDevice(), mesh, animation, D3DXVECTOR3(_position.x,  _position.y, _position.z), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
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

Sprite *GraphicsHandler::createSprite(string filename, FLOAT2 position, FLOAT2 size, int layer)
{
	Sprite *sprite = new Sprite(this->m_deviceHandler, position, size, this->m_resourceHolder->getTextureHolder()->getTexture(filename), layer);
	this->m_world->addSprite(sprite);

	return sprite;
}

bool GraphicsHandler::removeSprite(Sprite *sprite)
{
	return this->m_world->removeSprite(sprite);
}

SpriteSheet *GraphicsHandler::createSpriteSheet(string filename, FLOAT2 position, FLOAT2 size, INT2 nrOfFrames, int layer)
{
	SpriteSheet *s = new SpriteSheet(this->m_deviceHandler, this->m_resourceHolder->getTextureHolder()->getTexture(filename), position, size, nrOfFrames, layer);
	this->m_world->addSprite(s);
	return s;
}

bool GraphicsHandler::removeSpriteSheet(SpriteSheet *spriteSheet)
{
	return this->m_world->removeSprite(spriteSheet);
}

PointLight *GraphicsHandler::createPointLight(FLOAT3 position, FLOAT3 la, FLOAT3 ld, FLOAT3 ls, float radius)
{
	PointLight *l = new PointLight(position, la, ld, ls, radius);
	this->m_world->addPointLight(l);
	return l;
}

bool GraphicsHandler::removePointLight(PointLight *pointLight)
{
	return this->m_world->removePointLight(pointLight);
}

DirectionalLight *GraphicsHandler::createDirectionalLight(FLOAT3 direction, FLOAT3 la, FLOAT3 ld, FLOAT3 ls)
{
	DirectionalLight *l = new DirectionalLight(direction, la, ld, ls);
	this->m_world->addDirectionalLight(l);
	return l;
}

bool GraphicsHandler::removeDirectionalLight(DirectionalLight *directionalLight)
{
	return this->m_world->removeDirectionalLight(directionalLight);
}

SpotLight *GraphicsHandler::createSpotLight(FLOAT3 position, FLOAT3 _direction, FLOAT3 la, FLOAT3 ld, FLOAT3 ls, FLOAT2 angle, float range)
{
	SpotLight *l = new SpotLight(m_deviceHandler->getDevice(), position, _direction, la, ld, ls, angle, range);
	this->m_world->addSpotLight(l);
	return l;
}

bool GraphicsHandler::removeSpotLight(SpotLight* spotLight)
{
	return this->m_world->removeSpotLight(spotLight);
}

void GraphicsHandler::render()
{
	this->m_world->render();
}

void GraphicsHandler::update(float dt)
{
	this->m_world->update(dt);
}

void GraphicsHandler::Run()
{
	m_running = true;

	__int64 cntsPerSec = 0;
	QueryPerformanceFrequency((LARGE_INTEGER*)&cntsPerSec);
	float secsPerCnt = 1.0f / (float)cntsPerSec;

	__int64 prevTimeStamp = 0;
	QueryPerformanceCounter((LARGE_INTEGER*)&prevTimeStamp);

	while(m_running)
	{
		__int64 currTimeStamp = 0;
		QueryPerformanceCounter((LARGE_INTEGER*)&currTimeStamp);
		float dt = (currTimeStamp - prevTimeStamp) * secsPerCnt;
		
		static float lol = 0.0f;
		lol += dt;
		if(lol > 1.0f)
		{
			stringstream ss;
			ss << "GPU Fps: " << 1.0f/dt;
			this->m_fpsText->setString(ss.str());
			lol = -0.5f;
		}

		this->update(dt);
		this->render();

		prevTimeStamp = currTimeStamp;
	}
}