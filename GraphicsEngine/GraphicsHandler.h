#ifndef GRAPHICS_HANDLER
#define GRAPHICS_HANDLER

#include "stdafx.h"
#include "World.h"
#include "DeviceHandler.h"
#include "ResourceHolder.h"
#include "Model.h"
#include "ConfigFile.h"
#include "Camera.h"
#include "MyText.h"
#include "Animation.h"
#include "DirectionalLight.h"
#include "SpotLight.h"

class GraphicsHandler : public sf::Thread
{
private:
	World *m_world;
	DeviceHandler* m_deviceHandler;
	ResourceHolder *m_resourceHolder;
	INT2 m_configScreenSize;
	INT2 m_realScreenSize;
	bool m_windowed;
	Text* m_fpsText;

	bool m_running;
	void Run();
public:
	DECLDIR GraphicsHandler();
	DECLDIR GraphicsHandler(HWND _hWnd, ConfigFile* _configFile);
	DECLDIR ~GraphicsHandler();
	
	DECLDIR Camera *getCamera();
	DECLDIR INT2 getRealScreenSize();
	DECLDIR INT2 getScreenSize();
	
	DECLDIR Road* createRoad(string _texture, FLOAT3 _pos, float _rot);
	DECLDIR bool removeRoad(Road* _road);
	
	DECLDIR Terrain* createTerrain(FLOAT3 _v1, FLOAT3 _v2, vector<string> _textures, vector<string> _blendMaps, vector<string> _normalMaps);
	DECLDIR bool removeTerrain(Terrain* _terrain);
	
	DECLDIR Text* createText(string _text, INT2 _pos, int _size, D3DXCOLOR _color);
	DECLDIR bool removeText(Text *text);
	
	DECLDIR MyText* createMyText(string _texture, string _offsetPath, string _offsetFilename, string _text, INT2 _pos, int _size);
	DECLDIR bool removeMyText(MyText *text);

	DECLDIR Model* createModel(string _filename, FLOAT3 _position);
	DECLDIR bool removeModel(Model* _model);

	DECLDIR Sprite *createSprite(string filename, FLOAT2 position, FLOAT2 size, int layer);
	DECLDIR bool removeSprite(Sprite *sprite);

	DECLDIR SpriteSheet *createSpriteSheet(string filename, FLOAT2 position, FLOAT2 size, INT2 nrOfFrames, int layer);
	DECLDIR bool removeSpriteSheet(SpriteSheet *spriteSheet);

	DECLDIR PointLight *createPointLight(FLOAT3 position, FLOAT3 la, FLOAT3 ld, FLOAT3 ls, float radius);
	DECLDIR bool removePointLight(PointLight *pointLight);

	DECLDIR DirectionalLight *createDirectionalLight(FLOAT3 direction, FLOAT3 la, FLOAT3 ld, FLOAT3 ls);
	DECLDIR bool removeDirectionalLight(DirectionalLight *directionalLight);

	DECLDIR SpotLight *createSpotLight(FLOAT3 position, FLOAT3 la, FLOAT3 ld, FLOAT3 ls, FLOAT2 angle, float range);
	DECLDIR bool removeSpotLight(SpotLight* spotLight);

	DECLDIR void render();
	void stop() { m_running = false; }
	DECLDIR void update(float dt);
	DECLDIR HWND InitWindow(HINSTANCE _hInstance, int _nCmdShow, INT2 _screenSize);
};

#endif
