#pragma once

#include "ServerEntity.h"
#include <stack>
#include <DirectXMath.h>
#include <DirectXCollision.h>
using namespace DirectX;

class ServerQuadTreeNode
{
private:
	D3DXVECTOR2 m_min;
	D3DXVECTOR2 m_max;
	vector<ServerEntity*> m_serverEntities;
	
	ServerQuadTreeNode* m_children[4];
	BoundingOrientedBox* m_obb;
public:
	ServerQuadTreeNode();
	ServerQuadTreeNode(int _levels, D3DXVECTOR2 _min, D3DXVECTOR2 _max);
	~ServerQuadTreeNode();
	
	void addServerEntity(bool& _success, ServerEntity* _serverEntity);
	void getAllServerEntites(vector<ServerEntity*>& _serverEntities);
	void getServerEntities(vector<ServerEntity*> _serverEntities, D3DXVECTOR2 _focalPoint)const;
	bool intersects(const ServerEntity* _serverEntity)const;
	bool intersectsWithObject(const BoundingSphere& _bs);
	bool intersectsWithObject(const BoundingOrientedBox& _obb);
	bool removeServerEntity(ServerEntity* _serverEntity);
	void updateServerEntities(float _dt);
};