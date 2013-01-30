#pragma once

#include "Model.h"
#include "PointLight.h"
#include "Road.h"
#include <stack>
#include <DirectXMath.h>
#include <DirectXCollision.h>
using namespace DirectX;

class QuadTreeNode
{
private:
	D3DXVECTOR2 m_min;
	D3DXVECTOR2 m_max;
	vector<Model*> m_models;
	vector<PointLight*> m_lights;
	vector<Road*> m_roads;
	QuadTreeNode* m_children[4];
	BoundingOrientedBox* m_obb;
public:
	QuadTreeNode();
	QuadTreeNode(int _levels, D3DXVECTOR2 _min, D3DXVECTOR2 _max);
	~QuadTreeNode();

	void addModel(bool& _success, Model* _model);
	void addLight(bool& _success, PointLight* _light);
	void addRoad(bool& _success, Road* _road);
	bool intersects(const Model* _model)const;
	bool intersects(PointLight* _light)const;
	bool intersects(Road* _road)const;
	void getModels(stack<Model*>& _models, D3DXVECTOR3 _cameraPos)const;
	void getLights(vector<PointLight*>& _lights, D3DXVECTOR3 _cameraPos)const;
	void getRoads(vector<Road*>& _roads, D3DXVECTOR3 _cameraPos)const;
	void pullAllModels(stack<Model*>& _models);
	bool removeModel(Model* _model);
};