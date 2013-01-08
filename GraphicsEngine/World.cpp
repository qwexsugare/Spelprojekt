#include "World.h"

World::World()
{

}

World::World(DeviceHandler* _deviceHandler, HWND _hWnd)
{
	this->m_deviceHandler = _deviceHandler;
	this->m_sprites = vector<SpriteBase*>();
	this->m_texts = vector<Text*>();
	RECT rc;
	GetWindowRect(_hWnd, &rc);
	INT2 lolers = INT2(rc.right-rc.left, rc.bottom-rc.top);
	this->m_camera = new Camera(this->m_deviceHandler->getScreenSize().x, this->m_deviceHandler->getScreenSize().y, lolers);
	this->m_quadTree = new QuadTree(2, D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(1000.0f, 1000.0f));

	this->m_forwardRendering = new ForwardRenderingEffectFile(this->m_deviceHandler->getDevice());
	this->m_forwardRenderTarget = new RenderTarget(this->m_deviceHandler->getDevice(), this->m_deviceHandler->getBackBuffer());
	this->m_forwardDepthStencil = new DepthStencil(this->m_deviceHandler->getDevice(), this->m_deviceHandler->getScreenSize());

	this->m_deferredSampler = new DeferredSamplerEffectFile(this->m_deviceHandler->getDevice());
	this->m_deferredSampler->setProjectionMatrix(this->m_camera->getProjectionMatrix());
	this->m_deferredRendering = new DeferredRenderingEffectFile(this->m_deviceHandler->getDevice());

	this->m_positionBuffer = new RenderTarget(this->m_deviceHandler->getDevice(), this->m_deviceHandler->getScreenSize());
	this->m_normalBuffer = new RenderTarget(this->m_deviceHandler->getDevice(), this->m_deviceHandler->getScreenSize());
	this->m_diffuseBuffer = new RenderTarget(this->m_deviceHandler->getDevice(), this->m_deviceHandler->getScreenSize());

	this->m_positionBufferTransparant = new RenderTarget(this->m_deviceHandler->getDevice(), this->m_deviceHandler->getScreenSize());
	this->m_normalBufferTransparant = new RenderTarget(this->m_deviceHandler->getDevice(), this->m_deviceHandler->getScreenSize());
	this->m_diffuseBufferTransparant = new RenderTarget(this->m_deviceHandler->getDevice(), this->m_deviceHandler->getScreenSize());

	this->m_deferredPlane = new FullScreenPlane(this->m_deviceHandler->getDevice(), NULL);

	this->m_spriteRendering = new SpriteEffectFile(this->m_deviceHandler->getDevice());
}

World::~World()
{
	for(int i = 0; i < m_terrains.size(); i++)
		delete m_terrains[i];

	for(int i = 0; i < this->m_sprites.size(); i++)
	{
		delete this->m_sprites[i];
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
	this->m_forwardDepthStencil->clear(this->m_deviceHandler->getDevice());

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
		this->m_deviceHandler->setVertexBuffer(m_terrains[i]->getVertexBuffer());

		this->m_deferredSampler->setModelMatrix(m_terrains[i]->getModelMatrix());
		this->m_deferredSampler->setTerrainTextures(m_terrains[i]->getTextures(), m_terrains[i]->getNrOfTextures());
		this->m_deferredSampler->setTerrainBlendMaps(m_terrains[i]->getBlendMaps(), m_terrains[i]->getNrOfBlendMaps());
			
		this->m_deferredSampler->getRenderTerrainTechique()->GetPassByIndex( 0 )->Apply(0);
		this->m_deviceHandler->getDevice()->Draw(4, 0);
	}

	//Render all models
	/*D3DXMATRIX mat;
	D3DXMatrixMultiply(&mat, &this->m_camera->getViewMatrix(), &this->m_camera->getProjectionMatrix());
	XMMATRIX projectionMatrixInCyborgForm = XMMATRIX(
		mat._11, mat._12, mat._13, mat._14,
		mat._21, mat._22, mat._23, mat._24,
		mat._31, mat._32, mat._33, mat._34,
		mat._41, mat._42, mat._43, mat._44);
	BoundingFrustum bf = BoundingFrustum(projectionMatrixInCyborgForm);*/
	this->m_deviceHandler->getDevice()->IASetPrimitiveTopology( D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST );
	stack<Model*> models = this->m_quadTree->getModels(this->m_camera->getPos());
	stack<Model*> transparantModels;
	while(!models.empty())
	{
		/*XMFLOAT3 origin(this->m_camera->getPos().x, this->m_camera->getPos().y, this->m_camera->getPos().z);
		XMFLOAT4 orientation(0.0f, 0.0f, 0.0f, 1.0f);
		float rightSlope = 0.5f;
		float leftSlope = -0.5f;
		float topSlope = 0.5f;
		float bottomSlope = -0.5f;
		float near_ = 0.0f;
		float far_ = 1500000.0f;
		BoundingFrustum bf = BoundingFrustum(origin, orientation, rightSlope, leftSlope, topSlope, bottomSlope, near_, far_);*/
		//if(bf.Contains(*models.top()->getObb()) || bf.Intersects(*models.top()->getObb()))

		if(models.top()->getAlpha() < 1.0f)
		{
			transparantModels.push(models.top());
		}
		else
		{
			this->m_deviceHandler->setVertexBuffer(models.top()->getMesh()->buffer);

			this->m_deferredSampler->setModelMatrix(models.top()->getModelMatrix());
			this->m_deferredSampler->setTexture(models.top()->getMesh()->m_texture);
			this->m_deferredSampler->setModelAlpha(models.top()->getAlpha());
			
			// ULTRA CHARGED OPTIMIZATION COMMENTS AWAY SIMONS CODE
			/*D3D10_TECHNIQUE_DESC techDesc;
			this->m_deferredSampler->getTechnique()->GetDesc( &techDesc );

			for( UINT p = 0; p < techDesc.Passes; p++ )
			{*/
			this->m_deferredSampler->getTechnique()->GetPassByIndex( 0 )->Apply(0);
			this->m_deviceHandler->getDevice()->Draw(models.top()->getMesh()->nrOfVertices, 0);
			//}
		}
			
		models.pop();
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

	while(!transparantModels.empty())
	{
		this->m_deviceHandler->setVertexBuffer(transparantModels.top()->getMesh()->buffer);

		this->m_deferredSampler->setModelMatrix(transparantModels.top()->getModelMatrix());
		this->m_deferredSampler->setTexture(transparantModels.top()->getMesh()->m_texture);
		this->m_deferredSampler->setModelAlpha(transparantModels.top()->getAlpha());

		D3D10_TECHNIQUE_DESC techDesc;
		this->m_deferredSampler->getTechnique()->GetDesc( &techDesc );

		for( UINT p = 0; p < techDesc.Passes; p++ )
		{
			this->m_deferredSampler->getTechnique()->GetPassByIndex( p )->Apply(0);
			this->m_deviceHandler->getDevice()->Draw(transparantModels.top()->getMesh()->nrOfVertices, 0);
		}
		
		transparantModels.pop();
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

	this->m_deviceHandler->setVertexBuffer(this->m_deferredPlane->getMesh()->buffer);

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

	//Sprites
	for(int i = 0; i < this->m_sprites.size(); i++)
	{
		this->m_deviceHandler->setVertexBuffer(m_sprites[i]->getBuffer());

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

	// Render texts
	for(int i = 0; i < this->m_myTexts.size(); i++)
	{
		this->m_deviceHandler->setVertexBuffer(m_myTexts[i]->getBuffer());

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
	
	// Render texts
	for(int i = 0; i < this->m_texts.size(); i++)
	{
		this->m_texts[i]->render();
	}

	//Finish render
	this->m_deviceHandler->present();
}

void World::update(float dt)
{
	//SpriteSheets
	for(int i = 0; i < this->m_sprites.size(); i++)
	{
		this->m_sprites[i]->update(dt);
	}
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

Camera *World::getCamera()
{
	return this->m_camera;
}