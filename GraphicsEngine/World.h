#pragma once

#include "EffectFile.h"
#include "ForwardRenderingEffectFile.h"
#include "DeferredRenderingEffectFile.h"
#include "DeferredSamplerEffectFile.h"
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

	//Deferred sampling
	DeferredSamplerEffectFile *m_deferredSampler;
	DeferredRenderingEffectFile* m_deferredRendering;

	RenderTarget *m_positionBuffer;
	RenderTarget *m_normalBuffer;
	RenderTarget *m_diffuseBuffer;

	RenderTarget *m_positionBufferTransparant;
	RenderTarget *m_normalBufferTransparant;
	RenderTarget *m_diffuseBufferTransparant;
	FullScreenPlane *m_deferredPlane;

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
	vector<Road*> m_roads;

	// Shadow mapping
	D3D10_VIEWPORT m_shadowMapViewport;

	void renderShadowMap();
public:
	World();
	World(DeviceHandler* _deviceHandler, HWND _hWnd, bool _windowed);
	~World();

	void render();
	void update(float dt);
	
	bool addRoad(Road* _road);
	bool removeRoad(Road* _road);
	
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

	void addPointLight(PointLight* _pointLight);
	bool removePointLight(PointLight* _pointLight);

	void addDirectionalLight(DirectionalLight* _directionalLight);
	bool removeDirectionalLight(DirectionalLight* _directionalLight);

	void addSpotLight(SpotLight* _spotLight);
	bool removeSpotLight(SpotLight* _spotLight);

	Camera *getCamera();
};