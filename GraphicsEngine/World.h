#pragma once

#include "EffectFile.h"
#include "ForwardRenderingEffectFile.h"
#include "Camera.h"
#include "DeviceHandler.h"
#include "Model.h"
#include "VertexStructs.h"
#include "RenderTarget.h"
#include "DepthStencil.h"

class World
{
private:
	Camera *m_camera;
	ForwardRenderingEffectFile* m_forwardRendering;
	RenderTarget *m_forwardRenderTarget;
	DepthStencil *m_forwardDepthStencil;

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