#ifndef CAMERA_H
#define CAMERA_H

#include "stdafx.h"
#include "DataStructures.h"

class Camera
{
private:
	D3DXVECTOR3 m_position;
	D3DXVECTOR3 m_forward;
	D3DXVECTOR3 m_up;
	D3DXVECTOR3 m_right;
	D3DXMATRIX m_viewMatrix;
	D3DXMATRIX m_projectionMatrix;
	int m_width;
	int m_height;
	INT2 m_otherScreenSize;
public:
	Camera();
	Camera(int width, int height, INT2 _otherScreenSize);
	~Camera();

	DECLDIR void calcPick(D3DXVECTOR3& _pickDirOut, D3DXVECTOR3& _pickOrigOut, INT2 _mousePos);
	
	DECLDIR D3DXVECTOR3 getPos()const;
	DECLDIR D3DXVECTOR2 getPos2D()const;
	D3DXMATRIX getViewMatrix();
	D3DXMATRIX getProjectionMatrix();

	void updateViewMatrix();

	DECLDIR void moveRelative(float forward, float right, float up);	//Move based on the forward vector
	DECLDIR void moveStatic(float forward, float right, float up);
	DECLDIR void rotate(float x, float y, float z);
	DECLDIR void set(FLOAT3 _position, FLOAT3 _forward, FLOAT3 _up, FLOAT3 _right);
};

#endif

