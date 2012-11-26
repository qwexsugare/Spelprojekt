#ifndef CAMERA_H
#define CAMERA_H

#include "stdafx.h"

class Camera
{
private:
	D3DXVECTOR3 m_position;
	D3DXVECTOR3 m_forward;
	D3DXVECTOR3 m_up;
	D3DXVECTOR3 m_right;
	D3DXMATRIX m_viewMatrix;
	D3DXMATRIX m_projectionMatrix;

public:
	Camera();
	Camera(float width, float height);
	~Camera();

	D3DXMATRIX getViewMatrix();
	D3DXMATRIX getProjectionMatrix();

	void updateViewMatrix();

	void moveRelative(float forward, float right, float up);	//Move based on the forward vector
	void moveStatic(float forward, float right, float up);
	void rotate(float x, float y, float z);
};

#endif

