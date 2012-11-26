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

	D3DXMatrixLookAtLH(&this->m_viewMatrix, &this->m_position, &this->m_forward, &this->m_up);
	D3DXMatrixPerspectiveLH(&this->m_projectionMatrix, (float)D3DX_PI * 0.6f, (float)(width / height), 1.0f, 1000.0f);
}

Camera::~Camera()
{

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
	D3DXMatrixLookAtLH(&this->m_viewMatrix, &this->m_position, &this->m_forward, &this->m_up);
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

}