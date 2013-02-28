#pragma once

#include "EffectFile.h"
#include "ForwardRenderingEffectFile.h"
#include "DeferredRenderingEffectFile.h"
#include "DeferredSamplerEffectFile.h"
#include "GlowRenderingEffectFile.h"
#include "SSAOEffectFile.h"
#include "SpriteEffectFile.h"
#include "Camera.h"
#include "DeviceHandler.h"
#include "Model.h"
#include "VertexStructs.h"
#include "RenderTarget.h"
#include "DepthStencil.h"
#include "Sprite.h"
#include "FullScreenPlane.h"
#include "Text.h"
#include "MyText.h"
#include "QuadTree.h"
#include "SpriteSheet.h"
#include "SpriteBase.h"
#include "Terrain.h"
#include "PointLight.h"
#include "DirectionalLight.h"
#include "SpotLight.h"
#include "Road.h"

class World
{
private:
	Camera *m_camera;

	//Forward rendering
	ForwardRenderingEffectFile* m_forwardRendering;
	RenderTarget *m_forwardRenderTarget;
	DepthStencil *m_forwardDepthStencil;
	DepthStencil *m_SSAODepthStencil;

	//Deferred sampling
	DeferredSamplerEffectFile *m_deferredSampler;
	DeferredRenderingEffectFile* m_deferredRendering;

	RenderTarget *m_positionBuffer;
	RenderTarget *m_normalBuffer;
	RenderTarget *m_diffuseBuffer;
	RenderTarget *m_tangentBuffer;
	RenderTarget *m_glowBuffer;

	RenderTarget *m_positionBufferTransparant;
	RenderTarget *m_normalBufferTransparant;
	RenderTarget *m_diffuseBufferTransparant;
	RenderTarget *m_tangentBufferTransparant;
	RenderTarget *m_glowBufferTransparant;
	FullScreenPlane *m_deferredPlane;

	//Glow rendering
	GlowRenderingEffectFile* m_glowRendering;
	RenderTarget* m_glowRenderTarget;
	RenderTarget* m_glowRenderTarget2;
	D3D10_VIEWPORT m_glowViewport;

	//SSAO
	SSAOEffectFile* m_SSAORendering;

	//2D rendering
	SpriteEffectFile *m_spriteRendering;

	DeviceHandler* m_deviceHandler;
	
	vector<Text*> m_texts;
	vector<MyText*> m_myTexts;
	QuadTree* m_quadTree;
	vector<SpriteBase*> m_sprites;
	vector<Terrain*> m_terrains;
	vector<PointLight*> m_pointLights;
	vector<DirectionalLight*> m_directionalLights;
	vector<SpotLight*> m_spotLights;
	vector<Model*> m_models;

	// Shadow mapping
	D3D10_VIEWPORT m_shadowMapViewport;

	void renderShadowMap(const D3DXVECTOR2& _focalPoint);
public:
	World();
	World(DeviceHandler* _deviceHandler, HWND _hWnd, bool _windowed);
	~World();

	void render();
	void update(float dt);
	
	bool addRoad(Road* _road);
	bool removeRoad(Road* _road);
	
	bool addParticleEngine(ParticleEngine* _pe);
	bool removeParticleEngine(ParticleEngine* _pe);
	
	void addTerrain(Terrain* _terrain);
	bool removeTerrain(Terrain* _terrain);
	
	bool addModel(Model *_model);
	bool removeModel(Model *_model);

	void addSprite(SpriteBase *sprite);
	bool removeSprite(SpriteBase *sprite);
	
	void addText(Text* _text);
	bool removeText(Text* _text);
	
	void addMyText(MyText* _text);
	bool removeMyText(MyText* _text);

	bool addPointLight(PointLight* _pointLight, bool _static);
	bool removePointLight(PointLight* _pointLight);

	void addDirectionalLight(DirectionalLight* _directionalLight);
	bool removeDirectionalLight(DirectionalLight* _directionalLight);

	void addSpotLight(SpotLight* _spotLight);
	bool removeSpotLight(SpotLight* _spotLight);

	Camera *getCamera();
	void initQuadTree(FLOAT2 _extents);
};