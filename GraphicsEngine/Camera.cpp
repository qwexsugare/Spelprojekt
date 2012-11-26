#include "Camera.h"

Camera::Camera()
{

}

Camera::Camera(float width, float height)
{
	this->m_position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	this->m_forward = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	this->m_up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

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