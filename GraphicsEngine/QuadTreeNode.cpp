#include "QuadTreeNode.h"

QuadTreeNode::QuadTreeNode()
{
	for(int i = 0; i < 4; i++)
		this->m_children[i] = NULL;
}

QuadTreeNode::QuadTreeNode(int _levels, D3DXVECTOR2 _min, D3DXVECTOR2 _max)
{
	this->m_min = _min;
	this->m_max = _max;

	if(_levels > 0)
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
}

void QuadTreeNode::addModel(Model* _model)
{
	// If i have no kids i must to add the model
	if(!this->m_children[0])
	{
		this->m_models.push_back(_model);
	}
	// If I have kids I might pass the model on to them
	else
	{
		bool done = false;
		for(int i = 0; i < 4 && !done; i++)
		{
			// Check if child can fit the model inside his belly.
			if(this->m_children[i]->fits(_model->getPosition2D()))
			{
				// This fucker is now my child's problem!!!! IM FREE!!!!111
				this->m_children[i]->addModel(_model);
				done = true;
			}
		}

		// If no children could fit the model I must take care of it :'(
		if(!done)
		{
			this->m_models.push_back(_model);
		}
	}
}

bool QuadTreeNode::fits(D3DXVECTOR2 _pos)
{
	return (_pos.x >= this->m_min.x && _pos.x <= this->m_max.x && _pos.y >= this->m_min.y && _pos.y <= this->m_max.y);
}

void QuadTreeNode::getModels(stack<Model*>& _models)const
{
	if(this->m_children[0])
	{
		// ADD ALL CHILD MODELS TO VECTOR
		this->m_children[0]->getModels(_models);
		this->m_children[1]->getModels(_models);
		this->m_children[2]->getModels(_models);
		this->m_children[3]->getModels(_models);
	}
	
	// ADD MY MODELS TO VECTOR
	for(int i = 0; i < this->m_models.size(); i++)
		_models.push(this->m_models[i]);
}