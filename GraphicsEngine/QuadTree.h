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
	stack<Model*> getModels()const;
	bool removeModel(Model* _model);
};