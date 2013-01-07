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

class GraphicsHandler
{
private:
	World *m_world;
	DeviceHandler* m_deviceHandler;
	ResourceHolder *m_resourceHolder;
	INT2 m_configScreenSize;
	INT2 m_realScreenSize;
	bool m_windowed;
public:
	DECLDIR GraphicsHandler();
	DECLDIR GraphicsHandler(HWND _hWnd, ConfigFile* _configFile);
	DECLDIR ~GraphicsHandler();
	
	DECLDIR Camera *getCamera();
	DECLDIR INT2 getScreenSize();
	
	DECLDIR Terrain* createTerrain(FLOAT3 _v1, FLOAT3 _v2, vector<string> _textures, vector<string> _blendMaps);
	DECLDIR bool removeTerrain(Terrain* _terrain);
	
	DECLDIR Text* createText(string _text, INT2 _pos, int _size, D3DXCOLOR _color);
	DECLDIR bool removeText(Text *text);
	
	DECLDIR MyText* createMyText(string _texture, string _text, INT2 _pos, int _size, D3DXCOLOR _color);
	DECLDIR bool removeMyText(MyText *text);

	DECLDIR Model* createModel(string _filename, FLOAT3 _position);
	DECLDIR bool removeModel(Model* _model);

	DECLDIR Sprite *createSprite(string filename, FLOAT2 position, FLOAT2 size, int layer);
	DECLDIR bool removeSprite(Sprite *sprite);

	DECLDIR SpriteSheet *createSpriteSheet(string filename, FLOAT2 position, FLOAT2 size, INT2 nrOfFrames, int layer);
	DECLDIR bool removeSpriteSheet(SpriteSheet *spriteSheet);

	DECLDIR void render();
	DECLDIR void update(float dt);
	DECLDIR HWND InitWindow(HINSTANCE _hInstance, int _nCmdShow, INT2 _screenSize);
};

#endif
