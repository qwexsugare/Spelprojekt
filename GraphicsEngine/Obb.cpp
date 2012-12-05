#include "Obb.h"
#include "VertexStructs.h"

Obb::Obb()
{

}
   
Obb::Obb(ID3D10Device* _device, D3DXVECTOR2 _center, double _w, double _h, double _angle)
{
	this->m_angle = _angle;
	this->m_width = _w;
	this->m_height = _h;
	this->m_position = _center;

	D3DXVECTOR2 X( cos(this->m_angle), sin(this->m_angle));
    D3DXVECTOR2 Y(-sin(this->m_angle), cos(this->m_angle));

    X *= this->m_width / 2;
    Y *= this->m_height / 2;

    this->m_corners[0] = - X - Y;
    this->m_corners[1] = X - Y;
    this->m_corners[2] = X + Y;
    this->m_corners[3] = - X + Y;

	this->computeAxes();
	
	ID3D10Buffer* buffer;
	D3D10_BUFFER_DESC bd;
	bd.Usage = D3D10_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof( Vertex ) * 4;
	bd.BindFlags = D3D10_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
	bd.MiscFlags = 0;

	_device->CreateBuffer( &bd, 0, &buffer);

	Vertex *vertexData = NULL;
	buffer->Map( D3D10_MAP_WRITE_DISCARD, 0, reinterpret_cast< void** >((void**)&vertexData));
	vertexData[0].pos = D3DXVECTOR3(this->m_corners[0].x, 0.0f, this->m_corners[0].y);
	vertexData[1].pos = D3DXVECTOR3(this->m_corners[1].x, 0.0f, this->m_corners[1].y);
	vertexData[2].pos = D3DXVECTOR3(this->m_corners[3].x, 0.0f, this->m_corners[3].y);
	vertexData[3].pos = D3DXVECTOR3(this->m_corners[2].x, 0.0f, this->m_corners[2].y);
	buffer->Unmap();

	this->m_mesh = new Mesh(buffer, 4);
}

Obb::~Obb()
{
	delete this->m_mesh;
} 

void Obb::computeAxes()
{
	this->m_axes[0] = this->m_corners[1] - this->m_corners[0]; 
	this->m_axes[1] = this->m_corners[3] - this->m_corners[0]; 

	// Make the length of each axis 1/edge length so we know any
	// dot product must be less than 1 to fall within the edge.

	for (int i = 0; i < 2; ++i) {
		this->m_axes[i] /= pow(D3DXVec2Length(&this->m_axes[i]), 2.0);
		this->m_origins[i] = D3DXVec2Dot(&(this->m_corners[0]+this->m_position), &this->m_axes[i]);
	}
}

D3DXMATRIX Obb::getModelMatrix()const
{
	D3DXMATRIX ret = D3DXMATRIX(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		this->m_position.x, 0.0f, this->m_position.y, 1.0f);

	return ret;
}

bool Obb::overlaps1Way(const Obb& _obb)const
{
    for (int a = 0; a < 2; ++a)
	{
		double t = D3DXVec2Dot(&(_obb.m_corners[0]+_obb.m_position), &this->m_axes[a]);

        // Find the extent of box 2 on axis a
        double tMin = t;
        double tMax = t;
        for(int c = 1; c < 4; ++c)
		{
            t = D3DXVec2Dot(&(_obb.m_corners[c]+_obb.m_position), &this->m_axes[a]);

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

void Obb::setAngle(double _angle)
{
	this->m_angle = _angle;

	D3DXVECTOR2 X( cos(this->m_angle), sin(this->m_angle));
    D3DXVECTOR2 Y(-sin(this->m_angle), cos(this->m_angle));

    X *= this->m_width / 2;
    Y *= this->m_height / 2;

    this->m_corners[0] = - X - Y;
    this->m_corners[1] = X - Y;
    this->m_corners[2] = X + Y;
    this->m_corners[3] = - X + Y;

	this->computeAxes();
	
	Vertex *vertexData = NULL;
	this->m_mesh->buffer->Map( D3D10_MAP_WRITE_DISCARD, 0, reinterpret_cast< void** >((void**)&vertexData));
	vertexData[0].pos = D3DXVECTOR3(this->m_corners[0].x, 0.0f, this->m_corners[0].y);
	vertexData[1].pos = D3DXVECTOR3(this->m_corners[1].x, 0.0f, this->m_corners[1].y);
	vertexData[2].pos = D3DXVECTOR3(this->m_corners[3].x, 0.0f, this->m_corners[3].y);
	vertexData[3].pos = D3DXVECTOR3(this->m_corners[2].x, 0.0f, this->m_corners[2].y);
	this->m_mesh->buffer->Unmap();
}

void Obb::setPosition(D3DXVECTOR2 _position)
{
	this->m_position = _position;
	this->computeAxes();
}