#include "ServerQuadTreeNode.h"

ServerQuadTreeNode::ServerQuadTreeNode()
{
	for(int i = 0; i < 4; i++)
		this->m_children[i] = NULL;

	this->m_obb = NULL;
}

ServerQuadTreeNode::ServerQuadTreeNode(int _levels, D3DXVECTOR2 _min, D3DXVECTOR2 _max)
{
	this->m_min = _min;
	this->m_max = _max;
	this->m_obb = new BoundingOrientedBox(
		XMFLOAT3((this->m_min.x+this->m_max.x)/2.0f, 0.0f, (this->m_min.y+this->m_max.y)/2.0f),
		XMFLOAT3((_max.x-_min.x)/2.0f, 100000.0f, (_max.y-_min.y)/2.0f),
		XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f)
		);
	
	if(_levels > 1)
	{
		this->m_children[0] = new ServerQuadTreeNode(_levels-1, _min, (_max+_min)/2.0f);
		this->m_children[1] = new ServerQuadTreeNode(_levels-1, D3DXVECTOR2((_max.x+_min.x)/2.0f, _min.y), D3DXVECTOR2(_max.x, (_max.y+_min.y)/2.0f));
		this->m_children[2] = new ServerQuadTreeNode(_levels-1, D3DXVECTOR2(_min.x, (_max.y+_min.y)/2.0f), D3DXVECTOR2((_max.x+_min.x)/2.0f, _max.y));
		this->m_children[3] = new ServerQuadTreeNode(_levels-1, (_max+_min)/2.0f, _max);
	}
	else
	{
		for(int i = 0; i < 4; i++)
			this->m_children[i] = NULL;
	}
}

ServerQuadTreeNode::~ServerQuadTreeNode()
{
	for(int i = 0; i < 4; i++)
		if(this->m_children[i])
			delete this->m_children[i];

	for(int i = 0; i < m_serverEntities.size(); i++)
		delete m_serverEntities[i];

	if(this->m_obb)
		delete this->m_obb;
}

void ServerQuadTreeNode::addServerEntity(bool& _success, ServerEntity* _serverEntity)
{
	if(this->intersects(_serverEntity))
	{
		if(!this->m_children[0])
		{
			m_serverEntities.push_back(_serverEntity);
			_success = true;
		}
		else
		{
			int fittIndex = -1;
			int fittCounter = 0;
			for(int i = 0; i < 4; i++)
			{
				if(this->m_children[i]->intersects(_serverEntity))
				{
					fittIndex = i;
					fittCounter++;
				}
			}

			if(fittCounter > 1)
			{
				m_serverEntities.push_back(_serverEntity);
				_success = true;
			}
			else if(fittCounter > 0)
			{
				// This fucker is now my child's problem!!!! IM FREE!!!!111
				this->m_children[fittIndex]->addServerEntity(_success, _serverEntity);
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

void ServerQuadTreeNode::getAllServerEntites(vector<ServerEntity*>& _serverEntities)
{
	if(this->m_children[0])
	{
		this->m_children[0]->getAllServerEntites(_serverEntities);
		this->m_children[1]->getAllServerEntites(_serverEntities);
		this->m_children[2]->getAllServerEntites(_serverEntities);
		this->m_children[3]->getAllServerEntites(_serverEntities);
	}
	
	for(int i = 0; i < m_serverEntities.size(); i++)
		_serverEntities.push_back(m_serverEntities[i]);
}

void ServerQuadTreeNode::getServerEntities(vector<ServerEntity*> _serverEntities, D3DXVECTOR2 _focalPoint)const
{
	//D3DXVECTOR2 nodeDistanceToCamera = D3DXVECTOR2(m_obb->Center.x, m_obb->Center.z);
	//nodeDistanceToCamera.x = abs(nodeDistanceToCamera.x);
	//nodeDistanceToCamera.y = abs(nodeDistanceToCamera.y);

	//float greatestExtent;
	//if(m_obb->Extents.x > m_obb->Extents.z)
	//	greatestExtent = m_obb->Extents.x;
	//else
	//	greatestExtent = m_obb->Extents.z;

	//nodeDistanceToCamera.x -= greatestExtent;
	//nodeDistanceToCamera.y -= greatestExtent;
	//
	//if(abs(_focalPoint.x - m_obb->Center.x) < m_obb->Extents.x+6.0f && abs(_focalPoint.y - m_obb->Center.z) < m_obb->Extents.z+4.0f)
	//{
	//	if(this->m_children[0])
	//	{
	//		// ADD ALL CHILD MODELS TO STACK
	//		m_children[0]->getServerEntities(_serverEntities, _focalPoint);
	//		m_children[1]->getServerEntities(_serverEntities, _focalPoint);
	//		m_children[2]->getServerEntities(_serverEntities, _focalPoint);
	//		m_children[3]->getServerEntities(_serverEntities, _focalPoint);
	//	}
	//
	//	// ADD MY MODELS TO STACK
	//	for(int i = 0; i < m_serverEntities.size(); i++)
	//	{
	//		// Calculate models distance to camera and make it positive
	//		D3DXVECTOR2 modelDistanceToCamera = m_serverEntities[i]->getPosition2D()-_focalPoint;
	//		modelDistanceToCamera.x = abs(modelDistanceToCamera.x);
	//		modelDistanceToCamera.y = abs(modelDistanceToCamera.y);

	//		// Find the greatest extent of the model bounding box
	//		float greatestExtent;
	//		if(m_serverEntities[i]->getObb())
	//		{
	//			if(m_serverEntities[i]->getObb()->Extents.x > m_serverEntities[i]->getObb()->Extents.z)
	//				greatestExtent = m_serverEntities[i]->getObb()->Extents.x;
	//			else
	//				greatestExtent = m_serverEntities[i]->getObb()->Extents.z;
	//		}
	//		else if(m_models[i]->getBs())
	//		{
	//			greatestExtent = m_serverEntities[i]->getBs()->Radius;
	//		}
	//		else
	//		{
	//			// we are fucked
	//		}

	//		// Subtract the greatest extent from the distance
	//		modelDistanceToCamera.x -= greatestExtent;
	//		modelDistanceToCamera.y -= greatestExtent;

	//		if(modelDistanceToCamera.x < 6.0f && modelDistanceToCamera.y < 4.0f)
	//			_models.push(m_serverEntities[i]);
	//	}
	//}

	if(this->m_children[0])
	{
		// ADD ALL CHILD MODELS TO STACK
		m_children[0]->getServerEntities(_serverEntities, _focalPoint);
		m_children[1]->getServerEntities(_serverEntities, _focalPoint);
		m_children[2]->getServerEntities(_serverEntities, _focalPoint);
		m_children[3]->getServerEntities(_serverEntities, _focalPoint);
	}
	
	// ADD MY MODELS TO STACK
	for(int i = 0; i < m_serverEntities.size(); i++)
	{
		_serverEntities.push_back(m_serverEntities[i]);
	}
}

bool ServerQuadTreeNode::intersects(const ServerEntity* _serverEntity)const
{
	return _serverEntity->contains(*m_obb) != ContainmentType::DISJOINT;
}

bool ServerQuadTreeNode::removeServerEntity(ServerEntity* _serverEntity)
{
	bool removed = false;
	
	for(int i = 0; i < m_serverEntities.size() && !removed; i++)
	{
		if(m_serverEntities[i] == _serverEntity)
		{
			delete m_serverEntities[i];
			m_serverEntities.erase(m_serverEntities.begin()+i);
			removed = true;
		}
	}

	if(!removed && this->m_children[0])
	{
		removed = this->m_children[0]->removeServerEntity(_serverEntity);
		if(!removed)
		{
			removed = this->m_children[1]->removeServerEntity(_serverEntity);
			if(!removed)
			{
				removed = this->m_children[2]->removeServerEntity(_serverEntity);
				if(!removed)
				{
					removed = this->m_children[3]->removeServerEntity(_serverEntity);
				}
			}
		}
	}

	return removed;
}

void ServerQuadTreeNode::updateServerEntities(float _dt)
{
	if(this->m_children[0])
	{
		m_children[0]->updateServerEntities(_dt);
		m_children[1]->updateServerEntities(_dt);
		m_children[2]->updateServerEntities(_dt);
		m_children[3]->updateServerEntities(_dt);
	}
	
	for(int i = 0; i < m_serverEntities.size(); i++)
	{
		m_serverEntities[i]->update(_dt);
	}
}