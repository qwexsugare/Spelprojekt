#include "World.h"

World::World()
{

}

World::World(DeviceHandler* _deviceHandler, HWND _hWnd, bool _windowed)
{
	this->m_deviceHandler = _deviceHandler;
	this->m_sprites = vector<SpriteBase*>();
	this->m_texts = vector<Text*>();
	this->m_quadTree = new QuadTree(2, D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(100.0f, 100.0f));

	RECT rc;
	GetWindowRect(_hWnd, &rc);
	INT2 actualScreenSize = INT2(rc.right-rc.left, rc.bottom-rc.top);
	this->m_camera = new Camera(this->m_deviceHandler->getScreenSize(), actualScreenSize);

	this->m_forwardRendering = new ForwardRenderingEffectFile(this->m_deviceHandler->getDevice());
	this->m_forwardRenderTarget = new RenderTarget(this->m_deviceHandler->getDevice(), this->m_deviceHandler->getBackBuffer());
	this->m_forwardDepthStencil = new DepthStencil(this->m_deviceHandler->getDevice(), this->m_deviceHandler->getScreenSize(), true);

	this->m_deferredSampler = new DeferredSamplerEffectFile(this->m_deviceHandler->getDevice());
	this->m_deferredSampler->setProjectionMatrix(this->m_camera->getProjectionMatrix());
	this->m_deferredRendering = new DeferredRenderingEffectFile(this->m_deviceHandler->getDevice());
	m_forwardRendering->setProjectionMatrix(m_camera->getProjectionMatrix());

	this->m_positionBuffer = new RenderTarget(this->m_deviceHandler->getDevice(), this->m_deviceHandler->getScreenSize());
	this->m_normalBuffer = new RenderTarget(this->m_deviceHandler->getDevice(), this->m_deviceHandler->getScreenSize());
	this->m_diffuseBuffer = new RenderTarget(this->m_deviceHandler->getDevice(), this->m_deviceHandler->getScreenSize());

	this->m_positionBufferTransparant = new RenderTarget(this->m_deviceHandler->getDevice(), this->m_deviceHandler->getScreenSize());
	this->m_normalBufferTransparant = new RenderTarget(this->m_deviceHandler->getDevice(), this->m_deviceHandler->getScreenSize());
	this->m_diffuseBufferTransparant = new RenderTarget(this->m_deviceHandler->getDevice(), this->m_deviceHandler->getScreenSize());
	
	this->m_deferredPlane = new FullScreenPlane(this->m_deviceHandler->getDevice(), NULL);
	this->m_spriteRendering = new SpriteEffectFile(this->m_deviceHandler->getDevice());
	
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
	for(int i = 0; i < m_roads.size(); i++)
		delete m_roads[i];

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
	delete this->m_spriteRendering;

	delete this->m_deferredPlane;
	delete this->m_deferredSampler;
	delete this->m_deferredRendering;

	delete this->m_positionBuffer;
	delete this->m_normalBuffer;
	delete this->m_diffuseBuffer;

	delete this->m_positionBufferTransparant;
	delete this->m_normalBufferTransparant;
	delete this->m_diffuseBufferTransparant;

	delete this->m_camera;
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
	//Init render stuff
	this->m_camera->updateViewMatrix();
	this->m_deferredSampler->setViewMatrix(this->m_camera->getViewMatrix());
	this->m_deviceHandler->setInputLayout(this->m_deferredSampler->getInputLayout());
	
	//clear render target
	this->m_positionBuffer->clear(this->m_deviceHandler->getDevice());
	this->m_normalBuffer->clear(this->m_deviceHandler->getDevice());
	this->m_diffuseBuffer->clear(this->m_deviceHandler->getDevice());
	m_forwardDepthStencil->clear(this->m_deviceHandler->getDevice());
	m_forwardRenderTarget->clear(m_deviceHandler->getDevice());

	this->renderShadowMap();

	ID3D10RenderTargetView *renderTargets[3];
	renderTargets[0] = *this->m_positionBuffer->getRenderTargetView();
	renderTargets[1] = *this->m_normalBuffer->getRenderTargetView();
	renderTargets[2] = *this->m_diffuseBuffer->getRenderTargetView();

	this->m_deviceHandler->getDevice()->RSSetViewports( 1, &this->m_deviceHandler->getViewport());
	this->m_deviceHandler->getDevice()->OMSetRenderTargets(3, renderTargets , this->m_forwardDepthStencil->getDepthStencilView());
	
	// Render terrains
	this->m_deviceHandler->getDevice()->IASetPrimitiveTopology( D3D10_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP );
	for(int i = 0; i < this->m_terrains.size(); i++)
	{
		this->m_deviceHandler->setVertexBuffer(m_terrains[i]->getVertexBuffer(), sizeof(Vertex));

		this->m_deferredSampler->setModelMatrix(m_terrains[i]->getModelMatrix());
		this->m_deferredSampler->setTerrainTextures(m_terrains[i]->getTextures(), m_terrains[i]->getNrOfTextures());
		this->m_deferredSampler->setTerrainBlendMaps(m_terrains[i]->getBlendMaps(), m_terrains[i]->getNrOfBlendMaps());
		this->m_deferredSampler->setNormalMaps(m_terrains[i]->getNormalMap());
			
		this->m_deferredSampler->getRenderTerrainTechnique()->GetPassByIndex(0)->Apply(0);
		this->m_deviceHandler->getDevice()->Draw(m_terrains[i]->getNrOfVertices(), 0);
	}

	// Render roads yo dawg y u be messin' about
	stack<Road*> roads = this->m_quadTree->getRoads(this->m_camera->getPos());
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

	//Render all models
	this->m_deviceHandler->getDevice()->IASetPrimitiveTopology( D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST );
	stack<Model*> models = this->m_quadTree->getModels(this->m_camera->getPos());
	vector<Model*> transparentModels;
	vector<Model*> gubbs;
	while(!models.empty())
	{
		if(models.top()->getAlpha() < 1.0f)
		{
			if(transparentModels.size() == 0)
			{
				transparentModels.push_back(models.top());
			}
			else
			{
				if(models.top()->getPosition().y <= transparentModels[0]->getPosition().y)
					transparentModels.insert(transparentModels.begin(), models.top());
				else
				{
					bool inserted = false;
					for(int i = 1; i < transparentModels.size()-1 && !inserted; i++)
					{
						if(models.top()->getPosition().y > transparentModels[i]->getPosition().y && models.top()->getPosition().y <= transparentModels[i+1]->getPosition().y)
						{
							transparentModels.insert(transparentModels.begin()+i, models.top());
							inserted = true;
						}
					}
					if(!inserted)
					{
						transparentModels.push_back(models.top());
					}
				}
			}
		}
		else if(models.top()->isHouse())
		{
			this->m_deferredSampler->setModelMatrix(models.top()->getModelMatrix());
			this->m_deferredSampler->setModelAlpha(models.top()->getAlpha());

			for(int m = 0; m < models.top()->getMesh()->subMeshes.size(); m++)
			{
				this->m_deferredSampler->setTexture(models.top()->getMesh()->subMeshes[m]->textures[models.top()->getTextureIndex()]);
				this->m_deferredSampler->setNormalMap(models.top()->getMesh()->subMeshes[m]->textures["normalCamera"]);

				if(models.top()->getMesh()->isAnimated)
				{
					/*this->m_deferredSampler->setBoneTexture(models.top()->getAnimation()->getResource());
					this->m_deviceHandler->setVertexBuffer(models.top()->getMesh()->subMeshes[m]->buffer, sizeof(AnimationVertex));
					this->m_deviceHandler->setInputLayout(this->m_deferredSampler->getInputAnimationLayout());
					this->m_deferredSampler->getAnimationTechnique()->GetPassByIndex( 0 )->Apply(0);*/
				}
				else
				{
					this->m_deviceHandler->setVertexBuffer(models.top()->getMesh()->subMeshes[m]->buffer, sizeof(SuperVertex));
					this->m_deviceHandler->setInputLayout(this->m_deferredSampler->getSuperInputLayout());

					D3D10_TECHNIQUE_DESC desc;
					m_deferredSampler->getSuperTechnique()->GetDesc(&desc);

					this->m_deferredSampler->getSuperTechnique()->GetPassByIndex(1)->Apply(0);
					this->m_deviceHandler->getDevice()->Draw(models.top()->getMesh()->subMeshes[m]->numVerts, 0);

					//for(int i = 0; i < desc.Passes; i++)
					//{
					//	this->m_deferredSampler->getSuperTechnique()->GetPassByIndex( i )->Apply(0);
					//	this->m_deviceHandler->getDevice()->Draw(models.top()->getMesh()->subMeshes[m]->numVerts, 0);
					//}
				}
			}
		}
		else
		{
			gubbs.push_back(models.top());
		}

		models.pop();
	}

	for(int i = 0; i < gubbs.size(); i++)
	{
		this->m_deferredSampler->setModelMatrix(gubbs[i]->getModelMatrix());
		this->m_deferredSampler->setModelAlpha(gubbs[i]->getAlpha());

		for(int m = 0; m < gubbs[i]->getMesh()->subMeshes.size(); m++)
		{
			m_deferredSampler->setTexture(gubbs[i]->getMesh()->subMeshes[m]->textures[gubbs[i]->getTextureIndex()]);
			m_deferredSampler->setNormalMap(gubbs[i]->getMesh()->subMeshes[m]->textures["normalCamera"]);

			if(gubbs[i]->getMesh()->isAnimated)
			{
				/*this->m_forwardRendering->setBoneTexture(models.top()->getAnimation()->getResource());
				this->m_deviceHandler->setVertexBuffer(models.top()->getMesh()->subMeshes[m]->buffer, sizeof(AnimationVertex));
				this->m_deviceHandler->setInputLayout(this->m_deferredSampler->getInputAnimationLayout());
				this->m_deferredSampler->getAnimationTechnique()->GetPassByIndex( 0 )->Apply(0);*/
			}
			else
			{
				m_deviceHandler->setVertexBuffer(gubbs[i]->getMesh()->subMeshes[m]->buffer, sizeof(SuperVertex));
				m_deviceHandler->setInputLayout(m_deferredSampler->getSuperInputLayout());
				this->m_deviceHandler->getDevice()->OMSetRenderTargets(3, renderTargets , this->m_forwardDepthStencil->getDepthStencilView());
				this->m_deferredSampler->getSuperTechnique()->GetPassByIndex(0)->Apply(0);
				this->m_deviceHandler->getDevice()->Draw(gubbs[i]->getMesh()->subMeshes[m]->numVerts, 0);
			}
		}
	}

	//clear render target
	this->m_positionBufferTransparant->clear(this->m_deviceHandler->getDevice());
	this->m_normalBufferTransparant->clear(this->m_deviceHandler->getDevice());
	this->m_diffuseBufferTransparant->clear(this->m_deviceHandler->getDevice());

	renderTargets[0] = *this->m_positionBufferTransparant->getRenderTargetView();
	renderTargets[1] = *this->m_normalBufferTransparant->getRenderTargetView();
	renderTargets[2] = *this->m_diffuseBufferTransparant->getRenderTargetView();

	this->m_deviceHandler->getDevice()->OMSetRenderTargets(3, renderTargets , this->m_forwardDepthStencil->getDepthStencilView());
	this->m_deviceHandler->getDevice()->IASetPrimitiveTopology( D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST );

	for(int i = 0; i < transparentModels.size(); i++)
	{
		this->m_deferredSampler->setModelMatrix(transparentModels[i]->getModelMatrix());
		this->m_deferredSampler->setModelAlpha(transparentModels[i]->getAlpha());

		for(int m = 0; m < transparentModels[i]->getMesh()->subMeshes.size(); m++)
		{
			this->m_deferredSampler->setTexture(transparentModels[i]->getMesh()->subMeshes[m]->textures[transparentModels[i]->getTextureIndex()]);
			this->m_deferredSampler->setNormalMap(transparentModels[i]->getMesh()->subMeshes[m]->textures["normalCamera"]);

			if(transparentModels[i]->getMesh()->isAnimated)
			{
				this->m_deferredSampler->setBoneTexture(transparentModels[i]->getAnimation()->getResource());
				this->m_deviceHandler->setVertexBuffer(transparentModels[i]->getMesh()->subMeshes[m]->buffer, sizeof(AnimationVertex));
				this->m_deviceHandler->setInputLayout(this->m_deferredSampler->getInputAnimationLayout());
				this->m_deferredSampler->getAnimationTechnique()->GetPassByIndex( 0 )->Apply(0);
			}
			else
			{
				this->m_deviceHandler->setVertexBuffer(transparentModels[i]->getMesh()->subMeshes[m]->buffer, sizeof(SuperVertex));
				this->m_deviceHandler->setInputLayout(this->m_deferredSampler->getSuperInputLayout());
				this->m_deferredSampler->getSuperTechnique()->GetPassByIndex( 0 )->Apply(0);
			}

			this->m_deviceHandler->getDevice()->Draw(transparentModels[i]->getMesh()->subMeshes[m]->numVerts, 0);
		}
	}

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
	this->m_deferredRendering->setCameraPosition(this->m_camera->m_forward);
	this->m_deferredRendering->updateLights(this->m_quadTree->getPointLights(this->m_camera->getPos()), this->m_directionalLights, this->m_spotLights);

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

	for( UINT p = 0; p < techDesc.Passes; p++ )
	{
		this->m_deferredRendering->getTechnique()->GetPassByIndex( p )->Apply(0);
		this->m_deviceHandler->getDevice()->Draw(this->m_deferredPlane->getMesh()->nrOfVertices, 0);
	}

	m_deviceHandler->getDevice()->OMSetRenderTargets(1, m_forwardRenderTarget->getRenderTargetView(), m_forwardDepthStencil->getDepthStencilView());

	for(int i = 0; i < gubbs.size(); i++)
	{
		m_forwardRendering->setModelMatrix(gubbs[i]->getModelMatrix());

		for(int m = 0; m < gubbs[i]->getMesh()->subMeshes.size(); m++)
		{
			if(gubbs[i]->getMesh()->isAnimated)
			{
				/*this->m_forwardRendering->setBoneTexture(models.top()->getAnimation()->getResource());
				this->m_deviceHandler->setVertexBuffer(models.top()->getMesh()->subMeshes[m]->buffer, sizeof(AnimationVertex));
				this->m_deviceHandler->setInputLayout(this->m_deferredSampler->getInputAnimationLayout());
				this->m_deferredSampler->getAnimationTechnique()->GetPassByIndex( 0 )->Apply(0);*/
			}
			else
			{				
				m_deviceHandler->setVertexBuffer(gubbs[i]->getMesh()->subMeshes[m]->buffer, sizeof(SuperVertex));
				m_deviceHandler->setInputLayout(m_deferredSampler->getSuperInputLayout());				
				m_forwardRendering->m_forwardGubb->GetPassByIndex(0)->Apply(0);
				this->m_deviceHandler->getDevice()->Draw(gubbs[i]->getMesh()->subMeshes[m]->numVerts, 0);
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

void World::renderShadowMap()
{
	m_deviceHandler->getDevice()->RSSetViewports(1, &m_shadowMapViewport);

	vector<PointLight*> pointLights = this->m_quadTree->getPointLights(this->m_camera->getPos());
	ID3D10ShaderResourceView** resources = new ID3D10ShaderResourceView*[pointLights.size() * 6];
	D3DXMATRIX* wvps = new D3DXMATRIX[pointLights.size() * 6];
	
	m_deviceHandler->getDevice()->IASetPrimitiveTopology( D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST );

	for(int i = 0; i < pointLights.size(); i++)
	{
		pointLights[i]->clearShadowMap(m_deviceHandler->getDevice());

		for(int j = 0; j < 6; j++)
		{
			m_deferredSampler->setLightWvp(pointLights[i]->getMatrix(j));
			pointLights[i]->setShadowMapAsRenderTarget(m_deviceHandler->getDevice(), j);

			stack<Model*> models = this->m_quadTree->getModels(pointLights[i]->getPosition().toD3DXVector());
			while(!models.empty())
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
		}
	}

	m_deferredRendering->setPointLightWvps(wvps, pointLights.size() * 6);
	m_deferredRendering->setPointLightShadowMaps(resources, pointLights.size() * 6);

	delete []wvps;
	delete []resources;

	resources = new ID3D10ShaderResourceView*[this->m_spotLights.size()];
	wvps = new D3DXMATRIX[this->m_spotLights.size()];

	for(int i = 0; i < m_spotLights.size(); i++)
	{
		m_deferredSampler->setLightWvp(m_spotLights[i]->getWvp());
		m_spotLights[i]->clearShadowMap(m_deviceHandler->getDevice());
		m_spotLights[i]->setShadowMapAsRenderTarget(m_deviceHandler->getDevice());

		stack<Model*> models = this->m_quadTree->getModels(this->m_camera->getPos());
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

	stack<Model*> models = this->m_quadTree->getModels(m_camera->getPos());
	while(!models.empty())
	{
		models.top()->getAnimation()->Update(dt);
		models.pop();
	}

	//stack<Model*> models = this->m_quadTree->pullAllModels();
	//while(!models.empty())
	//{
	//	this->m_quadTree->addModel(models.top());
	//	models.pop();
	//}
}

bool World::addModel(Model *_model)
{
	return this->m_quadTree->addModel(_model);
}

bool World::removeModel(Model *_model)
{
	return this->m_quadTree->removeModel(_model);
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

void World::addPointLight(PointLight* _pointLight)
{
	//this->m_pointLights.push_back(_pointLight);
	this->m_quadTree->addLight(_pointLight);
}

bool World::removePointLight(PointLight* _pointLight)
{
	//bool found = false;

	//for(int i = 0; i < this->m_pointLights.size() && !found; i++)
	//{
	//	if(this->m_pointLights[i] == _pointLight)
	//	{
	//		delete this->m_pointLights[i];
	//		this->m_pointLights.erase(this->m_pointLights.begin()+i);
	//		found = true;
	//	}
	//}

	//return found;

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