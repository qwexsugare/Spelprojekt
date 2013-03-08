#include "QuadTreeNode.h"

QuadTreeNode::QuadTreeNode()
{
	for(int i = 0; i < 4; i++)
		this->m_children[i] = NULL;

	this->m_obb = NULL;
}

QuadTreeNode::QuadTreeNode(int _levels, D3DXVECTOR2 _min, D3DXVECTOR2 _max, D3DXVECTOR2 _cameraOffset)
{
	this->m_min = _min;
	this->m_max = _max;
	this->m_obb = new BoundingOrientedBox(
		XMFLOAT3((this->m_min.x+this->m_max.x)/2.0f, 0.0f, (this->m_min.y+this->m_max.y)/2.0f),
		XMFLOAT3((_max.x-_min.x)/2.0f, 100000.0f, (_max.y-_min.y)/2.0f),
		XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f)
		);
	m_cameraOffset = _cameraOffset;
	
	if(_levels > 1)
	{
		this->m_children[0] = new QuadTreeNode(_levels-1, _min, (_max+_min)/2.0f, _cameraOffset);
		this->m_children[1] = new QuadTreeNode(_levels-1, D3DXVECTOR2((_max.x+_min.x)/2.0f, _min.y), D3DXVECTOR2(_max.x, (_max.y+_min.y)/2.0f), _cameraOffset);
		this->m_children[2] = new QuadTreeNode(_levels-1, D3DXVECTOR2(_min.x, (_max.y+_min.y)/2.0f), D3DXVECTOR2((_max.x+_min.x)/2.0f, _max.y), _cameraOffset);
		this->m_children[3] = new QuadTreeNode(_levels-1, (_max+_min)/2.0f, _max, _cameraOffset);
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

	for(int i = 0; i < m_particleEngines.size(); i++)
		delete m_particleEngines[i];

	for(int i = 0; i < this->m_lights.size(); i++)
	{
		delete this->m_lights[i];
	}

	for(int i = 0; i < this->m_roads.size(); i++)
	{
		delete this->m_roads[i];
	}

	if(this->m_obb)
		delete this->m_obb;
}

void QuadTreeNode::addParticleEngine(bool& _success, ParticleEngine* _particleEngine)
{
	if(this->intersects(_particleEngine->getBs()))
	{
		if(!this->m_children[0])
		{
			this->m_particleEngines.push_back(_particleEngine);
			_success = true;
		}
		else
		{
			int fittIndex = -1;
			int fittCounter = 0;
			for(int i = 0; i < 4; i++)
			{
				if(this->m_children[i]->intersects(_particleEngine->getBs()))
				{
					fittIndex = i;
					fittCounter++;
				}
			}

			if(fittCounter > 1)
			{
				m_particleEngines.push_back(_particleEngine);
				_success = true;
			}
			else if(fittCounter > 0)
			{
				// This fucker is now my child's problem!!!! IM FREE!!!!111
				this->m_children[fittIndex]->addParticleEngine(_success, _particleEngine);
			}
			// Else we're fucked
			else
			{
				_success = false;
			}
		}
	}
	// Else the model is outside of the world tree and no one can take care of this poor sucker :(
	else
	{
		_success = false;
	}
}

void QuadTreeNode::addModel(bool& _success, Model* _model)
{
	if(this->intersects(_model))
	{
		if(!this->m_children[0])
		{
			this->m_models.push_back(_model);
			_success = true;
		}
		else
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
				_success = true;
			}
			else if(fittCounter > 0)
			{
				// This fucker is now my child's problem!!!! IM FREE!!!!111
				this->m_children[fittIndex]->addModel(_success, _model);
			}
			// Else we're fucked
			else
			{
				_success = false;
			}
		}
	}
	// Else the model is outside of the world tree and no one can take care of this poor sucker :(
	else
	{
		_success = false;
	}
}

void QuadTreeNode::addLight(bool& _success, PointLight* _light)
{
	if(this->intersects(_light))
	{
		if(!this->m_children[0])
		{
			this->m_lights.push_back(_light);
			_success = true;
		}
		else
		{
			int fittIndex = -1;
			int fittCounter = 0;
			for(int i = 0; i < 4; i++)
			{
				if(this->m_children[i]->intersects(_light))
				{
					fittIndex = i;
					fittCounter++;
				}
			}

			if(fittCounter > 1)
			{
				this->m_lights.push_back(_light);
				_success = true;
			}
			else if(fittCounter > 0)
			{
				// This fucker is now my child's problem!!!! IM FREE!!!!111
				this->m_children[fittIndex]->addLight(_success, _light);
			}
			// Else we're fucked
			else
			{
				_success = false;
			}
		}
	}
	// Else the model is outside of the world tree and no one can take care of this poor sucker :(
	else
	{
		_success = false;
	}
}

void QuadTreeNode::addRoad(bool& _success, Road* _road)
{
	if(this->intersects(_road))
	{
		if(!this->m_children[0])
		{
			this->m_roads.push_back(_road);
			_success = true;
		}
		else
		{
			int fittIndex = -1;
			int fittCounter = 0;
			for(int i = 0; i < 4; i++)
			{
				if(this->m_children[i]->intersects(_road))
				{
					fittIndex = i;
					fittCounter++;
				}
			}

			if(fittCounter > 1)
			{
				this->m_roads.push_back(_road);
				_success = true;
			}
			else if(fittCounter > 0)
			{
				// This fucker is now my child's problem!!!! IM FREE!!!!111
				this->m_children[fittIndex]->addRoad(_success, _road);
			}
			// Else we're fucked
			else
			{
				_success = false;
			}
		}
	}
	// Else the model is outside of the world tree and no one can take care of this poor sucker :(
	else
	{
		_success = false;
	}
}

bool QuadTreeNode::intersects(const BoundingSphere _bs)const
{
	return m_obb->Contains(_bs) != ContainmentType::DISJOINT;
}

bool QuadTreeNode::intersects(const Model* _model)const
{
	return _model->intersects(*this->m_obb);
}

bool QuadTreeNode::intersects(PointLight* _light)const
{
	return _light->getBs()->Contains(*this->m_obb) != ContainmentType::DISJOINT;
}

bool QuadTreeNode::intersects(Road* _road)const
{
	return _road->getOBB()->Contains(*this->m_obb) != ContainmentType::DISJOINT;
}

void QuadTreeNode::getAllLights(vector<PointLight*>& _lights)
{
	if(this->m_children[0])
	{
		this->m_children[0]->getAllLights(_lights);
		this->m_children[1]->getAllLights(_lights);
		this->m_children[2]->getAllLights(_lights);
		this->m_children[3]->getAllLights(_lights);
	}
	
	for(int i = 0; i < this->m_lights.size(); i++)
		_lights.push_back(this->m_lights[i]);
}

void QuadTreeNode::getAllModels(stack<Model*>& _models)
{
	if(this->m_children[0])
	{
		this->m_children[0]->getAllModels(_models);
		this->m_children[1]->getAllModels(_models);
		this->m_children[2]->getAllModels(_models);
		this->m_children[3]->getAllModels(_models);
	}
	
	for(int i = 0; i < this->m_models.size(); i++)
		_models.push(this->m_models[i]);
}

void QuadTreeNode::getAllRoads(stack<Road*>& _roads)
{
	if(this->m_children[0])
	{
		this->m_children[0]->getAllRoads(_roads);
		this->m_children[1]->getAllRoads(_roads);
		this->m_children[2]->getAllRoads(_roads);
		this->m_children[3]->getAllRoads(_roads);
	}
	
	for(int i = 0; i < this->m_roads.size(); i++)
		_roads.push(this->m_roads[i]);
}

void QuadTreeNode::getModels(stack<Model*>& _models, D3DXVECTOR2 _focalPoint)const
{
	D3DXVECTOR2 nodeDistanceToCamera = D3DXVECTOR2(m_obb->Center.x, m_obb->Center.z);
	nodeDistanceToCamera.x = abs(nodeDistanceToCamera.x);
	nodeDistanceToCamera.y = abs(nodeDistanceToCamera.y);

	float greatestExtent;
	if(m_obb->Extents.x > m_obb->Extents.z)
		greatestExtent = m_obb->Extents.x;
	else
		greatestExtent = m_obb->Extents.z;

	nodeDistanceToCamera.x -= greatestExtent;
	nodeDistanceToCamera.y -= greatestExtent;
	
	if(abs(_focalPoint.x - m_obb->Center.x) < m_obb->Extents.x+m_cameraOffset.x && abs(_focalPoint.y - m_obb->Center.z) < m_obb->Extents.z+m_cameraOffset.y)
	{
		if(this->m_children[0])
		{
			// ADD ALL CHILD MODELS TO STACK
			m_children[0]->getModels(_models, _focalPoint);
			m_children[1]->getModels(_models, _focalPoint);
			m_children[2]->getModels(_models, _focalPoint);
			m_children[3]->getModels(_models, _focalPoint);
		}
	
		// ADD MY MODELS TO STACK
		for(int i = 0; i < this->m_models.size(); i++)
		{
			// Calculate models distance to camera and make it positive
			D3DXVECTOR2 modelDistanceToCamera = this->m_models[i]->getPosition2D()-_focalPoint;
			modelDistanceToCamera.x = abs(modelDistanceToCamera.x);
			modelDistanceToCamera.y = abs(modelDistanceToCamera.y);

			// Find the greatest extent of the model bounding box
			float greatestExtent;
			if(m_models[i]->getObb())
			{
				if(this->m_models[i]->getObb()->Extents.x > this->m_models[i]->getObb()->Extents.z)
					greatestExtent = this->m_models[i]->getObb()->Extents.x;
				else
					greatestExtent = this->m_models[i]->getObb()->Extents.z;
			}
			else if(m_models[i]->getBs())
			{
				greatestExtent = this->m_models[i]->getBs()->Radius;
			}
			else
			{
				// we are fucked
			}

			// Subtract the greatest extent from the distance
			modelDistanceToCamera.x -= greatestExtent;
			modelDistanceToCamera.y -= greatestExtent;
			
			if(modelDistanceToCamera.x < m_cameraOffset.x && modelDistanceToCamera.y < m_cameraOffset.y)
				_models.push(this->m_models[i]);
		}
	}
}

void QuadTreeNode::getLights(vector<PointLight*>& _lights, D3DXVECTOR2 _focalPoint)const
{
	D3DXVECTOR2 nodeDistanceToCamera = D3DXVECTOR2(m_obb->Center.x, m_obb->Center.z);
	nodeDistanceToCamera.x = abs(nodeDistanceToCamera.x);
	nodeDistanceToCamera.y = abs(nodeDistanceToCamera.y);

	float greatestExtent;
	if(m_obb->Extents.x > m_obb->Extents.z)
		greatestExtent = m_obb->Extents.x;
	else
		greatestExtent = m_obb->Extents.z;

	nodeDistanceToCamera.x -= greatestExtent;
	nodeDistanceToCamera.y -= greatestExtent;
	
	if(abs(_focalPoint.x - m_obb->Center.x) < m_obb->Extents.x+m_cameraOffset.x && abs(_focalPoint.y - m_obb->Center.z) < m_obb->Extents.z+m_cameraOffset.y)
	{
		if(this->m_children[0])
		{
			// ADD ALL CHILD MODELS TO STACK
			this->m_children[0]->getLights(_lights, _focalPoint);
			this->m_children[1]->getLights(_lights, _focalPoint);
			this->m_children[2]->getLights(_lights, _focalPoint);
			this->m_children[3]->getLights(_lights, _focalPoint);
		}
	
		// ADD MY MODELS TO STACK
		for(int i = 0; i < this->m_lights.size(); i++)
		{
			// Calculate models distance to camera and make it positive
			D3DXVECTOR2 modelDistanceToCamera = m_lights[i]->getPosition2D()-_focalPoint;
			modelDistanceToCamera.x = abs(modelDistanceToCamera.x);
			modelDistanceToCamera.y = abs(modelDistanceToCamera.y);

			float greatestExtent = this->m_lights[i]->getBs()->Radius;

			// Subtract the greatest extent from the distance
			modelDistanceToCamera.x -= greatestExtent;
			modelDistanceToCamera.y -= greatestExtent;

			if(modelDistanceToCamera.x < m_cameraOffset.x && modelDistanceToCamera.y < m_cameraOffset.y)
				_lights.push_back(this->m_lights[i]);
		}
	}
}

void QuadTreeNode::getParticleEngines(stack<ParticleEngine*>& _particleEngines, D3DXVECTOR2 _focalPoint)const
{
	if(this->m_children[0])
	{
		// ADD ALL CHILD MODELS TO STACK
		this->m_children[0]->getParticleEngines(_particleEngines, _focalPoint);
		this->m_children[1]->getParticleEngines(_particleEngines, _focalPoint);
		this->m_children[2]->getParticleEngines(_particleEngines, _focalPoint);
		this->m_children[3]->getParticleEngines(_particleEngines, _focalPoint);
	}
	
	// ADD MY MODELS TO STACK
	for(int i = 0; i < m_particleEngines.size(); i++)
	{
		_particleEngines.push(m_particleEngines[i]);
	}
}

void QuadTreeNode::getRoads(stack<Road*>& _roads, D3DXVECTOR2 _focalPoint)const
{
	D3DXVECTOR2 nodeDistanceToCamera = D3DXVECTOR2(m_obb->Center.x, m_obb->Center.z);
	nodeDistanceToCamera.x = abs(nodeDistanceToCamera.x);
	nodeDistanceToCamera.y = abs(nodeDistanceToCamera.y);

	float greatestExtent;
	if(m_obb->Extents.x > m_obb->Extents.z)
		greatestExtent = m_obb->Extents.x;
	else
		greatestExtent = m_obb->Extents.z;

	nodeDistanceToCamera.x -= greatestExtent;
	nodeDistanceToCamera.y -= greatestExtent;
	
	if(abs(_focalPoint.x - m_obb->Center.x) < m_obb->Extents.x+m_cameraOffset.x && abs(_focalPoint.y - m_obb->Center.z) < m_obb->Extents.z+m_cameraOffset.y)
	{
		if(this->m_children[0])
		{
			// ADD ALL CHILD MODELS TO STACK
			this->m_children[0]->getRoads(_roads, _focalPoint);
			this->m_children[1]->getRoads(_roads, _focalPoint);
			this->m_children[2]->getRoads(_roads, _focalPoint);
			this->m_children[3]->getRoads(_roads, _focalPoint);
		}
	
		// ADD MY MODELS TO STACK
		for(int i = 0; i < this->m_roads.size(); i++)
		{
			// Calculate models distance to camera and make it positive +
			D3DXVECTOR2 modelDistanceToCamera = m_roads[i]->getPosition2D()-_focalPoint;
			modelDistanceToCamera.x = abs(modelDistanceToCamera.x);
			modelDistanceToCamera.y = abs(modelDistanceToCamera.y);

			// Find the greatest extent of the bounding box
			float greatestExtent;
			if(this->m_roads[i]->getOBB()->Extents.x > this->m_roads[i]->getOBB()->Extents.z)
				greatestExtent = this->m_roads[i]->getOBB()->Extents.x;
			else
				greatestExtent = this->m_roads[i]->getOBB()->Extents.z;

			// Subtract the greatest extent from the distance
			modelDistanceToCamera.x -= greatestExtent;
			modelDistanceToCamera.y -= greatestExtent;
		
			if(modelDistanceToCamera.x < m_cameraOffset.x && modelDistanceToCamera.y < m_cameraOffset.y)
				_roads.push(m_roads[i]);
		}
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
	
	for(int i = 0; i < this->m_models.size() && !removed; i++)
	{
		if(this->m_models[i] == _model)
		{
			delete this->m_models[i];
			this->m_models.erase(this->m_models.begin()+i);
			removed = true;
		}
	}

	if(!removed && this->m_children[0])
	{
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

	return removed;
}

bool QuadTreeNode::removeLight(PointLight* _light)
{
	bool removed = false;
	
	for(int i = 0; i < this->m_lights.size() && !removed; i++)
	{
		if(this->m_lights[i] == _light)
		{
			delete this->m_lights[i];
			this->m_lights.erase(this->m_lights.begin()+i);
			removed = true;
		}
	}

	if(!removed && this->m_children[0])
	{
		removed = this->m_children[0]->removeLight(_light);
		if(!removed)
		{
			removed = this->m_children[1]->removeLight(_light);
			if(!removed)
			{
				removed = this->m_children[2]->removeLight(_light);
				if(!removed)
				{
					removed = this->m_children[3]->removeLight(_light);
				}
			}
		}
	}

	return removed;
}

bool QuadTreeNode::removeParticleEngine(ParticleEngine* _pe)
{
	bool removed = false;
	
	for(int i = 0; i < this->m_particleEngines.size() && !removed; i++)
	{
		if(m_particleEngines[i] == _pe)
		{
			delete m_particleEngines[i];
			m_particleEngines.erase(m_particleEngines.begin()+i);
			removed = true;
		}
	}

	if(!removed && this->m_children[0])
	{
		removed = this->m_children[0]->removeParticleEngine(_pe);
		if(!removed)
		{
			removed = this->m_children[1]->removeParticleEngine(_pe);
			if(!removed)
			{
				removed = this->m_children[2]->removeParticleEngine(_pe);
				if(!removed)
				{
					removed = this->m_children[3]->removeParticleEngine(_pe);
				}
			}
		}
	}

	return removed;
}

bool QuadTreeNode::removeRoad(Road* _road)
{
	bool removed = false;
	
	for(int i = 0; i < this->m_roads.size() && !removed; i++)
	{
		if(this->m_roads[i] == _road)
		{
			delete this->m_roads[i];
			this->m_roads.erase(this->m_roads.begin()+i);
			removed = true;
		}
	}

	if(!removed && this->m_children[0])
	{
		removed = this->m_children[0]->removeRoad(_road);
		if(!removed)
		{
			removed = this->m_children[1]->removeRoad(_road);
			if(!removed)
			{
				removed = this->m_children[2]->removeRoad(_road);
				if(!removed)
				{
					removed = this->m_children[3]->removeRoad(_road);
				}
			}
		}
	}

	return removed;
}