#pragma once

#include "stdafx.h"
#include "Mesh.h"

class DECLDIR Obb
{
private:
	D3DXVECTOR2 m_corners[4];
	D3DXVECTOR2 m_axes[2];
	double m_origins[2];
	D3DXVECTOR2 m_position;

	Mesh* m_mesh;
public:
	Obb();
    Obb(ID3D10Device* _device, D3DXVECTOR2 _center, double _w, double _h, double _angle);
	~Obb();

	void computeAxes();
	bool overlaps1Way(const Obb& _obb)const;
	bool intersects(const Obb& _obb)const;
	Mesh* getMesh()const { return this->m_mesh; }
	D3DXMATRIX getModelMatrix()const;
	void setPosition(D3DXVECTOR2 _position);
};