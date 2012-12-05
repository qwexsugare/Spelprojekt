#pragma once

#include "stdafx.h"

class BoundingSphere
{
private:
	D3DXVECTOR3 m_position;
	float m_radius;
public:
	BoundingSphere();
	~BoundingSphere();

	bool intersects(const BoundingSphere& _bs)const;
};