#pragma once

#include "stdafx.h"

class Obb
{
private:
	D3DXVECTOR2 m_corners[4];
	D3DXVECTOR2 m_axes[2];
	double m_origins[2];

	ID3D10Buffer* m_buffer;
public:
	Obb();
    Obb(D3DXVECTOR2 _center, double _w, double _h, double _angle);
	~Obb();

	void computeAxes();
	bool overlaps1Way(const Obb& _obb)const;
	bool intersects(const Obb& _obb)const;
};