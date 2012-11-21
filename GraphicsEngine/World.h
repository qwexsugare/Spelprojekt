#pragma once

#include "EffectFile.h"
#include "ForwardRenderingEffectFile.h"
#include "Camera.h"
#include "DeviceHandler.h"
#include "Model.h"
#include "VertexStructs.h"

class World
{
private:
	Camera *m_camera;
	ForwardRenderingEffectFile* m_forwardRendering;
	EffectFile m_deferredRendering;
	ID3D10InputLayout *m_vertexLayout;
	DeviceHandler* m_deviceHandler;

	vector<Model*> m_models;
public:
	World();
	World(DeviceHandler* _deviceHandler);
	~World();

	void render();

	void addModel(Model *_model);
	bool removeModel(Model *_model);

	Camera *getCamera();
};