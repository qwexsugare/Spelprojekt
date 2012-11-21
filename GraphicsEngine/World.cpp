#include "World.h"

World::World()
{

}

World::World(DeviceHandler* _deviceHandler)
{
	this->m_deviceHandler = _deviceHandler;
	this->m_models = vector<Model*>();
	this->m_camera = new Camera(this->m_deviceHandler->getScreenSize().x, this->m_deviceHandler->getScreenSize().y);
	this->m_forwardRendering = new ForwardRenderingEffectFile(this->m_deviceHandler->getDevice());
}

World::~World()
{
	delete this->m_forwardRendering;
	delete this->m_camera;
}

void World::render()
{
	//Init render stuff
	this->m_camera->updateViewMatrix();

	// Set variables
	this->m_forwardRendering->setViewMatrix(this->m_camera->getViewMatrix());
	this->m_forwardRendering->setProjectionMatrix(this->m_camera->getProjectionMatrix());

	static float ClearColor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };

	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	
	this->m_deviceHandler->setInputLayout(this->m_vertexLayout);

	//clear render target
	this->m_deviceHandler->getDevice()->ClearRenderTargetView( this->m_deviceHandler->getForwardRenderTarget(), ClearColor );
	this->m_deviceHandler->getDevice()->ClearDepthStencilView( this->m_deviceHandler->getForwardDepthStencil(), D3D10_CLEAR_DEPTH, 1.0f, 0 );
	this->m_deviceHandler->getDevice()->OMSetRenderTargets(1, this->m_deviceHandler->getForwardRenderTarget(), this->m_deviceHandler->getForwardDepthStencil());

	//Render all models
	for(int i = 0; i < this->m_models.size(); i++)
	{
		this->m_deviceHandler->getDevice()->IASetVertexBuffers(0, 1, &this->m_models[i]->getMesh()->buffer, &stride, &offset);

		D3D10_TECHNIQUE_DESC techDesc;
		this->m_forwardRendering->getTechniqueRenderModelForward()->GetDesc( &techDesc );

		for( UINT p = 0; p < techDesc.Passes; p++ )
		{
			this->m_forwardRendering->getTechniqueRenderModelForward()->GetPassByIndex( p )->Apply(0);
			this->m_deviceHandler->getDevice()->Draw(this->m_models[i]->getMesh()->nrOfVertices, 0);
		}
	}

	//Finish render
	this->m_deviceHandler->present();
}

void World::addModel(Model *_model)
{
	this->m_models.push_back(_model);
}

bool World::removeModel(Model *_model)
{
	// we do not know HOW to write this code
	return true;
}

Camera *World::getCamera()
{
	return this->m_camera;
}