#pragma once

#include "EffectFile.h"
#include "Camera.h"
#include "DeviceHandler.h"
#include "Model.h"

class World
{
private:
	Camera m_camera;
	EffectFile m_forwardRendering;
	EffectFile m_deferredRendering;
	DeviceHandler* m_deviceHandler;

	vector<Model*> m_models;
public:
	World();
	World(DeviceHandler* _deviceHandler);
	~World();

	void render();

	void addModel(Model *_model);
	bool removeModel(Model *_model);
};