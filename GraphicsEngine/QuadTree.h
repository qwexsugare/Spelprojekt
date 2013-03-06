#pragma once

#include "QuadTreeNode.h"

class QuadTree
{
private:
	QuadTreeNode* m_parent;
public:
	QuadTree();
	QuadTree(int _levels, D3DXVECTOR2 _min, D3DXVECTOR2 _max, D3DXVECTOR2 _cameraOffset);
	~QuadTree();
	
	bool addParticleEngine(ParticleEngine* _particleEngine);
	bool addModel(Model* _model);
	bool addLight(PointLight* _light);
	bool addRoad(Road *_road);
	vector<PointLight*> getAllLights()const;
	stack<Model*> getAllModels()const;
	stack<Road*> getAllRoads()const;
	stack<Model*> getModels(D3DXVECTOR2 _focalPoint)const;
	stack<ParticleEngine*> getParticleEngines(D3DXVECTOR2 _focalPoint)const;
	vector<PointLight*> getPointLights(D3DXVECTOR2 _focalPoint)const;
	stack<Road*> getRoads(D3DXVECTOR2 _focalPoint)const;
	stack<Model*> pullAllModels();
	bool removeModel(Model* _model);
	bool removeLight(PointLight* _light);
	bool removeParticleEngine(ParticleEngine* _pe);
	bool removeRoad(Road* _road);
};