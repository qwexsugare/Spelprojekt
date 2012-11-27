#include "World.h"

World::World()
{

}

World::World(DeviceHandler* _deviceHandler)
{
	this->m_deviceHandler = _deviceHandler;
	this->m_models = vector<Model*>();
	this->m_sprites = vector<Sprite*>();
	this->m_camera = new Camera(this->m_deviceHandler->getScreenSize().x, this->m_deviceHandler->getScreenSize().y);

	this->m_forwardRendering = new ForwardRenderingEffectFile(this->m_deviceHandler->getDevice());
	this->m_forwardRenderTarget = new RenderTarget(this->m_deviceHandler->getDevice(), this->m_deviceHandler->getBackBuffer());
	this->m_forwardDepthStencil = new DepthStencil(this->m_deviceHandler->getDevice(), this->m_deviceHandler->getScreenSize());

	this->m_deferredSampler = new DeferredSamplerEffectFile(this->m_deviceHandler->getDevice());
	this->m_deferredRendering = new DeferredRenderingEffectFile(this->m_deviceHandler->getDevice());
	this->m_positionBuffer = new RenderTarget(this->m_deviceHandler->getDevice(), this->m_deviceHandler->getScreenSize());
	this->m_normalBuffer = new RenderTarget(this->m_deviceHandler->getDevice(), this->m_deviceHandler->getScreenSize());
	this->m_diffuseBuffer = new RenderTarget(this->m_deviceHandler->getDevice(), this->m_deviceHandler->getScreenSize());
	this->m_deferredPlane = new FullScreenPlane(this->m_deviceHandler->getDevice(), NULL);
	
	// Create a font
	D3DX10CreateFontA(this->m_deviceHandler->getDevice(), 30, 0, FW_BOLD, 0, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, TEXT("Arial"), &this->m_fpsFont);
}

World::~World()
{
	for(int i = 0; i < this->m_models.size(); i++)
	{
		delete this->m_models[i];
	}

	for(int i = 0; i < this->m_sprites.size(); i++)
	{
		delete this->m_sprites[i];
	}

	delete this->m_forwardRendering;
	delete this->m_forwardRenderTarget;
	delete this->m_forwardDepthStencil;

	delete this->m_deferredPlane;
	delete this->m_deferredSampler;
	delete this->m_deferredRendering;
	delete this->m_positionBuffer;
	delete this->m_normalBuffer;
	delete this->m_diffuseBuffer;

	delete this->m_camera;
}

void World::render()
{
	//Init render stuff
	this->m_camera->updateViewMatrix();

	this->m_deferredSampler->setViewMatrix(this->m_camera->getViewMatrix());
	this->m_deferredSampler->setProjectionMatrix(this->m_camera->getProjectionMatrix());

	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	
	this->m_deviceHandler->setInputLayout(this->m_deferredSampler->getInputLayout());
 	this->m_forwardDepthStencil->clear(this->m_deviceHandler->getDevice());
	
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
	this->m_deviceHandler->getDevice()->IASetPrimitiveTopology( D3D10_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP );
	
	//Render all models
	for(int i = 0; i < this->m_models.size(); i++)
	{
		this->m_deviceHandler->getDevice()->IASetVertexBuffers(0, 1, &this->m_models[i]->getMesh()->buffer, &stride, &offset);

		this->m_deferredSampler->setModelMatrix(this->m_models[i]->getModelMatrix());
		this->m_deferredSampler->setTexture(this->m_models[i]->getMesh()->m_texture);
		this->m_deferredSampler->setModelAlpha(this->m_models[i]->getAlpha());

		D3D10_TECHNIQUE_DESC techDesc;
		this->m_deferredSampler->getTechnique()->GetDesc( &techDesc );

		for( UINT p = 0; p < techDesc.Passes; p++ )
		{
			this->m_deferredSampler->getTechnique()->GetPassByIndex( p )->Apply(0);
			this->m_deviceHandler->getDevice()->Draw(this->m_models[i]->getMesh()->nrOfVertices, 0);
		}
	}

	//Deferred
	this->m_forwardRendering->setViewMatrix(this->m_camera->getViewMatrix());
	this->m_forwardRendering->setProjectionMatrix(this->m_camera->getProjectionMatrix());

	this->m_forwardRenderTarget->clear(this->m_deviceHandler->getDevice());
	this->m_forwardDepthStencil->clear(this->m_deviceHandler->getDevice());

	this->m_deviceHandler->getDevice()->RSSetViewports( 1, &this->m_deviceHandler->getViewport());
	this->m_deviceHandler->getDevice()->OMSetRenderTargets(1, this->m_forwardRenderTarget->getRenderTargetView(), this->m_forwardDepthStencil->getDepthStencilView());
	this->m_deviceHandler->getDevice()->IASetPrimitiveTopology( D3D10_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP );

	this->m_deviceHandler->setInputLayout(this->m_deferredRendering->getVertexLayout());
	this->m_deferredRendering->setPositionsTexture(this->m_positionBuffer->getShaderResource());
	this->m_deferredRendering->setNormalsTexture(this->m_normalBuffer->getShaderResource());
	this->m_deferredRendering->setDiffuseTexture(this->m_diffuseBuffer->getShaderResource());

	this->m_deviceHandler->getDevice()->IASetVertexBuffers(0, 1, &this->m_deferredPlane->getMesh()->buffer, &stride, &offset);

	D3D10_TECHNIQUE_DESC techDesc;
	this->m_deferredRendering->getTechnique()->GetDesc( &techDesc );

	for( UINT p = 0; p < techDesc.Passes; p++ )
	{
		this->m_deferredRendering->getTechnique()->GetPassByIndex( p )->Apply(0);
		this->m_deviceHandler->getDevice()->Draw(this->m_deferredPlane->getMesh()->nrOfVertices, 0);
	}

	string str  = "KHJHWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWSK";
	RECT rc;
	rc.bottom = 100;
	rc.top = 200;
	rc.left = 400;
	rc.right = 500;
	this->m_fpsFont->DrawTextA(NULL, str.c_str(), -1, &rc, DT_NOCLIP, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	//Finish render
	this->m_deviceHandler->present();
}

void World::addModel(Model *_model)
{
	this->m_models.push_back(_model);
}

bool World::removeModel(Model *_model)
{
	bool found = false;

	for(int i = 0; i < this->m_models.size() && !found; i++)
	{
		if(this->m_models[i] == _model)
		{
			delete this->m_models[i];
			this->m_models.erase(this->m_models.begin()+i);
			found = true;
		}
	}

	return found;
}

void World::addSprite(Sprite *sprite)
{
	this->m_sprites.push_back(sprite);	
}

bool World::removeSprite(Sprite *sprite)
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

Camera *World::getCamera()
{
	return this->m_camera;
}