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

	Model* createModel(string _filename);
	bool removeModel(Model* _model);

	void render();
	void update(float dt);
};

#endif
