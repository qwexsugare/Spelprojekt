#include "World.h"

World::World()
{
	m_quadTree = NULL;
}

World::World(DeviceHandler* _deviceHandler, HWND _hWnd, bool _windowed)
{
	this->m_deviceHandler = _deviceHandler;
	this->m_sprites = vector<SpriteBase*>();
	this->m_texts = vector<Text*>();
	m_quadTree = new QuadTree(0, D3DXVECTOR2(), D3DXVECTOR2());

	RECT rc;
	GetWindowRect(_hWnd, &rc);
	INT2 actualScreenSize = INT2(rc.right-rc.left, rc.bottom-rc.top);
	this->m_camera = new Camera(this->m_deviceHandler->getScreenSize(), actualScreenSize);

	this->m_forwardRendering = new ForwardRenderingEffectFile(this->m_deviceHandler->getDevice());
	this->m_forwardRenderTarget = new RenderTarget(this->m_deviceHandler->getDevice(), this->m_deviceHandler->getBackBuffer());
	this->m_forwardDepthStencil = new DepthStencil(this->m_deviceHandler->getDevice(), this->m_deviceHandler->getScreenSize(), true);
	this->m_SSAODepthStencil = new DepthStencil(this->m_deviceHandler->getDevice(), this->m_deviceHandler->getScreenSize(), true);

	this->m_deferredSampler = new DeferredSamplerEffectFile(this->m_deviceHandler->getDevice());
	this->m_deferredSampler->setProjectionMatrix(this->m_camera->getProjectionMatrix());
	this->m_deferredRendering = new DeferredRenderingEffectFile(this->m_deviceHandler->getDevice());
	m_forwardRendering->setProjectionMatrix(m_camera->getProjectionMatrix());

	this->m_positionBuffer = new RenderTarget(this->m_deviceHandler->getDevice(), this->m_deviceHandler->getScreenSize());
	this->m_normalBuffer = new RenderTarget(this->m_deviceHandler->getDevice(), this->m_deviceHandler->getScreenSize());
	this->m_diffuseBuffer = new RenderTarget(this->m_deviceHandler->getDevice(), this->m_deviceHandler->getScreenSize());
	this->m_tangentBuffer = new RenderTarget(this->m_deviceHandler->getDevice(), this->m_deviceHandler->getScreenSize());
	//Glow
	this->m_glowRendering = new GlowRenderingEffectFile(this->m_deviceHandler->getDevice());
	this->m_glowBuffer = new RenderTarget(this->m_deviceHandler->getDevice(), this->m_deviceHandler->getScreenSize());
	this->m_glowBufferTransparant = new RenderTarget(this->m_deviceHandler->getDevice(), this->m_deviceHandler->getScreenSize());
	int trollSize = 1920/4;
	int trollSize2 = 1080/4;
	this->m_glowRenderTarget = new RenderTarget(this->m_deviceHandler->getDevice(), INT2(trollSize, trollSize2));
	this->m_glowRenderTarget2 = new RenderTarget(this->m_deviceHandler->getDevice(), INT2(trollSize, trollSize2));

	//SSAO
	this->m_SSAORendering = new SSAOEffectFile(this->m_deviceHandler->getDevice());

	this->m_positionBufferTransparant = new RenderTarget(this->m_deviceHandler->getDevice(), this->m_deviceHandler->getScreenSize());
	this->m_normalBufferTransparant = new RenderTarget(this->m_deviceHandler->getDevice(), this->m_deviceHandler->getScreenSize());
	this->m_diffuseBufferTransparant = new RenderTarget(this->m_deviceHandler->getDevice(), this->m_deviceHandler->getScreenSize());
	this->m_tangentBufferTransparant = new RenderTarget(this->m_deviceHandler->getDevice(), this->m_deviceHandler->getScreenSize());
	
	this->m_deferredPlane = new FullScreenPlane(this->m_deviceHandler->getDevice(), NULL);
	this->m_spriteRendering = new SpriteEffectFile(this->m_deviceHandler->getDevice());

	//m_glowViewport.Width = this->m_deviceHandler->getScreenSize().x/2;
	//m_glowViewport.Height = this->m_deviceHandler->getScreenSize().y/2;
	m_glowViewport.Width = trollSize;
	m_glowViewport.Height = trollSize2;
	m_glowViewport.MinDepth = 0.0f;
	m_glowViewport.MaxDepth = 1.0f;
	m_glowViewport.TopLeftX = 0;
	m_glowViewport.TopLeftY = 0;
	
	m_shadowMapViewport.Width = 512;
	m_shadowMapViewport.Height = 512;
	m_shadowMapViewport.MinDepth = 0.0f;
	m_shadowMapViewport.MaxDepth = 1.0f;
	m_shadowMapViewport.TopLeftX = 0;
	m_shadowMapViewport.TopLeftY = 0;
}

World::~World()
{
	for(int i = 0; i < m_terrains.size(); i++)
		delete m_terrains[i];
	for(int i = 0; i < m_models.size(); i++)
		delete m_models[i];

	for(int i = 0; i < this->m_sprites.size(); i++)
	{
		delete this->m_sprites[i];
	}

	for(int i = 0; i < this->m_pointLights.size(); i++)
	{
		delete this->m_pointLights[i];
	}

	for(int i = 0; i < this->m_directionalLights.size(); i++)
	{
		delete this->m_directionalLights[i];
	}

	for(int i = 0; i < this->m_spotLights.size(); i++)
	{
		delete this->m_spotLights[i];
	}
	
	for(int i = 0; i < this->m_texts.size(); i++)
		delete this->m_texts[i];

	for(int i = 0; i < this->m_myTexts.size(); i++)
		delete this->m_myTexts[i];

	delete this->m_forwardRendering;
	delete this->m_forwardRenderTarget;
	delete this->m_forwardDepthStencil;
	delete this->m_SSAODepthStencil;
	delete this->m_spriteRendering;

	delete this->m_deferredPlane;
	delete this->m_deferredSampler;
	delete this->m_deferredRendering;
	delete this->m_glowRendering;
	delete this->m_SSAORendering;

	delete this->m_positionBuffer;
	delete this->m_normalBuffer;
	delete this->m_diffuseBuffer;
	delete this->m_tangentBuffer;
	delete this->m_glowBuffer;
	delete this->m_glowRenderTarget;
	delete this->m_glowRenderTarget2;


	delete this->m_positionBufferTransparant;
	delete this->m_normalBufferTransparant;
	delete this->m_diffuseBufferTransparant;
	delete this->m_tangentBufferTransparant;
	delete this->m_glowBufferTransparant;

	delete this->m_camera;
	if(m_quadTree)
		delete this->m_quadTree;
}

bool World::addRoad(Road* _road)
{
	return this->m_quadTree->addRoad(_road);
}

bool World::removeRoad(Road* _road)
{
	return this->m_quadTree->removeRoad(_road);
}

bool World::addParticleEngine(ParticleEngine* _pe)
{
	return m_quadTree->addParticleEngine(_pe);
}

bool World::removeParticleEngine(ParticleEngine* _pe)
{
	return m_quadTree->removeParticleEngine(_pe);
}

void World::addTerrain(Terrain* _terrain)
{
	this->m_terrains.push_back(_terrain);
}

bool World::removeTerrain(Terrain* _terrain)
{
	bool found = false;

	for(int i = 0; i < m_terrains.size() && !found; i++)
	{
		if(m_terrains[i] == _terrain)
		{
			delete m_terrains[i];
			m_terrains.erase(m_terrains.begin()+i);
			found = true;
		}
	}

	return found;
}

void World::render()
{
	D3DXVECTOR2 focalPoint = D3DXVECTOR2(m_camera->getPos2D().x, m_camera->getPos2D().y+4.0f);

	//Init render stuff
	this->m_camera->updateViewMatrix();
	this->m_deferredSampler->setViewMatrix(this->m_camera->getViewMatrix());
	this->m_deviceHandler->setInputLayout(this->m_deferredSampler->getInputLayout());
	
	//clear render target
	this->m_positionBuffer->clear(this->m_deviceHandler->getDevice());
	this->m_normalBuffer->clear(this->m_deviceHandler->getDevice());
	this->m_diffuseBuffer->clear(this->m_deviceHandler->getDevice());
	this->m_tangentBuffer->clear(this->m_deviceHandler->getDevice());
	this->m_glowBuffer->clear(this->m_deviceHandler->getDevice());
	m_forwardDepthStencil->clear(this->m_deviceHandler->getDevice());
	m_forwardRenderTarget->clear(m_deviceHandler->getDevice());
	
	this->renderShadowMap(focalPoint);

	ID3D10RenderTargetView *renderTargets[5];
	renderTargets[0] = *this->m_positionBuffer->getRenderTargetView();
	renderTargets[1] = *this->m_normalBuffer->getRenderTargetView();
	renderTargets[2] = *this->m_diffuseBuffer->getRenderTargetView();
	renderTargets[3] = *this->m_tangentBuffer->getRenderTargetView();
	renderTargets[4] = *this->m_glowBuffer->getRenderTargetView();

	this->m_deviceHandler->getDevice()->RSSetViewports( 1, &this->m_deviceHandler->getViewport());
	this->m_deviceHandler->getDevice()->OMSetRenderTargets(5, renderTargets , this->m_forwardDepthStencil->getDepthStencilView());
	
	// Render terrains
	this->m_deviceHandler->getDevice()->IASetPrimitiveTopology( D3D10_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP );
	for(int i = 0; i < this->m_terrains.size(); i++)
	{
		this->m_deviceHandler->setVertexBuffer(m_terrains[i]->getVertexBuffer(), sizeof(Vertex));

		this->m_deferredSampler->setModelMatrix(m_terrains[i]->getModelMatrix());
		this->m_deferredSampler->setTerrainTextures(m_terrains[i]->getTextures(), m_terrains[i]->getNrOfTextures());
		this->m_deferredSampler->setTerrainBlendMaps(m_terrains[i]->getBlendMaps(), m_terrains[i]->getNrOfBlendMaps());
		this->m_deferredSampler->setTerrainNormalMaps(m_terrains[i]->getNormalMap(), m_terrains[i]->getNrOfTextures());
		this->m_deferredSampler->setTerrainSpecularMaps(m_terrains[i]->getSpecularMap(), m_terrains[i]->getNrOfTextures());
			
		this->m_deferredSampler->getRenderTerrainTechnique()->GetPassByIndex(0)->Apply(0);
		this->m_deviceHandler->getDevice()->Draw(m_terrains[i]->getNrOfVertices(), 0);
	}
	
	//Render all models
	this->m_deviceHandler->getDevice()->IASetPrimitiveTopology( D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST );
	stack<Model*> staticModels = this->m_quadTree->getModels(focalPoint);
	vector<Model*> transparentStaticModels;
	while(!staticModels.empty())
	{
		if(staticModels.top()->getAlpha() < 1.0f)
		{
			if(transparentStaticModels.size() == 0)
			{
				transparentStaticModels.push_back(staticModels.top());
			}
			else
			{
				if(staticModels.top()->getPosition().y <= transparentStaticModels[0]->getPosition().y)
					transparentStaticModels.insert(transparentStaticModels.begin(), staticModels.top());
				else
				{
					bool inserted = false;
					for(int i = 1; i < transparentStaticModels.size()-1 && !inserted; i++)
					{
						if(staticModels.top()->getPosition().y > transparentStaticModels[i]->getPosition().y && staticModels.top()->getPosition().y <= transparentStaticModels[i+1]->getPosition().y)
						{
							transparentStaticModels.insert(transparentStaticModels.begin()+i, staticModels.top());
							inserted = true;
						}
					}
					if(!inserted)
					{
						transparentStaticModels.push_back(staticModels.top());
					}
				}
			}
		}
		else
		{
			this->m_deferredSampler->setModelMatrix(staticModels.top()->getModelMatrix());
			this->m_deferredSampler->setModelAlpha(staticModels.top()->getAlpha());

			for(int m = 0; m < staticModels.top()->getMesh()->subMeshes.size(); m++)
			{
				this->m_deferredSampler->setTexture(staticModels.top()->getMesh()->subMeshes[m]->textures[staticModels.top()->getTextureIndex()]);
				this->m_deferredSampler->setNormalMap(staticModels.top()->getMesh()->subMeshes[m]->textures["normalCamera"]);
				if(staticModels.top()->getGlowIndex() != "")
					this->m_deferredSampler->setGlowMap(staticModels.top()->getMesh()->subMeshes[m]->textures[staticModels.top()->getGlowIndex()]);
				this->m_deferredSampler->setSpecularMap(staticModels.top()->getMesh()->subMeshes[m]->textures["specularColor"]);

				if(staticModels.top()->getMesh()->isAnimated)
				{
					//this->m_deferredSampler->setBoneTexture(models.top()->getAnimation()->getResource());
					//this->m_deviceHandler->setVertexBuffer(models.top()->getMesh()->subMeshes[m]->buffer, sizeof(AnimationVertex));
					//this->m_deviceHandler->setInputLayout(this->m_deferredSampler->getInputAnimationLayout());
					//this->m_deferredSampler->getAnimationTechnique()->GetPassByIndex( 0 )->Apply(0);
				}
				else
				{
					this->m_deviceHandler->setVertexBuffer(staticModels.top()->getMesh()->subMeshes[m]->buffer, sizeof(SuperVertex));
					this->m_deviceHandler->setInputLayout(this->m_deferredSampler->getSuperInputLayout());

					D3D10_TECHNIQUE_DESC desc;
					m_deferredSampler->getSuperTechnique()->GetDesc(&desc);

					this->m_deferredSampler->getSuperTechnique()->GetPassByIndex(1)->Apply(0);
					this->m_deviceHandler->getDevice()->Draw(staticModels.top()->getMesh()->subMeshes[m]->numVerts, 0);

					//for(int i = 0; i < desc.Passes; i++)
					//{
					//	this->m_deferredSampler->getSuperTechnique()->GetPassByIndex( i )->Apply(0);
					//	this->m_deviceHandler->getDevice()->Draw(models.top()->getMesh()->subMeshes[m]->numVerts, 0);
					//}
				}
			}
		}

		staticModels.pop();
	}
	
	
	vector<Model*> transparentModels;
	for(int i = 0; i < m_models.size(); i++)
	{
		// Calculate models distance to camera and make it positive
		D3DXVECTOR2 modelDistanceToCamera = m_models[i]->getPosition2D()-focalPoint;
		modelDistanceToCamera.x = abs(modelDistanceToCamera.x);
		modelDistanceToCamera.y = abs(modelDistanceToCamera.y);

		// Find the greatest extent of the model bounding box
		float greatestExtent;
		if(m_models[i]->getObb())
		{
			if(this->m_models[i]->getObb()->Extents.x > this->m_models[i]->getObb()->Extents.z)
				greatestExtent = this->m_models[i]->getObb()->Extents.x;
			else
				greatestExtent = this->m_models[i]->getObb()->Extents.z;
		}
		else if(m_models[i]->getBs())
		{
			greatestExtent = this->m_models[i]->getBs()->Radius;
		}
		else
		{
			// we are fucked
			greatestExtent = 1337;
		}

		// Subtract the greatest extent from the distance
		modelDistanceToCamera.x -= greatestExtent;
		modelDistanceToCamera.y -= greatestExtent;

		if(modelDistanceToCamera.x < 6.0f && modelDistanceToCamera.y < 4.0f)
		{
			if(m_models[i]->getAlpha() < 1.0f)
			{
				if(transparentModels.size() == 0)
				{
					transparentModels.push_back(m_models[i]);
				}
				else
				{
					if(m_models[i]->getPosition().y <= transparentModels[0]->getPosition().y)
						transparentModels.insert(transparentModels.begin(), m_models[i]);
					else
					{
						bool inserted = false;
						for(int j = 1; j < transparentModels.size()-1 && !inserted; j++)
						{
							if(m_models[i]->getPosition().y > transparentModels[j]->getPosition().y && m_models[i]->getPosition().y <= transparentModels[j+1]->getPosition().y)
							{
								transparentModels.insert(transparentModels.begin()+j, m_models[i]);
								inserted = true;
							}
						}
						if(!inserted)
						{
							transparentModels.push_back(m_models[i]);
						}
					}
				}
			}
			else
			{
				this->m_deferredSampler->setModelMatrix(m_models[i]->getModelMatrix());
				this->m_deferredSampler->setModelAlpha(m_models[i]->getAlpha());

				for(int m = 0; m < m_models[i]->getMesh()->subMeshes.size(); m++)
				{
					this->m_deferredSampler->setTexture(m_models[i]->getMesh()->subMeshes[m]->textures[m_models[i]->getTextureIndex()]);
					this->m_deferredSampler->setNormalMap(m_models[i]->getMesh()->subMeshes[m]->textures["normalCamera"]);
					if(m_models[i]->getGlowIndex() != "")
						this->m_deferredSampler->setGlowMap(m_models[i]->getMesh()->subMeshes[m]->textures[m_models[i]->getGlowIndex()]);
					this->m_deferredSampler->setSpecularMap(m_models[i]->getMesh()->subMeshes[m]->textures["specularColor"]);

					if(m_models[i]->getMesh()->isAnimated)
					{
						m_models[i]->getAnimation()->UpdateSkeletonTexture();
						this->m_deferredSampler->setBoneTexture(m_models[i]->getAnimation()->getResource());
						this->m_deviceHandler->setVertexBuffer(m_models[i]->getMesh()->subMeshes[m]->buffer, sizeof(AnimationVertex));
						this->m_deviceHandler->setInputLayout(this->m_deferredSampler->getInputAnimationLayout());
						this->m_deferredSampler->getAnimationTechnique()->GetPassByIndex( 0 )->Apply(0);
						this->m_deviceHandler->getDevice()->Draw(m_models[i]->getMesh()->subMeshes[m]->numVerts, 0);
						//Draw Props
						if(m_models[i]->getHat())
						{	
							this->m_deferredSampler->setTexture(m_models[i]->getHat()->subMeshes[m]->textures["color"]);
							this->m_deferredSampler->setGlowMap(m_models[i]->getHat()->subMeshes[m]->textures["glowIntensity"]);

							this->m_deferredSampler->setPropsMatrix(m_models[i]->getAnimation()->getHatMatrix());
							this->m_deviceHandler->setVertexBuffer(m_models[i]->getHat()->subMeshes[m]->buffer, sizeof(SuperVertex));
							this->m_deferredSampler->getPropsTechnique()->GetPassByIndex( 0 )->Apply(0);
							this->m_deviceHandler->getDevice()->Draw(m_models[i]->getHat()->subMeshes[m]->numVerts, 0);
						}
						if(m_models[i]->getRightHand())
						{
							this->m_deferredSampler->setTexture(m_models[i]->getRightHand()->subMeshes[m]->textures["color"]);

							this->m_deferredSampler->setPropsMatrix(m_models[i]->getAnimation()->getRightHandMatrix());
							this->m_deviceHandler->setVertexBuffer(m_models[i]->getRightHand()->subMeshes[m]->buffer, sizeof(SuperVertex));
							this->m_deferredSampler->getPropsTechnique()->GetPassByIndex( 0 )->Apply(0);
							this->m_deviceHandler->getDevice()->Draw(m_models[i]->getRightHand()->subMeshes[m]->numVerts, 0);
						}
						if(m_models[i]->getLeftHand())
						{
							this->m_deferredSampler->setTexture(m_models[i]->getLeftHand()->subMeshes[m]->textures["color"]);
							this->m_deferredSampler->setGlowMap(m_models[i]->getLeftHand()->subMeshes[m]->textures["glowIntensity"]);

							this->m_deferredSampler->setPropsMatrix(m_models[i]->getAnimation()->getLeftHandMatrix());
							this->m_deviceHandler->setVertexBuffer(m_models[i]->getLeftHand()->subMeshes[m]->buffer, sizeof(SuperVertex));
							this->m_deferredSampler->getPropsTechnique()->GetPassByIndex( 0 )->Apply(0);
							this->m_deviceHandler->getDevice()->Draw(m_models[i]->getLeftHand()->subMeshes[m]->numVerts, 0);
						}
					}
					else
					{
						m_deviceHandler->setVertexBuffer(m_models[i]->getMesh()->subMeshes[m]->buffer, sizeof(SuperVertex));
						m_deviceHandler->setInputLayout(m_deferredSampler->getSuperInputLayout());
						//this->m_deviceHandler->getDevice()->OMSetRenderTargets(5, renderTargets , this->m_forwardDepthStencil->getDepthStencilView());
						this->m_deferredSampler->getSuperTechnique()->GetPassByIndex(0)->Apply(0);
						this->m_deviceHandler->getDevice()->Draw(m_models[i]->getMesh()->subMeshes[m]->numVerts, 0);
					}
				}
			}
		}
	}

	//clear render target
	this->m_positionBufferTransparant->clear(this->m_deviceHandler->getDevice());
	this->m_normalBufferTransparant->clear(this->m_deviceHandler->getDevice());
	this->m_diffuseBufferTransparant->clear(this->m_deviceHandler->getDevice());
	this->m_tangentBufferTransparant->clear(this->m_deviceHandler->getDevice());
	//this->m_glowBufferTransparant->clear(this->m_deviceHandler->getDevice());

	renderTargets[0] = *this->m_positionBufferTransparant->getRenderTargetView();
	renderTargets[1] = *this->m_normalBufferTransparant->getRenderTargetView();
	renderTargets[2] = *this->m_diffuseBufferTransparant->getRenderTargetView();
	renderTargets[3] = *this->m_tangentBufferTransparant->getRenderTargetView();
	//renderTargets[4] = *this->m_glowBufferTransparant->getRenderTargetView();

	this->m_deviceHandler->getDevice()->OMSetRenderTargets(5, renderTargets , this->m_forwardDepthStencil->getDepthStencilView());
	this->m_deviceHandler->getDevice()->IASetPrimitiveTopology( D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST );


	// Render roads yo dawg y u be messin' about
	stack<Road*> roads = m_quadTree->getRoads(focalPoint);
	this->m_deviceHandler->getDevice()->IASetPrimitiveTopology( D3D10_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP );
	while(!roads.empty())
	{
		this->m_deviceHandler->setVertexBuffer(roads.top()->getVertexBuffer(), sizeof(Vertex));
		this->m_deferredSampler->setModelMatrix(roads.top()->getModelMatrix());
		this->m_deferredSampler->setTexture(roads.top()->getTexture());
		this->m_deferredSampler->getRenderRoadTechnique()->GetPassByIndex(0)->Apply(0);
		this->m_deviceHandler->getDevice()->Draw(roads.top()->getNrOfVertices(), 0);

		roads.pop();
	}
	
	this->m_deviceHandler->getDevice()->IASetPrimitiveTopology( D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST );
	for(int i = 0; i < transparentStaticModels.size(); i++)
	{
		this->m_deferredSampler->setModelMatrix(transparentStaticModels[i]->getModelMatrix());
		this->m_deferredSampler->setModelAlpha(transparentStaticModels[i]->getAlpha());

		for(int m = 0; m < transparentStaticModels[i]->getMesh()->subMeshes.size(); m++)
		{
			this->m_deferredSampler->setTexture(transparentStaticModels[i]->getMesh()->subMeshes[m]->textures[transparentStaticModels[i]->getTextureIndex()]);
			this->m_deferredSampler->setNormalMap(transparentStaticModels[i]->getMesh()->subMeshes[m]->textures["normalCamera"]);
			if(transparentStaticModels[i]->getGlowIndex() != "")
				this->m_deferredSampler->setGlowMap(transparentStaticModels[i]->getMesh()->subMeshes[m]->textures[transparentStaticModels[i]->getGlowIndex()]);
			this->m_deferredSampler->setSpecularMap(transparentStaticModels[i]->getMesh()->subMeshes[m]->textures["specularColor"]);

			if(transparentStaticModels[i]->getMesh()->isAnimated)
			{
				transparentStaticModels[i]->getAnimation()->UpdateSkeletonTexture();
				this->m_deferredSampler->setBoneTexture(transparentStaticModels[i]->getAnimation()->getResource());
				this->m_deviceHandler->setVertexBuffer(transparentStaticModels[i]->getMesh()->subMeshes[m]->buffer, sizeof(AnimationVertex));
				this->m_deviceHandler->setInputLayout(this->m_deferredSampler->getInputAnimationLayout());
				this->m_deferredSampler->getAnimationTechnique()->GetPassByIndex( 0 )->Apply(0);
			}
			else
			{
				this->m_deviceHandler->setVertexBuffer(transparentStaticModels[i]->getMesh()->subMeshes[m]->buffer, sizeof(SuperVertex));
				this->m_deviceHandler->setInputLayout(this->m_deferredSampler->getSuperInputLayout());
				this->m_deferredSampler->getSuperTechnique()->GetPassByIndex( 0 )->Apply(0);
			}

			this->m_deviceHandler->getDevice()->Draw(transparentStaticModels[i]->getMesh()->subMeshes[m]->numVerts, 0);
		}
	}

	for(int i = 0; i < transparentModels.size(); i++)
	{
		this->m_deferredSampler->setModelMatrix(transparentModels[i]->getModelMatrix());
		this->m_deferredSampler->setModelAlpha(transparentModels[i]->getAlpha());

		for(int m = 0; m < transparentModels[i]->getMesh()->subMeshes.size(); m++)
		{
			m_deferredSampler->setTexture(transparentModels[i]->getMesh()->subMeshes[m]->textures[transparentModels[i]->getTextureIndex()]);
			m_deferredSampler->setNormalMap(transparentModels[i]->getMesh()->subMeshes[m]->textures["normalCamera"]);
			if(transparentModels[i]->getGlowIndex() != "")
				this->m_deferredSampler->setGlowMap(transparentModels[i]->getMesh()->subMeshes[m]->textures[transparentModels[i]->getGlowIndex()]);
			m_deferredSampler->setSpecularMap(transparentModels[i]->getMesh()->subMeshes[m]->textures["specularColor"]);

			if(transparentModels[i]->getMesh()->isAnimated)
			{
				//this->m_forwardRendering->setBoneTexture(models.top()->getAnimation()->getResource());
				//this->m_deviceHandler->setVertexBuffer(models.top()->getMesh()->subMeshes[m]->buffer, sizeof(AnimationVertex));
				//this->m_deviceHandler->setInputLayout(this->m_deferredSampler->getInputAnimationLayout());
				//this->m_deferredSampler->getAnimationTechnique()->GetPassByIndex( 0 )->Apply(0);
			}
			else
			{
				m_deviceHandler->setVertexBuffer(transparentModels[i]->getMesh()->subMeshes[m]->buffer, sizeof(SuperVertex));
				m_deviceHandler->setInputLayout(m_deferredSampler->getSuperInputLayout());
				//this->m_deviceHandler->getDevice()->OMSetRenderTargets(5, renderTargets , this->m_forwardDepthStencil->getDepthStencilView());
				this->m_deferredSampler->getSuperTechnique()->GetPassByIndex(0)->Apply(0);
				this->m_deviceHandler->getDevice()->Draw(transparentModels[i]->getMesh()->subMeshes[m]->numVerts, 0);
			}
		}
	}
	

		
	
	this->m_forwardRenderTarget->clear(this->m_deviceHandler->getDevice());

	//Deferred
	this->m_forwardRendering->setViewMatrix(this->m_camera->getViewMatrix());
	this->m_forwardRendering->setProjectionMatrix(this->m_camera->getProjectionMatrix());
	this->m_forwardRenderTarget->clear(this->m_deviceHandler->getDevice());

	this->m_deviceHandler->getDevice()->RSSetViewports( 1, &this->m_deviceHandler->getViewport());
	this->m_deviceHandler->getDevice()->OMSetRenderTargets(1, this->m_forwardRenderTarget->getRenderTargetView(), this->m_forwardDepthStencil->getDepthStencilView());
	this->m_deviceHandler->getDevice()->IASetPrimitiveTopology( D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST );

	this->m_deviceHandler->setInputLayout(this->m_deferredRendering->getVertexLayout());
	this->m_deferredRendering->setPositionsTexture(this->m_positionBuffer->getShaderResource());
	this->m_deferredRendering->setNormalsTexture(this->m_normalBuffer->getShaderResource());
	this->m_deferredRendering->setDiffuseTexture(this->m_diffuseBuffer->getShaderResource());
	this->m_deferredRendering->setTangentTexture(this->m_tangentBuffer->getShaderResource());

	this->m_deferredRendering->setCameraPosition(this->m_camera->m_forward);
	this->m_deferredRendering->updateLights(this->m_quadTree->getPointLights(focalPoint), this->m_directionalLights, this->m_spotLights);

	this->m_deviceHandler->setVertexBuffer(this->m_deferredPlane->getMesh()->buffer, sizeof(Vertex));

	D3D10_TECHNIQUE_DESC techDesc;
	this->m_deferredRendering->getTechnique()->GetDesc( &techDesc );

	for( UINT p = 0; p < techDesc.Passes; p++ )
	{
		this->m_deferredRendering->getTechnique()->GetPassByIndex( p )->Apply(0);
		this->m_deviceHandler->getDevice()->Draw(this->m_deferredPlane->getMesh()->nrOfVertices, 0);
	}

	this->m_deferredRendering->setPositionsTexture(this->m_positionBufferTransparant->getShaderResource());
	this->m_deferredRendering->setNormalsTexture(this->m_normalBufferTransparant->getShaderResource());
	this->m_deferredRendering->setDiffuseTexture(this->m_diffuseBufferTransparant->getShaderResource());
	this->m_deferredRendering->setTangentTexture(this->m_tangentBufferTransparant->getShaderResource());

	for( UINT p = 0; p < techDesc.Passes; p++ )
	{
		this->m_deferredRendering->getTechnique()->GetPassByIndex( p )->Apply(0);
		this->m_deviceHandler->getDevice()->Draw(this->m_deferredPlane->getMesh()->nrOfVertices, 0);
	}
	
	this->m_deviceHandler->setVertexBuffer(this->m_deferredPlane->getMesh()->buffer, sizeof(Vertex));

	
	/////SSAO START
	////this->m_forwardDepthStencil->clear(m_deviceHandler->getDevice());
	//this->m_SSAORendering->setDepthTexture(this->m_forwardDepthStencil->getShaderResource());
	//this->m_deviceHandler->getDevice()->RSSetViewports( 1, &this->m_deviceHandler->getViewport());
	//this->m_deviceHandler->getDevice()->OMSetRenderTargets(1, m_forwardRenderTarget->getRenderTargetView(), m_SSAODepthStencil->getDepthStencilView());

	//D3D10_TECHNIQUE_DESC SSAOTechDesc;
	//this->m_SSAORendering->getTechnique()->GetDesc( &SSAOTechDesc );

	//for( UINT p = 0; p < SSAOTechDesc.Passes; p++ )
	//{
	//	this->m_SSAORendering->getTechnique()->GetPassByIndex( p )->Apply(0);
	//	this->m_deviceHandler->getDevice()->Draw(this->m_deferredPlane->getMesh()->nrOfVertices, 0);
	//}
	////SSAO END


	//Glow

	m_glowRenderTarget->clear(m_deviceHandler->getDevice());
	//m_forwardDepthStencil->clear(m_deviceHandler->getDevice());

	//HorizontalBlur
	this->m_glowRendering->setGlowTexture(this->m_glowBuffer->getShaderResource());
	this->m_deviceHandler->getDevice()->RSSetViewports( 1, &this->m_glowViewport);
	this->m_deviceHandler->getDevice()->OMSetRenderTargets(1, this->m_glowRenderTarget->getRenderTargetView(), this->m_forwardDepthStencil->getDepthStencilView());

	D3D10_TECHNIQUE_DESC techGlowHoriDesc;
	this->m_glowRendering->getTechniqueHori()->GetDesc( &techGlowHoriDesc );

	for( UINT p = 0; p < techGlowHoriDesc.Passes; p++ )
	{
		this->m_glowRendering->getTechniqueHori()->GetPassByIndex( p )->Apply(0);
		this->m_deviceHandler->getDevice()->Draw(this->m_deferredPlane->getMesh()->nrOfVertices, 0);
	}

	//VerticalBlur
	this->m_glowRendering->setGlowTexture(this->m_glowRenderTarget->getShaderResource());
	this->m_deviceHandler->getDevice()->OMSetRenderTargets(1, this->m_glowRenderTarget2->getRenderTargetView(), this->m_forwardDepthStencil->getDepthStencilView());

	D3D10_TECHNIQUE_DESC techGlowVertDesc;
	this->m_glowRendering->getTechniqueVert()->GetDesc( &techGlowVertDesc );

	for( UINT p = 0; p < techGlowVertDesc.Passes; p++ )
	{
		this->m_glowRendering->getTechniqueVert()->GetPassByIndex( p )->Apply(0);
		this->m_deviceHandler->getDevice()->Draw(this->m_deferredPlane->getMesh()->nrOfVertices, 0);
	}
	
	//UpSample
	this->m_glowRendering->setGlowTexture(this->m_glowRenderTarget2->getShaderResource());
	
	this->m_deviceHandler->getDevice()->RSSetViewports( 1, &this->m_deviceHandler->getViewport());
	this->m_deviceHandler->getDevice()->OMSetRenderTargets(1, this->m_forwardRenderTarget->getRenderTargetView(), this->m_forwardDepthStencil->getDepthStencilView());
	
	D3D10_TECHNIQUE_DESC techGlowDesc;
	this->m_glowRendering->getTechnique()->GetDesc( &techGlowDesc );

	for( UINT p = 0; p < techGlowDesc.Passes; p++ )
	{
		this->m_glowRendering->getTechnique()->GetPassByIndex( p )->Apply(0);
		this->m_deviceHandler->getDevice()->Draw(this->m_deferredPlane->getMesh()->nrOfVertices, 0);
	}

	//FinalGlow
	this->m_glowRendering->setGlowTexture(this->m_glowBuffer->getShaderResource());
	D3D10_TECHNIQUE_DESC techGlowDesc2;
	this->m_glowRendering->getTechnique()->GetDesc( &techGlowDesc2 );

	for( UINT p = 0; p < techGlowDesc2.Passes; p++ )
	{
		this->m_glowRendering->getTechnique()->GetPassByIndex( p )->Apply(0);
		this->m_deviceHandler->getDevice()->Draw(this->m_deferredPlane->getMesh()->nrOfVertices, 0);
	}
	//GlowEnd


	/////////////////////////////////////////////////////////////////////////
	//PPPPP//AAAAAA//RRRRR///TTTTTTTT//II//CCCCCC//LL//////EEEEEEE//SSSSSSS//
	//PPPPP//AA//AA//RRRRR//////TT/////II//CC//////LL//////EE///////SS///////
	//PP/////AAAAAA//RRRR///////TT/////II//CC//////LL//////EEEE/////SSSSSSS//
	//PP/////AA//AA//RR//RR/////TT/////II//CCCCCC//LLLLLL//EEEEEEE//SSSSSSS//
	/////////////////////////////////////////////////////////////////////////

	// Particle Engines (Systems)
	stack<ParticleEngine*> pes = m_quadTree->getParticleEngines(focalPoint);
	while(!pes.empty())
	{
		//pes.top()->getstuffandrendershit();
		/* What do you call a sheep with no legs? A cloud. */
		pes.pop();
	}
	
	m_deviceHandler->getDevice()->OMSetRenderTargets(1, m_forwardRenderTarget->getRenderTargetView(), m_forwardDepthStencil->getDepthStencilView());

	for(int i = 0; i < m_models.size(); i++)
	{
		m_forwardRendering->setModelMatrix(m_models[i]->getModelMatrix());

		for(int m = 0; m < m_models[i]->getMesh()->subMeshes.size(); m++)
		{
			if(m_models[i]->getMesh()->isAnimated)
			{
				//this->m_deferredSampler->setBoneTexture(m_models[i]->getAnimation()->getResource());
				//this->m_deviceHandler->setVertexBuffer(m_models[i]->getMesh()->subMeshes[m]->buffer, sizeof(AnimationVertex));
				//this->m_deviceHandler->setInputLayout(this->m_deferredSampler->getInputAnimationLayout());
				//this->m_deferredSampler->getAnimationTechnique()->GetPassByIndex( 0 )->Apply(0);
				//this->m_deviceHandler->getDevice()->Draw(m_models[i]->getMesh()->subMeshes[m]->numVerts, 0);
			}
			else
			{				
				m_deviceHandler->setVertexBuffer(m_models[i]->getMesh()->subMeshes[m]->buffer, sizeof(SuperVertex));
				m_deviceHandler->setInputLayout(m_deferredSampler->getSuperInputLayout());				
				m_forwardRendering->m_forwardGubb->GetPassByIndex(0)->Apply(0);
				this->m_deviceHandler->getDevice()->Draw(m_models[i]->getMesh()->subMeshes[m]->numVerts, 0);
			}
		}
	}
	
	//Sprites
	for(int i = 0; i < this->m_sprites.size(); i++)
	{
		if(this->m_sprites[i]->getVisible() == true)
		{
			this->m_deviceHandler->setVertexBuffer(m_sprites[i]->getBuffer(), sizeof(Vertex));

			this->m_spriteRendering->setModelMatrix(m_sprites[i]->getModelMatrix());
			this->m_spriteRendering->setTexture(m_sprites[i]->getTexture());

			D3D10_TECHNIQUE_DESC techDesc;
			this->m_spriteRendering->getTechnique()->GetDesc( &techDesc );

			for( UINT p = 0; p < techDesc.Passes; p++ )
			{
				this->m_spriteRendering->getTechnique()->GetPassByIndex( p )->Apply(0);
				this->m_deviceHandler->getDevice()->Draw(m_sprites[i]->getNrOfVertices(), this->m_sprites[i]->getStartIndex());
			}
		}
	}
	
	// Render texts
	for(int i = 0; i < this->m_myTexts.size(); i++)
	{
		if(this->m_myTexts[i]->getVisible() == true)
		{
			this->m_deviceHandler->setVertexBuffer(m_myTexts[i]->getBuffer(), sizeof(Vertex));

			this->m_spriteRendering->setModelMatrix(this->m_myTexts[i]->getModelMatrix());
			this->m_spriteRendering->setTexture(m_myTexts[i]->getTexture());

			D3D10_TECHNIQUE_DESC techDesc;
			this->m_spriteRendering->getTechnique()->GetDesc( &techDesc );

			for( UINT p = 0; p < techDesc.Passes; p++ )
			{
				this->m_spriteRendering->getTechnique()->GetPassByIndex( p )->Apply(0);
				this->m_deviceHandler->getDevice()->Draw(m_myTexts[i]->getNumberOfPoints(), 0);
			}
		}
	}
	
	// Render texts
	for(int i = 0; i < this->m_texts.size(); i++)
	{
		this->m_texts[i]->render();
	}

	//Finish render
	this->m_deviceHandler->present();
}

void World::renderShadowMap(const D3DXVECTOR2& _focalPoint)
{
	m_deviceHandler->getDevice()->RSSetViewports(1, &m_shadowMapViewport);

	vector<PointLight*> pointLights = this->m_quadTree->getPointLights(_focalPoint);
	ID3D10ShaderResourceView** resources = new ID3D10ShaderResourceView*[pointLights.size() * 6];
	D3DXMATRIX* wvps = new D3DXMATRIX[pointLights.size() * 6];
	
	m_deviceHandler->getDevice()->IASetPrimitiveTopology( D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST );
	int counter = 0;

	for(int i = 0; i < pointLights.size() && i * 6 < 100; i++)
	{
		if(pointLights[i]->getCastShadow() == true)
		{
			pointLights[i]->clearShadowMap(m_deviceHandler->getDevice());

			for(int j = 0; j < 6; j++)
			{
				m_deferredSampler->setLightWvp(pointLights[i]->getMatrix(j));
				pointLights[i]->setShadowMapAsRenderTarget(m_deviceHandler->getDevice(), j);

				stack<Model*> models = this->m_quadTree->getAllModels();
				while(!models.empty() && i * 6 + j < 100)
				{
					if(models.top()->getAlpha() == 1.0f)
					{
						this->m_deferredSampler->setModelMatrix(models.top()->getModelMatrix());
						//this->m_deferredSampler->setModelAlpha(models.top()->getAlpha());

						for(int m = 0; m < models.top()->getMesh()->subMeshes.size(); m++)
						{
							if(models.top()->getMesh()->isAnimated)
							{
								this->m_deferredSampler->setBoneTexture(models.top()->getAnimation()->getResource());
								this->m_deviceHandler->setVertexBuffer(models.top()->getMesh()->subMeshes[m]->buffer, sizeof(AnimationVertex));
								this->m_deviceHandler->setInputLayout(this->m_deferredSampler->getInputAnimationLayout());
								m_deferredSampler->renderShadowMap->GetPassByIndex(0)->Apply(0);
							}
							else
							{
								this->m_deviceHandler->setVertexBuffer(models.top()->getMesh()->subMeshes[m]->buffer, sizeof(SuperVertex));
								this->m_deviceHandler->setInputLayout(this->m_deferredSampler->getInputLayout());
								m_deferredSampler->renderShadowMap->GetPassByIndex(0)->Apply(0);
							}

							this->m_deviceHandler->getDevice()->Draw(models.top()->getMesh()->subMeshes[m]->numVerts, 0);
						}
					}

					models.pop();
				}
		
				resources[i * 6 + j] = pointLights[i]->getResource(j);
				wvps[i * 6 + j] = pointLights[i]->getMatrix(j);
				counter++;
			}
		}
	}

	if(counter > 0)
	{
		if(counter * 6 < 100)
		{
			m_deferredRendering->setPointLightWvps(wvps, counter * 6);
			m_deferredRendering->setPointLightShadowMaps(resources, counter * 6);
		}
		else
		{
			m_deferredRendering->setPointLightWvps(wvps, 100);
			m_deferredRendering->setPointLightShadowMaps(resources, 100);
		}
	}

	delete []wvps;
	delete []resources;

	resources = new ID3D10ShaderResourceView*[this->m_spotLights.size()];
	wvps = new D3DXMATRIX[this->m_spotLights.size()];

	for(int i = 0; i < m_spotLights.size(); i++)
	{
		m_deferredSampler->setLightWvp(m_spotLights[i]->getWvp());
		m_spotLights[i]->clearShadowMap(m_deviceHandler->getDevice());
		m_spotLights[i]->setShadowMapAsRenderTarget(m_deviceHandler->getDevice());

		stack<Model*> models = this->m_quadTree->getModels(_focalPoint);
		while(!models.empty())
		{
			if(models.top()->getAlpha() == 1.0f)
			{
				this->m_deferredSampler->setModelMatrix(models.top()->getModelMatrix());

				for(int m = 0; m < models.top()->getMesh()->subMeshes.size(); m++)
				{
					if(models.top()->getMesh()->isAnimated)
					{
						this->m_deferredSampler->setBoneTexture(models.top()->getAnimation()->getResource());
						this->m_deviceHandler->setVertexBuffer(models.top()->getMesh()->subMeshes[m]->buffer, sizeof(AnimationVertex));
						this->m_deviceHandler->setInputLayout(this->m_deferredSampler->getInputAnimationLayout());
						m_deferredSampler->renderShadowMap->GetPassByIndex(0)->Apply(0);
					}
					else
					{
						this->m_deviceHandler->setVertexBuffer(models.top()->getMesh()->subMeshes[m]->buffer, sizeof(SuperVertex));
						this->m_deviceHandler->setInputLayout(this->m_deferredSampler->getInputLayout());
						m_deferredSampler->renderShadowMap->GetPassByIndex(0)->Apply(0);
					}

					this->m_deviceHandler->getDevice()->Draw(models.top()->getMesh()->subMeshes[m]->numVerts, 0);
				}
			}

			models.pop();
		}
		
		resources[i] = m_spotLights[i]->getResource();
		wvps[i] = m_spotLights[i]->getWvp();
	}

	m_deferredRendering->setSpotLightWvps(wvps, this->m_spotLights.size());
	m_deferredRendering->setSpotLightShadowMaps(resources, this->m_spotLights.size());
	
	delete []wvps;
	delete []resources;
}

void World::update(float dt)
{
	//SpriteSheets
	for(int i = 0; i < this->m_sprites.size(); i++)
	{
		this->m_sprites[i]->update(dt);
	}

	for(int i = 0; i < m_models.size(); i++)
		m_models[i]->Update(dt);

	//stack<Model*> models = this->m_quadTree->pullAllModels();
	//while(!models.empty())
	//{
	//	this->m_quadTree->addModel(models.top());
	//	models.pop();
	//}
}

bool World::addModel(Model *_model)
{
	bool success;
	if(_model->isStatic())
		success = this->m_quadTree->addModel(_model);
	else
	{
		m_models.push_back(_model);
		success = true;
	}
	return success;
}

bool World::removeModel(Model *_model)
{
	bool success = false;

	if(_model->isStatic())
		success = this->m_quadTree->removeModel(_model);
	else
	{
		for(int i = 0; i < m_models.size(); i++)
		{
			if(m_models[i] == _model)
			{
				delete m_models[i];
				m_models.erase(m_models.begin()+i);
				success = true;
				i = m_models.size();
			}
		}
	}

	return success;
}

void World::addSprite(SpriteBase *sprite)
{
    bool found = false;

    for(int i = 0; i < this->m_sprites.size() && found == false; i++)
    {
            if(this->m_sprites[i]->getLayer() > sprite->getLayer())
            {
                    this->m_sprites.insert(this->m_sprites.begin() + i, sprite);
                    found = true;
            }
    }

    if(found == false)
    {
		this->m_sprites.push_back(sprite);
    }
}

bool World::removeSprite(SpriteBase *sprite)
{
	bool found = false;

	for(int i = 0; i < this->m_sprites.size() && !found; i++)
	{
		if(this->m_sprites[i] == sprite)
		{
			delete this->m_sprites[i];
			this->m_sprites.erase(this->m_sprites.begin()+i);
			found = true;
		}
	}

	return found;
}

void World::addText(Text* _text)
{
	this->m_texts.push_back(_text);
}

bool World::removeText(Text* _text)
{
	bool found = false;

	for(int i = 0; i < this->m_texts.size() && !found; i++)
	{
		if(this->m_texts[i] == _text)
		{
			delete this->m_texts[i];
			this->m_texts.erase(this->m_texts.begin()+i);
			found = true;
		}
	}

	return found;
}

void World::addMyText(MyText* _text)
{
	this->m_myTexts.push_back(_text);
}

bool World::removeMyText(MyText* _text)
{
	bool found = false;

	for(int i = 0; i < this->m_myTexts.size() && !found; i++)
	{
		if(this->m_myTexts[i] == _text)
		{
			delete this->m_myTexts[i];
			this->m_myTexts.erase(this->m_myTexts.begin()+i);
			found = true;
		}
	}

	return found;
}

bool World::addPointLight(PointLight* _pointLight)
{
	return this->m_quadTree->addLight(_pointLight);
}

bool World::removePointLight(PointLight* _pointLight)
{
	return this->m_quadTree->removeLight(_pointLight);
}

void World::addDirectionalLight(DirectionalLight* _directionalLight)
{
	this->m_directionalLights.push_back(_directionalLight);
}

bool World::removeDirectionalLight(DirectionalLight* _directionalLight)
{
	bool found = false;

	for(int i = 0; i < this->m_directionalLights.size() && !found; i++)
	{
		if(this->m_directionalLights[i] == _directionalLight)
		{
			delete this->m_directionalLights[i];
			this->m_directionalLights.erase(this->m_directionalLights.begin()+i);
			found = true;
		}
	}

	return found;
}

void World::addSpotLight(SpotLight* _spotLight)
{
	this->m_spotLights.push_back(_spotLight);
}

bool World::removeSpotLight(SpotLight* _spotLight)
{
	bool found = false;

	for(int i = 0; i < this->m_spotLights.size() && !found; i++)
	{
		if(this->m_spotLights[i] == _spotLight)
		{
			delete this->m_spotLights[i];
			this->m_spotLights.erase(this->m_spotLights.begin()+i);
			found = true;
		}
	}

	return found;
}

Camera *World::getCamera()
{
	return this->m_camera;
}

void World::initQuadTree(FLOAT2 _extents)
{
	if(m_quadTree)
		delete m_quadTree;
	this->m_quadTree = new QuadTree(3, D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(_extents.x, _extents.y));
}