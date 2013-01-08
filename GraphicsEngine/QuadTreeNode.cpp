#include "QuadTreeNode.h"

QuadTreeNode::QuadTreeNode()
{
	for(int i = 0; i < 4; i++)
		this->m_children[i] = NULL;

	this->m_obb = NULL;
}

QuadTreeNode::QuadTreeNode(int _levels, D3DXVECTOR2 _min, D3DXVECTOR2 _max)
{
	this->m_min = _min;
	this->m_max = _max;
	this->m_obb = new BoundingOrientedBox(
		XMFLOAT3((this->m_min.x+this->m_max.x)/2.0f, 0.0f, (this->m_min.y+this->m_max.y)/2.0f),
		XMFLOAT3((_max.x-_min.x)/2.0f, 0.5f, (_max.y-_min.y)/2.0f),
		XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f)
		);
	
	if(_levels > 1)
	{
		this->m_children[0] = new QuadTreeNode(_levels-1, _min, (_max+_min)/2.0f);
		this->m_children[1] = new QuadTreeNode(_levels-1, D3DXVECTOR2((_max.x+_min.x)/2.0f, _min.y), D3DXVECTOR2(_max.x, (_max.y+_min.y)/2.0f));
		this->m_children[2] = new QuadTreeNode(_levels-1, D3DXVECTOR2(_min.x, (_max.y+_min.y)/2.0f), D3DXVECTOR2((_max.x+_min.x)/2.0f, _max.y));
		this->m_children[3] = new QuadTreeNode(_levels-1, (_max+_min)/2.0f, _max);
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

bool QuadTreeNode::addModel(Model* _model)
{
	bool success = true;

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
	// Else the model is outside of the world tree and no one can take care of this poor sucker :(
	else
	{
		success = false;
	}

	return success;
}

bool QuadTreeNode::intersects(const Model* _model)const
{
	return _model->intersects(*this->m_obb);
}

void QuadTreeNode::getModels(stack<Model*>& _models, D3DXVECTOR3 _cameraPos)const
{
	if(this->m_children[0])
	{
		// ADD ALL CHILD MODELS TO STACK
		this->m_children[0]->getModels(_models, _cameraPos);
		this->m_children[1]->getModels(_models, _cameraPos);
		this->m_children[2]->getModels(_models, _cameraPos);
		this->m_children[3]->getModels(_models, _cameraPos);
	}
	
	// ADD MY MODELS TO STACK
	for(int i = 0; i < this->m_models.size(); i++)
	{
		// COMMENCE ADVANCED CHEAT CULLING

		// Calculate models distance to camera and make it positive +
		D3DXVECTOR2 modelDistanceToCamera = D3DXVECTOR2(this->m_models[i]->getPosition2D()-D3DXVECTOR2(_cameraPos.x, _cameraPos.z));
		modelDistanceToCamera.x = max(modelDistanceToCamera.x, -modelDistanceToCamera.x);
		modelDistanceToCamera.y = max(modelDistanceToCamera.y, -modelDistanceToCamera.y);
		// Find the greatest extent of the model bounding box
		float greatestExtent;
		if(this->m_models[i]->getObb()->Extents.x > this->m_models[i]->getObb()->Extents.z)
			greatestExtent = this->m_models[i]->getObb()->Extents.x;
		else
			greatestExtent = this->m_models[i]->getObb()->Extents.z;
		// Subtract the greatest extent from the distance
		modelDistanceToCamera.x -= greatestExtent;
		modelDistanceToCamera.y -= greatestExtent;

		// If the bounding box is within camera bounds, add it, otherwise it is "culled".
		if(modelDistanceToCamera.x < 30.0f && modelDistanceToCamera.y < 25.0f)
			_models.push(this->m_models[i]);

		// END ADVANCED CHEAT CULLING
	}
}

void QuadTreeNode::pullAllModels(stack<Model*>& _models)
{
	if(this->m_children[0])
	{
		// ADD ALL CHILD MODELS TO STACK
		this->m_children[0]->pullAllModels(_models);
		this->m_children[1]->pullAllModels(_models);
		this->m_children[2]->pullAllModels(_models);
		this->m_children[3]->pullAllModels(_models);
	}
	
	// ADD MY MODELS TO STACK
	for(int i = 0; i < this->m_models.size(); i++)
	{
		_models.push(this->m_models[i]);
		this->m_models.erase(this->m_models.begin()+i);
	}
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