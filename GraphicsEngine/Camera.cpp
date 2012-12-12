#include "Camera.h"

Camera::Camera()
{

}

Camera::Camera(float width, float height)
{
	this->m_position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	this->m_forward = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	this->m_up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	this->m_right = D3DXVECTOR3(1.0f, 0.0f, 0.0f);

	D3DXMatrixLookAtLH(&this->m_viewMatrix, &this->m_position, &(this->m_forward + this->m_position), &this->m_up);
	D3DXMatrixPerspectiveLH(&this->m_projectionMatrix, (float)D3DX_PI * 0.8f /* 0.6f? */, (float)(width / height), 1.0f, 1000.0f);
}

Camera::~Camera()
{

}

D3DXVECTOR3 Camera::getPos()const
{
	return this->m_position;
}

D3DXVECTOR2 Camera::getPos2D()const
{
	return D3DXVECTOR2(this->m_position.x, this->m_position.z);
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
	D3DXMatrixLookAtLH(&this->m_viewMatrix, &this->m_position, &(this->m_forward + this->m_position), &this->m_up);
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

	D3DXMatrixLookAtLH(&this->m_viewMatrix, &this->m_position, &(this->m_forward + this->m_position), &this->m_up);
}