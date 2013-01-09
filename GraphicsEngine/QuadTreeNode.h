#pragma once

#include "Model.h"
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
	QuadTreeNode* m_children[4];
	BoundingOrientedBox* m_obb;
public:
	QuadTreeNode();
	QuadTreeNode(int _levels, D3DXVECTOR2 _min, D3DXVECTOR2 _max);
	~QuadTreeNode();

	void addModel(bool& _success, Model* _model);
	bool intersects(const Model* _model)const;
	void getModels(stack<Model*>& _models, D3DXVECTOR3 _cameraPos)const;
	void pullAllModels(stack<Model*>& _models);
	bool removeModel(Model* _model);
};