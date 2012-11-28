#ifndef GRAPHICS_HANDLER
#define GRAPHICS_HANDLER

#include "stdafx.h"
#include "World.h"
#include "DeviceHandler.h"
#include "ResourceHolder.h"
#include "Model.h"
#include "ConfigFile.h"
#include "Camera.h"

class DECLDIR GraphicsHandler
{
private:
	World *m_world;
	DeviceHandler* m_deviceHandler;
	ResourceHolder *m_resourceHolder;
public:
	GraphicsHandler();
	GraphicsHandler(HWND _hWnd, ConfigFile* _configFile);
	~GraphicsHandler();

	Camera *getCamera();
	
	Text* createText(string _text, INT2 _pos, int _size, D3DXCOLOR _color);
	Model* createModel(string _filename);
	bool removeModel(Model* _model);

	Sprite *createSprite(string filename);
	bool remove(Sprite *sprite);

	void render();
	void update(float dt);
	HWND InitWindow(HINSTANCE _hInstance, int _nCmdShow, INT2 _screenSize);
};

#endif
