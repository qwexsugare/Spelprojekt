#pragma once

#include "EffectFile.h"
#include "ForwardRenderingEffectFile.h"
#include "DeferredRenderingEffectFile.h"
#include "Camera.h"
#include "DeviceHandler.h"
#include "Model.h"
#include "VertexStructs.h"
#include "RenderTarget.h"
#include "DepthStencil.h"

class World
{
private:
	ID3DX10Font* m_fpsFont;
	Camera *m_camera;

	//Forward rendering
	ForwardRenderingEffectFile* m_forwardRendering;
	RenderTarget *m_forwardRenderTarget;
	DepthStencil *m_forwardDepthStencil;

	//Deferred rendering
	DeferredRenderingEffectFile* m_deferredRendering;
	RenderTarget *m_positionBuffer;
	RenderTarget *m_normalBuffer;
	RenderTarget *m_diffuseBuffer;

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

	Camera *getCamera();
};