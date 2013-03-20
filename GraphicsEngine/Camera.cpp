#include "Camera.h"

Camera::Camera()
{

}

Camera::Camera(INT2 _configScreenSize, INT2 _actualScreenSize)
{
	this->m_configScreenSize = _configScreenSize;
	this->m_actualScreenSize = _actualScreenSize;
	this->m_position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	this->m_forward = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	this->m_up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	this->m_right = D3DXVECTOR3(1.0f, 0.0f, 0.0f);

	this->updateViewMatrix();
	D3DXMatrixPerspectiveFovLH(&this->m_projectionMatrix, D3DX_PI/4.0f,  float(m_configScreenSize.x) / float(m_configScreenSize.y), 0.1f, 1000000.0f);
	
	m_xOffset = 6.0f; // 8.8f;
	m_zOffset = 4.0f; // 5.86f;
}

Camera::~Camera()
{

}

void Camera::calcPick(D3DXVECTOR3& _pickDirOut, D3DXVECTOR3& _pickOrigOut, INT2 _mousePos)
{
	// Do stuff in a retard right handed world
	D3DXMATRIX rhProjMat;
	D3DXMatrixPerspectiveFovRH(&rhProjMat, D3DX_PI/4.0f,  float(m_configScreenSize.x) / float(m_configScreenSize.y), 0.1f, 1000000.0f);
	D3DXMATRIX rhViewMat;
	D3DXMatrixLookAtRH(&rhViewMat, &this->m_position, &(this->m_forward + this->m_position), &this->m_up);

	// Compute the vector of the pick ray in screen space
	D3DXVECTOR3 v;
	v.x = ( ( ( 2.0f * float(_mousePos.x)) / float(m_configScreenSize.x) ) - 1.0f ) / rhProjMat._11;
	v.y = ( ( ( 2.0f * float(_mousePos.y) ) / float(m_configScreenSize.y) ) - 1.0f ) / rhProjMat._22;
	v.z = 1.0f;

	// Get the inverse view matrix
	D3DXMATRIX m;
	D3DXMatrixInverse(&m, NULL, &rhViewMat);

	// Transform the screen space pick ray into 3D space
	_pickDirOut.x = v.x * m._11 + v.y * m._21 + v.z * m._31;
	_pickDirOut.y = v.x * m._12 + v.y * m._22 + v.z * m._32;
	_pickDirOut.z = v.x * m._13 + v.y * m._23 + v.z * m._33;
	D3DXVec3Normalize(&_pickDirOut, &_pickDirOut);
	_pickOrigOut.x = m._41;
	_pickOrigOut.y = m._42;
	_pickOrigOut.z = m._43;
}

float Camera::getXOffset()const
{
	return m_xOffset;
}

float Camera::getZOffset()const
{
	return m_zOffset;
}

const D3DXVECTOR3& Camera::getPos()const
{
	return this->m_position;
}

FLOAT2 Camera::getPos2D()const
{
	return FLOAT2(this->m_position.x, this->m_position.z);
}

D3DXMATRIX Camera::getViewMatrix()
{
	return this->m_viewMatrix;
}

D3DXMATRIX Camera::getProjectionMatrix()
{
	return this->m_projectionMatrix;
}

void Camera::updateViewMatrix()
{
	D3DXMatrixLookAtLH(&this->m_viewMatrix, &this->m_position, &(this->m_position+m_forward), &this->m_up);
	D3DXMatrixMultiply(&this->m_viewProjectionMatrix, &this->m_viewMatrix, &this->m_projectionMatrix);
}

void Camera::moveY(float _val)
{
	m_position.y += _val;
	m_xOffset += _val*0.8f;
	m_zOffset += _val*0.53f;
	this->updateViewMatrix();
}

void Camera::moveRelative(float forward, float right, float up)
{
	this->m_position = this->m_position + forward * this->m_forward;
	this->m_position = this->m_position + right * this->m_right;
	this->m_position = this->m_position + up * this->m_up;
}

void Camera::moveStatic(float forward, float right, float up)
{
	this->m_position.x = this->m_position.x + right;
	this->m_position.y = this->m_position.y + up;
	this->m_position.z = this->m_position.z + forward;
}

void Camera::rotate(float x, float y, float z)
{
	D3DXMATRIX rotationMatrix;
	D3DXMatrixRotationYawPitchRoll(&rotationMatrix, x, y, z);

	D3DXVECTOR4 tmp;
	D3DXVec3Transform(&tmp, &this->m_up, &rotationMatrix);
	this->m_up = D3DXVECTOR3(tmp.x, tmp.y, tmp.z);
	D3DXVec3Transform(&tmp, &this->m_right, &rotationMatrix);
	this->m_right = D3DXVECTOR3(tmp.x, tmp.y, tmp.z);
	D3DXVec3Transform(&tmp, &this->m_forward, &rotationMatrix);
	this->m_forward = D3DXVECTOR3(tmp.x, tmp.y, tmp.z);
}

void Camera::set(FLOAT3 _position, FLOAT3 _forward, FLOAT3 _up, FLOAT3 _right)
{
	this->m_position = D3DXVECTOR3(_position.x, _position.y, _position.z);
	this->m_forward = D3DXVECTOR3(_forward.x, _forward.y, _forward.z);
	this->m_up = D3DXVECTOR3(_up.x, _up.y, _up.z);
	this->m_right = D3DXVECTOR3(_right.x, _right.y, _right.z);
	this->updateViewMatrix();
}

void Camera::set(FLOAT2 _position)
{
	this->m_position.x = _position.x;
	this->m_position.z = _position.y;
	this->updateViewMatrix();
}

void Camera::setX(float _x)
{
	this->m_position.x = _x;
	this->updateViewMatrix();
}

void Camera::setZ(float _z)
{
	this->m_position.z = _z;
	this->updateViewMatrix();
}

D3DXMATRIX Camera::getViewProjectionMatrix()
{
	return this->m_viewProjectionMatrix;
}