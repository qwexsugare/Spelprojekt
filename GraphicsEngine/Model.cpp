#include "Model.h"

Model::Model()
{
	this->m_obb = NULL;
	this->m_bs = NULL;
	this->animation = NULL;
}

Model::Model(ID3D10Device* _device, Mesh* _mesh, Animation _animation, D3DXVECTOR3 _position, D3DXVECTOR3 _scale, D3DXVECTOR3 _rotation, float _alpha)
{
	this->m_alpha = _alpha;
	this->m_mesh = _mesh;
	this->m_position = _position;
	this->m_scale = _scale;
	this->m_rotation = _rotation;
	this->updateModelMatrix();
	//this->m_obb = new BoundingOrientedBox(XMFLOAT3(_position.x, 0.0f, _position.z), XMFLOAT3(0.5f, 0.5f, 0.5f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	//this->m_bs = NULL;
	//this->m_bs = new BoundingSphere(XMFLOAT3(_position.x, 0.0f, _position.z), 2.0f);
	if(_mesh->m_bs == NULL)
	{
		this->m_bs = NULL;
		this->m_obb = new BoundingOrientedBox(*_mesh->m_obb);
		this->m_obb->Center = XMFLOAT3(m_position.x, m_position.y, m_position.z);
		this->m_obb->Extents.x *= _scale.x;
		this->m_obb->Extents.y *= _scale.y;
		this->m_obb->Extents.z *= _scale.z;
	}
	if(_mesh->m_obb == NULL)
	{
		this->m_bs = new BoundingSphere(*_mesh->m_bs);
		this->m_obb = NULL;
		m_bs->Center = XMFLOAT3(m_position.x, m_position.y, m_position.z);

		float largestScale = _scale.x;
		if(_scale.y > largestScale)
			largestScale = _scale.y;
		if(_scale.z > largestScale)
			largestScale = _scale.z;
		this->m_bs->Radius *= largestScale;
	}
	
	this->animation =  new Animation(_animation);
}

Model::~Model()
{
	if(this->m_obb)
		delete this->m_obb;
	if(this->m_bs)
		delete this->m_bs;
	if(this->animation)
		delete this->animation;
}

float Model::getAlpha()const
{
	return this->m_alpha;
}

BoundingOrientedBox* Model::getObb()const
{
	return this->m_obb;
}

Mesh *Model::getMesh() const
{
	return this->m_mesh;
}

Animation* Model::getAnimation()
{
	return this->animation;
}

FLOAT3 Model::getPosition()const
{
	return FLOAT3(this->m_position.x, this->m_position.y, this->m_position.z);
}

D3DXVECTOR2 Model::getPosition2D()const
{
	return D3DXVECTOR2(this->m_position.x, this->m_position.z);
}

bool Model::contains(const BoundingOrientedBox& _obb)const
{
	if(this->m_obb)
		return this->m_obb->Contains(_obb);
	else if(this->m_bs)
		return this->m_bs->Contains(_obb);
	else
		return false;
}

bool Model::contains(const BoundingSphere& _bs)const
{
	if(this->m_obb)
		return this->m_obb->Contains(_bs);
	else if(this->m_bs)
		return this->m_bs->Contains(_bs);
	else
		return false;
}

bool Model::intersects(const BoundingOrientedBox& _obb)const
{
	if(this->m_obb)
		return this->m_obb->Intersects(_obb);
	else if(this->m_bs)
		return this->m_bs->Intersects(_obb);
	else
		return false;
}

bool Model::intersects(const BoundingSphere& _bs)const
{
	if(this->m_obb)
		return this->m_obb->Intersects(_bs);
	else if(this->m_bs)
		return this->m_bs->Intersects(_bs);
	else
		return false;
}

bool Model::intersects(float& _dist, D3DXVECTOR3 _origin, D3DXVECTOR3 _direction)const
{
	_direction = -_direction;

	if(this->m_obb)
		return this->m_obb->Intersects(XMLoadFloat3(&XMFLOAT3(_origin)), XMLoadFloat3(&XMFLOAT3(_direction)), _dist);
	else if(this->m_bs)
		return this->m_bs->Intersects(XMLoadFloat3(&XMFLOAT3(_origin)), XMLoadFloat3(&XMFLOAT3(_direction)), _dist);
	else
	{
		_dist = 0;
		return false;
	}
}

void Model::move(FLOAT3 _distance)
{
	this->m_position.x += _distance.x;
	this->m_position.y += _distance.y;
	this->m_position.z += _distance.z;
	this->updateModelMatrix();
	if(this->m_bs)
	{
		this->m_bs->Center = XMFLOAT3(this->m_position.x, this->m_position.y, this->m_position.z);
	}
	else
	{
		this->m_obb->Center = XMFLOAT3(this->m_position.x, this->m_position.y, this->m_position.z);
	}
}

void Model::rotate(float _yaw, float _pitch, float _roll)
{
	D3DXMATRIX rotationMatrix;
	D3DXMatrixRotationYawPitchRoll(&rotationMatrix, _yaw, _pitch, _roll);
	D3DXMatrixMultiply(&this->m_modelMatrix, &rotationMatrix, &this->m_modelMatrix);

	if(this->m_obb)
	{
		XMMATRIX transform = XMMatrixRotationRollPitchYaw(_pitch, _yaw, _roll);
		XMVECTOR rot = XMLoadFloat3(&XMFLOAT3(_yaw, _pitch, _roll));
		XMVECTOR transsexual = XMLoadFloat3(&XMFLOAT3(0.0f, 0.0f, 0.0f));

		BoundingOrientedBox box;
		this->m_obb->Transform(box, transform);
		//this->m_obb = new BoundingOrientedBox(box);
		this->m_obb->Center = box.Center;
		this->m_obb->Orientation = box.Orientation;
		this->m_obb->Extents = box.Extents;
		float orientationNorm = sqrt(box.Orientation.x * box.Orientation.x + box.Orientation.y * box.Orientation.y +  box.Orientation.z * box.Orientation.z + box.Orientation.w * box.Orientation.w);
		this->m_obb->Orientation.x = this->m_obb->Orientation.x / orientationNorm;
		this->m_obb->Orientation.y = this->m_obb->Orientation.y / orientationNorm;
		this->m_obb->Orientation.z = this->m_obb->Orientation.z / orientationNorm;
		this->m_obb->Orientation.w = this->m_obb->Orientation.w / orientationNorm;

		//this->m_obb->Transform(box, 1.0f, rot, transsexual);
	}
}

void Model::setAlpha(float _alpha)
{
	this->m_alpha = _alpha;
}

void Model::setPosition(D3DXVECTOR3 _position)
{
	this->m_position = _position;
	this->updateModelMatrix();
}

void Model::setScale(D3DXVECTOR3 _scale)
{
	this->m_scale = _scale;
	this->updateModelMatrix();
}

void Model::setRotation(D3DXVECTOR3 _rotation)
{
	this->m_rotation = _rotation;
	this->updateModelMatrix();
}

void Model::updateModelMatrix()
{
	D3DXMATRIX rotationMatrix;
	D3DXMatrixRotationYawPitchRoll(&rotationMatrix, this->m_rotation.x, this->m_rotation.y, this->m_rotation.z);
	
	D3DXMATRIX scalingMatrix;
	D3DXMatrixScaling(&scalingMatrix, this->m_scale.x, this->m_scale.y, this->m_scale.z);

	this->m_modelMatrix = D3DXMATRIX(
		this->m_scale.x, 0.0f, 0.0f, 0.0f,
		0.0f, this->m_scale.y, 0.0f, 0.0f,
		0.0f, 0.0f, this->m_scale.z, 0.0f,
		this->m_position.x, this->m_position.y, this->m_position.z, 1.0f);
	
	D3DXMatrixMultiply(&this->m_modelMatrix, &scalingMatrix, &this->m_modelMatrix);
	D3DXMatrixMultiply(&this->m_modelMatrix, &rotationMatrix, &this->m_modelMatrix);
}

void Model::setPosition(FLOAT3 _position)
{
	this->m_position = D3DXVECTOR3(_position.x, _position.y, _position.z);
	this->updateModelMatrix();

	if(this->m_bs)
	{
		this->m_bs->Center = XMFLOAT3(this->m_position.x, this->m_position.y, this->m_position.z);
	}
	else
	{
		this->m_obb->Center = XMFLOAT3(this->m_position.x, this->m_position.y, this->m_position.z);
	}
}

void Model::setScale(float x, float y, float z)
{
	this->m_scale = D3DXVECTOR3(x, y, z);
	this->updateModelMatrix();
}

void Model::setRotation(float x, float y, float z)
{
	this->m_rotation = D3DXVECTOR3(x, y, z);
	this->updateModelMatrix();
}

void Model::setRotation(FLOAT3 _rotation)
{
	this->m_rotation = D3DXVECTOR3(_rotation.x, _rotation.y, _rotation.z);
	this->updateModelMatrix();
}