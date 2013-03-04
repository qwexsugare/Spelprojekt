#pragma once

#include "ServerQuadTreeNode.h"

class ServerQuadTree
{
private:
	ServerQuadTreeNode* m_parent;
public:
	ServerQuadTree();
	ServerQuadTree(int _levels, D3DXVECTOR2 _min, D3DXVECTOR2 _max);
	~ServerQuadTree();
	
	bool addServerEntity(ServerEntity* _serverEntity);
	void getAllServerEntites(vector<ServerEntity*>& _serverEntities);
	vector<ServerEntity*> getServerEntities(D3DXVECTOR2 _focalPoint)const;
	bool intersectsWithObject(const BoundingSphere& _bs);
	bool intersectsWithObject(const BoundingOrientedBox& _obb);
	bool removeServerEntity(ServerEntity* _serverEntity);
	void updateServerEntities(float _dt);
};