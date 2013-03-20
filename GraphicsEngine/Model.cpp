#include "Model.h"

Model::Model()
{
	this->m_obb = NULL;
	this->m_bs = NULL;
	this->animation = NULL;
	this->m_rightHand = NULL;
	this->m_leftHand = NULL;
	this->m_hat = NULL;
	this->m_weaponGlowIndex = "";
	this->m_glowAlpha = 1;
	m_static = false;
	m_neutral = false;
}

Model::Model(ID3D10Device* _device, Mesh* _mesh, Animation* _animation, D3DXVECTOR3 _position, D3DXVECTOR3 _scale, D3DXVECTOR3 _rotation, float _alpha, string _textureIndex, string _glowIndex)
{
	this->m_alpha = _alpha;
	this->m_mesh = _mesh;
	this->m_position = _position;
	this->m_scale = _scale;
	this->m_rotation = D3DXVECTOR3(_rotation.y, _rotation.x, _rotation.z);
	this->m_textureIndex = _textureIndex;
	this->m_glowIndex = _glowIndex;
	this->m_rightHand = NULL;
	this->m_leftHand = NULL;
	this->m_hat = NULL;
	this->m_glowAlpha = 1;
	this->m_shadow = true;

	if(_mesh->m_bs == NULL)
	{
		this->m_bs = NULL;
		this->m_obb = new BoundingOrientedBox(*_mesh->m_obb);
		this->m_obb->Center = XMFLOAT3(m_position.x + _mesh->m_obb->Center.x*_scale.x, m_position.y + _mesh->m_obb->Center.y*_scale.y, m_position.z + _mesh->m_obb->Center.z*_scale.z);
		this->m_obb->Extents.x *= _scale.x;
		this->m_obb->Extents.y *= _scale.y;
		this->m_obb->Extents.z *= _scale.z;
	}
	if(_mesh->m_obb == NULL)
	{
		this->m_bs = new BoundingSphere(*_mesh->m_bs);
		this->m_obb = NULL;
		this->m_bs->Center = XMFLOAT3(m_position.x + _mesh->m_bs->Center.x*_scale.x, m_position.y + _mesh->m_bs->Center.y*_scale.y, m_position.z + _mesh->m_bs->Center.z*_scale.z);

		float largestScale = _scale.x;
		if(_scale.y > largestScale)
			largestScale = _scale.y;
		if(_scale.z > largestScale)
			largestScale = _scale.z;
		this->m_bs->Radius *= largestScale;
	}
	
	this->updateModelMatrix();
	this->animation =  _animation;
	m_static = false;
	m_neutral = false;
	this->m_weaponGlowIndex = "glowIntensity3";
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

Mesh *Model::getHat() const
{
	return this->m_hat;
}

Mesh *Model::getLeftHand() const
{
	return this->m_leftHand;
}

Mesh *Model::getRightHand() const
{
	return this->m_rightHand;
}

Animation* Model::getAnimation()
{
	return this->animation;
}

FLOAT3 Model::getPosition()const
{
	return FLOAT3(this->m_position.x, this->m_position.y, this->m_position.z);
}

D3DXVECTOR3 Model::getRotation()const
{
	return this->m_rotation;
}

D3DXVECTOR2 Model::getPosition2D()const
{
	return D3DXVECTOR2(this->m_position.x, this->m_position.z);
}

FLOAT2 Model::getPosition2DAsFloat2()const
{
	return FLOAT2(m_position.x, m_position.z);
}

bool Model::isNeutral()const
{
	return m_neutral;
}

void Model::SetHat(Mesh* _hat)
{
	this->m_hat = _hat;
}

void Model::SetLeftHand(Mesh* _lHand)
{
	this->m_leftHand = _lHand;
}

void Model::SetRightHand(Mesh* _rHand)
{
	this->m_rightHand = _rHand;
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
	bool result;
	
	XMVECTOR origin = XMLoadFloat3(&XMFLOAT3(_origin.x, _origin.y, _origin.z));
	_direction = -_direction;
	XMVECTOR direction = XMLoadFloat3(&XMFLOAT3(_direction.x, _direction.y, _direction.z));

	if(this->m_obb)
	{
		result = this->m_obb->Intersects(origin, direction, _dist);
	}
	else if(this->m_bs)
		result = this->m_bs->Intersects(origin, direction, _dist);
	else
	{
		_dist = 0;
		result = false;
	}

	return result;
}

void Model::move(FLOAT3 _distance)
{
	this->m_position.x += _distance.x;
	this->m_position.y += _distance.y;
	this->m_position.z += _distance.z;
	this->updateModelMatrix();

	if(this->m_bs)
		this->m_bs->Center =
			XMFLOAT3(m_position.x + m_mesh->m_obb->Center.x*m_scale.x, m_position.y + m_mesh->m_obb->Center.y*m_scale.y, m_position.z + m_mesh->m_obb->Center.z*m_scale.z);
	else if(this->m_obb)
		this->m_obb->Center =
			XMFLOAT3(m_position.x + m_mesh->m_obb->Center.x*m_scale.x, m_position.y + m_mesh->m_obb->Center.y*m_scale.y, m_position.z + m_mesh->m_obb->Center.z*m_scale.z);
}

void Model::move(D3DXVECTOR3 _distance)
{
	m_position += _distance;
	this->updateModelMatrix();

	if(this->m_bs)
		this->m_bs->Center =
			XMFLOAT3(m_position.x + m_mesh->m_obb->Center.x*m_scale.x, m_position.y + m_mesh->m_obb->Center.y*m_scale.y, m_position.z + m_mesh->m_obb->Center.z*m_scale.z);
	else if(this->m_obb)
		this->m_obb->Center =
			XMFLOAT3(m_position.x + m_mesh->m_obb->Center.x*m_scale.x, m_position.y + m_mesh->m_obb->Center.y*m_scale.y, m_position.z + m_mesh->m_obb->Center.z*m_scale.z);
}

void Model::rotate(float _yaw, float _pitch, float _roll)
{
	m_rotation.x += _pitch;
	m_rotation.y += _yaw;
	m_rotation.z += _roll;

	updateModelMatrix();
}

void Model::setAlpha(float _alpha)
{
	this->m_alpha = _alpha;
}

void Model::setPosition(D3DXVECTOR3 _position)
{
	this->m_position = _position;

	if(this->m_bs)
	{
		this->m_bs->Center =
			XMFLOAT3(m_position.x + m_mesh->m_obb->Center.x*m_scale.x, m_position.y + m_mesh->m_obb->Center.y*m_scale.y, m_position.z + m_mesh->m_obb->Center.z*m_scale.z);
	}
	else
	{
		this->m_obb->Center =
			XMFLOAT3(m_position.x + m_mesh->m_obb->Center.x*m_scale.x, m_position.y + m_mesh->m_obb->Center.y*m_scale.y, m_position.z + m_mesh->m_obb->Center.z*m_scale.z);
	}

	this->updateModelMatrix();
}

void Model::setScale(D3DXVECTOR3 _scale)
{
	this->m_scale = _scale;
	this->updateModelMatrix();
}

void Model::setTextureIndex(string _textureIndex)
{
	m_textureIndex = _textureIndex;
}

void Model::setGlowIndex(string _glowIndex)
{
	m_glowIndex = _glowIndex;
}

void Model::setWeaponGlowIndex(string _glowIndex)
{
	m_weaponGlowIndex = _glowIndex;
}

void Model::Update(float dt)
{
	this->animation->Update(dt);
}

void Model::updateModelMatrix()
{
	D3DXMATRIX rotationMatrix;
	D3DXMatrixRotationYawPitchRoll(&rotationMatrix, m_rotation.y, m_rotation.x, this->m_rotation.z);

	this->m_modelMatrix = D3DXMATRIX(
		this->m_scale.x, 0.0f, 0.0f, 0.0f,
		0.0f, this->m_scale.y, 0.0f, 0.0f,
		0.0f, 0.0f, this->m_scale.z, 0.0f,
		this->m_position.x, this->m_position.y, this->m_position.z, 1.0f);
	
	D3DXMatrixMultiply(&this->m_modelMatrix, &rotationMatrix, &this->m_modelMatrix);
	
	if(this->m_obb)
	{
		XMVECTOR rot = XMQuaternionRotationRollPitchYaw(m_rotation.x, m_rotation.y, m_rotation.z);
		XMVECTOR trans = XMLoadFloat3(&XMFLOAT3(0,0,0));
		
		//XMMATRIX Fucker = XMMatrixRotationQuaternion(XMQuaternionRotationRollPitchYaw(m_rotation.x, m_rotation.y, m_rotation.z));
		XMFLOAT3 temp = m_obb->Center;
		m_obb->Center = XMFLOAT3(0.0f, 0.0f, 0.0f);
		XMStoreFloat4(&this->m_obb->Orientation, XMQuaternionIdentity());
		BoundingOrientedBox box;
		//this->m_obb->Transform(box, Fucker);
		this->m_obb->Transform(box, 1.0f, rot, trans);
		delete m_obb;
		this->m_obb = new BoundingOrientedBox(box);
		m_obb->Center = temp;
	}
}

void Model::setPosition(FLOAT3 _position)
{
	this->m_position = D3DXVECTOR3(_position.x, _position.y, _position.z);

	if(this->m_bs)
	{
		this->m_bs->Center =
			XMFLOAT3(m_position.x + m_mesh->m_bs->Center.x*m_scale.x, m_position.y + m_mesh->m_bs->Center.y*m_scale.y, m_position.z + m_mesh->m_bs->Center.z*m_scale.z);
	}
	else
	{
		this->m_obb->Center =
			XMFLOAT3(m_position.x + m_mesh->m_obb->Center.x*m_scale.x, m_position.y + m_mesh->m_obb->Center.y*m_scale.y, m_position.z + m_mesh->m_obb->Center.z*m_scale.z);
	}

	this->updateModelMatrix();
}

void Model::setScale(float x, float y, float z)
{
	this->m_scale = D3DXVECTOR3(x, y, z);
	this->updateModelMatrix();
}

void Model::setRotation(FLOAT3 _rotation)
{
	this->m_rotation = D3DXVECTOR3(_rotation.y, _rotation.x, _rotation.z);
	this->updateModelMatrix();
}

void Model::setStatic(bool _static)
{
	m_static = _static;
}

FLOAT3 Model::getLeftHandPosition()
{
	if(this->m_leftHand != NULL)
	{
		D3DXVECTOR4 result;
		D3DXMATRIX leftHandModelMatrix;

		D3DXMatrixMultiply(&leftHandModelMatrix, this->animation->getLeftHandMatrix(), &this->m_modelMatrix);

		D3DXVec3Transform(&result, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &leftHandModelMatrix);
		return FLOAT3(result.x, result.y, result.z);
	}
	else
	{
		return FLOAT3(this->m_position.x, this->m_position.y, this->m_position.z);
	}
}

FLOAT3 Model::getRightHandPosition()
{
	if(this->m_rightHand != NULL)
	{
		D3DXVECTOR4 result;
		D3DXMATRIX rightHandModelMatrix;

		D3DXMatrixMultiply(&rightHandModelMatrix, this->animation->getRightHandMatrix(), &this->m_modelMatrix);

		D3DXVec3Transform(&result, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &rightHandModelMatrix);
		return FLOAT3(result.x, result.y, result.z);
	}
	else
	{
		return FLOAT3(this->m_position.x, this->m_position.y, this->m_position.z);
	}
}

void Model::setShadow(bool _shadow)
{
	this->m_shadow = _shadow;
}

bool Model::getShadow()
{
	return this->m_shadow;
}

void Model::neutralize()
{
	m_neutral = true;
}

FLOAT2 Model::getScreenPos(D3DXMATRIX viewProjectionMatrix)
{
	D3DXVECTOR4 screenPos;
	D3DXVec3Transform(&screenPos, &this->getPosition().toD3DXVector(), &viewProjectionMatrix);

	return FLOAT2(screenPos.x / screenPos.w, screenPos.y / screenPos.w);
}

void Model::setColor(D3DXVECTOR4 color)
{
	this->m_stencilColor = color;
}

void Model::setGlowAlpha(float _glowAlpha)
{
	this->m_glowAlpha = _glowAlpha;
}

float Model::getGlowAlpha()
{
	return this->m_glowAlpha;
}