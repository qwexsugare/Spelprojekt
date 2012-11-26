#ifndef GRAPHICS_HANDLER
#define GRAPHICS_HANDLER

#include "stdafx.h"
#include "World.h"
#include "DeviceHandler.h"
#include "ResourceHolder.h"
#include "Model.h"
#include "ConfigFile.h"

class DECLDIR GraphicsHandler
{
private:
	World *m_world;
	DeviceHandler* m_deviceHandler;
	ResourceHolder *m_resourceHolder;
	ConfigFile m_configFile;
public:
	GraphicsHandler();
	GraphicsHandler(HWND _hWnd, const ConfigFile& _configFile);
	~GraphicsHandler();

	Model* createModel(string _filename);
	bool removeModel(Model* _model);

	void render();
	void update(float dt);
};

#endif
