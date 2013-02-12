#include "QuadTree.h"

QuadTree::QuadTree()
{
	this->m_parent = NULL;
}

QuadTree::QuadTree(int _levels, D3DXVECTOR2 _min, D3DXVECTOR2 _max)
{
	this->m_parent = new QuadTreeNode(_levels, _min, _max);
}

QuadTree::~QuadTree()
{
	if(this->m_parent)
		delete this->m_parent;
}

bool QuadTree::addParticleEngine(ParticleEngine* _particleEngine)
{
	bool success;
	m_parent->addParticleEngine(success, _particleEngine);
	return success;
}

bool QuadTree::addModel(Model* _model)
{
	bool success;
	this->m_parent->addModel(success, _model);
	return success;
}

bool QuadTree::addLight(PointLight* _light)
{
	bool success;
	this->m_parent->addLight(success, _light);
	return success;
}

bool QuadTree::addRoad(Road *_road)
{
	bool success;
	this->m_parent->addRoad(success, _road);
	return success;
}

stack<Model*> QuadTree::getAllModels()const
{
	stack<Model*> models;

	this->m_parent->getAllModels(models);

	return models;
}

stack<Model*> QuadTree::getModels(D3DXVECTOR3 _cameraPos)const
{
	stack<Model*> models;

	this->m_parent->getModels(models, _cameraPos);

	return models;
}

stack<ParticleEngine*> QuadTree::getParticleEngines(D3DXVECTOR3 _cameraPos)const
{
	stack<ParticleEngine*> ret;

	m_parent->getParticleEngines(ret, _cameraPos);

	return ret;
}

vector<PointLight*> QuadTree::getPointLights(D3DXVECTOR3 _cameraPos)const
{
	vector<PointLight*> lights;

	this->m_parent->getLights(lights, _cameraPos);

	return lights;
}

stack<Road*> QuadTree::getRoads(D3DXVECTOR3 _cameraPos)const
{
	stack<Road*> roads;
	this->m_parent->getRoads(roads, _cameraPos);
	return roads;
}

stack<Model*> QuadTree::pullAllModels()
{
	stack<Model*> models;

	this->m_parent->pullAllModels(models);

	return models;
}

bool QuadTree::removeModel(Model* _model)
{
	return this->m_parent->removeModel(_model);
}

bool QuadTree::removeLight(PointLight* _light)
{
	return this->m_parent->removeLight(_light);
}

bool QuadTree::removeRoad(Road* _road)
{
	return this->m_parent->removeRoad(_road);
}