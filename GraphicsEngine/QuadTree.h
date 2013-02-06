#pragma once

#include "QuadTreeNode.h"

class QuadTree
{
private:
	QuadTreeNode* m_parent;
public:
	QuadTree();
	QuadTree(int _levels, D3DXVECTOR2 _min, D3DXVECTOR2 _max);
	~QuadTree();

	bool addModel(Model* _model);
	bool addLight(PointLight* _light);
	bool addRoad(Road *_road);
	stack<Model*> getAllModels()const;
	stack<Model*> getModels(D3DXVECTOR3 _cameraPos)const;
	vector<PointLight*> getPointLights(D3DXVECTOR3 _cameraPos)const;
	stack<Road*> getRoads(D3DXVECTOR3 _cameraPos)const;
	stack<Model*> pullAllModels();
	bool removeModel(Model* _model);
};