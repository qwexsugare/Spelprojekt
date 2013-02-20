#include "ServerQuadTree.h"

ServerQuadTree::ServerQuadTree()
{
	this->m_parent = NULL;
}

ServerQuadTree::ServerQuadTree(int _levels, D3DXVECTOR2 _min, D3DXVECTOR2 _max)
{
	this->m_parent = new ServerQuadTreeNode(_levels, _min, _max);
}

ServerQuadTree::~ServerQuadTree()
{
	if(this->m_parent)
		delete this->m_parent;
}

bool ServerQuadTree::addServerEntity(ServerEntity* _serverEntity)
{
	bool success;
	this->m_parent->addServerEntity(success, _serverEntity);
	return success;
}

void ServerQuadTree::getAllServerEntites(vector<ServerEntity*>& _serverEntities)
{
	m_parent->getAllServerEntites(_serverEntities);
}

vector<ServerEntity*> ServerQuadTree::getServerEntities(D3DXVECTOR2 _focalPoint)const
{
	vector<ServerEntity*> ses;
	this->m_parent->getServerEntities(ses, _focalPoint);
	return ses;
}

bool ServerQuadTree::removeServerEntity(ServerEntity* _serverEntity)
{
	return m_parent->removeServerEntity(_serverEntity);
}

void ServerQuadTree::updateServerEntities(float _dt)
{
	m_parent->updateServerEntities(_dt);
}