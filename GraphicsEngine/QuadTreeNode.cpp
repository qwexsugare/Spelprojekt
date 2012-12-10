#include "QuadTreeNode.h"

QuadTreeNode::QuadTreeNode()
{
	for(int i = 0; i < 4; i++)
		this->m_children[i] = NULL;

	this->m_obb = NULL;
}

QuadTreeNode::QuadTreeNode(ID3D10Device* _device, int _levels, D3DXVECTOR2 _min, D3DXVECTOR2 _max)
{
	this->m_min = _min;
	this->m_max = _max;
	this->m_obb = new BoundingOrientedBox(
		XMFLOAT3((this->m_min.x+this->m_max.x)/2.0f, 0.0f, (this->m_min.y+this->m_max.y)/2.0f),
		XMFLOAT3((_max.x-_min.x)/2.0f, 5.0f, (_max.y-_min.y)/2.0f),
		XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f)
		);
	
	if(_levels > 1)
	{
		this->m_children[0] = new QuadTreeNode(_device, _levels-1, _min, (_max+_min)/2.0f);
		this->m_children[1] = new QuadTreeNode(_device, _levels-1, D3DXVECTOR2((_max.x+_min.x)/2.0f, _min.y), D3DXVECTOR2(_max.x, (_max.y+_min.y)/2.0f));
		this->m_children[2] = new QuadTreeNode(_device, _levels-1, D3DXVECTOR2(_min.x, (_max.y+_min.y)/2.0f), D3DXVECTOR2((_max.x+_min.x)/2.0f, _max.y));
		this->m_children[3] = new QuadTreeNode(_device, _levels-1, (_max+_min)/2.0f, _max);
	}
	else
	{
		for(int i = 0; i < 4; i++)
			this->m_children[i] = NULL;
	}
}

QuadTreeNode::~QuadTreeNode()
{
	for(int i = 0; i < 4; i++)
		if(this->m_children[i])
			delete this->m_children[i];

	for(int i = 0; i < this->m_models.size(); i++)
		delete this->m_models[i];

	if(this->m_obb)
		delete this->m_obb;
}

void QuadTreeNode::addModel(Model* _model)
{
	if(!this->m_children[0])
	{
		this->m_models.push_back(_model);
	}
	else if(this->intersects(_model))
	{
		int fittIndex = -1;
		int fittCounter = 0;
		for(int i = 0; i < 4; i++)
		{
			if(this->m_children[i]->intersects(_model))
			{
				fittIndex = i;
				fittCounter++;
			}
		}

		if(fittCounter > 1)
		{
			this->m_models.push_back(_model);
		}
		else
		{
			// This fucker is now my child's problem!!!! IM FREE!!!!111
			this->m_children[fittIndex]->addModel(_model);
		}
	}
	else
	{
		delete _model;
	}
}

bool QuadTreeNode::intersects(const Model* _model)const
{
	return _model->intersects(*this->m_obb);
}

void QuadTreeNode::getModels(stack<Model*>& _models)const
{
	if(this->m_children[0])
	{
		// ADD ALL CHILD MODELS TO STACK
		this->m_children[0]->getModels(_models);
		this->m_children[1]->getModels(_models);
		this->m_children[2]->getModels(_models);
		this->m_children[3]->getModels(_models);
	}
	
	// ADD MY MODELS TO STACK
	for(int i = 0; i < this->m_models.size(); i++)
		_models.push(this->m_models[i]);
}

bool QuadTreeNode::removeModel(Model* _model)
{
	bool removed = false;

	if(this->m_children[0])
	{
		// ADD ALL CHILD MODELS TO VECTOR
		removed = this->m_children[0]->removeModel(_model);
		if(!removed)
		{
			removed = this->m_children[1]->removeModel(_model);
			if(!removed)
			{
				removed = this->m_children[2]->removeModel(_model);
				if(!removed)
				{
					removed = this->m_children[3]->removeModel(_model);
				}
			}
		}
	}
	else
	{
		for(int i = 0; i < this->m_models.size() && !removed; i++)
		{
			if(this->m_models[i] == _model)
			{
				delete this->m_models[i];
				this->m_models.erase(this->m_models.begin()+i);
				removed = true;
			}
		}
	}

	return removed;
}