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
	g_pd3dDevice->IASetInputLayout( g_pVertexLayout );
	g_pd3dDevice->IASetPrimitiveTopology( D3D10_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP );
	

	//clear render target
	g_pd3dDevice->ClearRenderTargetView( g_pRenderTargetView, ClearColor );

	//clear depth info
	g_pd3dDevice->ClearDepthStencilView( g_pDepthStencilView, D3D10_CLEAR_DEPTH, 1.0f, 0 );

	for(int i = 0; i < this->m_models.size(); i++)
	{
		g_pd3dDevice->IASetVertexBuffers( 0, 1, &g_pVB, &stride, &offset );
	}



	//Render all models


	//Finish render
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