#include "Obb.h"

Obb::Obb()
{

}
   
Obb::Obb(D3DXVECTOR2 _center, double _w, double _h, double _angle)
{
	D3DXVECTOR2 X( cos(_angle), sin(_angle));
    D3DXVECTOR2 Y(-sin(_angle), cos(_angle));

    X *= _w / 2;
    Y *= _h / 2;

    this->m_corners[0] = _center - X - Y;
    this->m_corners[1] = _center + X - Y;
    this->m_corners[2] = _center + X + Y;
    this->m_corners[3] = _center - X + Y;

	this->computeAxes();


	//this->m_mesh = Mesh(
}

Obb::~Obb()
{

} 

void Obb::computeAxes()
{
	this->m_axes[0] = this->m_corners[1] - this->m_corners[0]; 
	this->m_axes[1] = this->m_corners[3] - this->m_corners[0]; 

	// Make the length of each axis 1/edge length so we know any
	// dot product must be less than 1 to fall within the edge.

	for (int i = 0; i < 2; ++i) {
		this->m_axes[i] /= pow(D3DXVec2Length(&this->m_axes[i]), 2.0);
		this->m_origins[i] = D3DXVec2Dot(&this->m_corners[0], &this->m_axes[i]);
	}
}

bool Obb::overlaps1Way(const Obb& _obb)const
{
    for (int a = 0; a < 2; ++a)
	{
		double t = D3DXVec2Dot(&_obb.m_corners[0], &this->m_axes[a]);

        // Find the extent of box 2 on axis a
        double tMin = t;
        double tMax = t;
        for(int c = 1; c < 4; ++c)
		{
            t = D3DXVec2Dot(&_obb.m_corners[c], &this->m_axes[a]);

            if(t < tMin)
                tMin = t;
			else if(t > tMax)
                tMax = t;
        }

        // We have to subtract off the origin

        // See if [tMin, tMax] intersects [0, 1]
		if ((tMin > 1 + this->m_origins[a]) || (tMax < this->m_origins[a])) {
            // There was no intersection along this dimension;
            // the boxes cannot possibly overlap.
            return false;
        }
    }

    // There was no dimension along which there is no intersection.
    // Therefore the boxes overlap.
    return true;
}

bool Obb::intersects(const Obb& _obb)const
{
	return (overlaps1Way(_obb) && _obb.overlaps1Way(*this));
}