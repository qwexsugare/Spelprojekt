#pragma once

#include "stdafx.h"
#include "Mesh.h"
#include "DataStructures.h"
#include <DirectXMath.h>
#include <DirectXCollision.h>
#include "Animation.h"
using namespace DirectX;

class Model
{
private:
	Mesh* m_mesh;
	Mesh* m_hat;
	Mesh* m_leftHand;
	Mesh* m_rightHand;
	D3DXMATRIX m_modelMatrix;
	D3DXVECTOR3 m_position;
	D3DXVECTOR3 m_scale;
	D3DXVECTOR3 m_rotation;
	float m_alpha;
	BoundingOrientedBox* m_obb;
	BoundingSphere* m_bs;
	Animation* animation;
	string m_textureIndex;
	string m_glowIndex;
	bool m_static;
	bool m_shadow;
	bool m_neutral;

	D3DXVECTOR3 m_screenPosition;
public:
	Model();
	Model(ID3D10Device* _device, Mesh* _mesh, Animation* _animation, D3DXVECTOR3 _position,
		D3DXVECTOR3 _scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f), D3DXVECTOR3 _rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		float _alpha = 1.0f, string _textureIndex = "color", string _glowIndex = "");
	~Model();
	
	DECLDIR float getAlpha()const;
	DECLDIR BoundingOrientedBox* getObb()const;
	BoundingSphere* getBs()const { return this->m_bs; }
	DECLDIR FLOAT3 getPosition()const;
	D3DXVECTOR2 getPosition2D()const;
	DECLDIR FLOAT2 getPosition2DAsFloat2()const;
	D3DXVECTOR3 getScale()const;
	D3DXVECTOR3 getRotation()const;
	DECLDIR Mesh* getMesh()const;
	DECLDIR Mesh* getHat()const;
	DECLDIR Mesh* getLeftHand()const;
	DECLDIR Mesh* getRightHand()const;
	string getTextureIndex()const { return m_textureIndex; }
	string getGlowIndex()const { return m_glowIndex; }
	bool isNeutral()const;
	D3DXMATRIX getModelMatrix()const { return this->m_modelMatrix; }
	DECLDIR void SetHat(Mesh* _hat);
	DECLDIR void SetLeftHand(Mesh* _lHand);
	DECLDIR void SetRightHand(Mesh* _rHand);
	void Update(float dt);
	DECLDIR Animation* getAnimation();
	DECLDIR bool contains(const BoundingOrientedBox& _obb)const;
	DECLDIR bool contains(const BoundingSphere& _bs)const;
	DECLDIR bool intersects(const BoundingOrientedBox& _obb)const;
	DECLDIR bool intersects(const BoundingSphere& _bs)const;
	DECLDIR bool intersects(float& _dist, D3DXVECTOR3 _origin, D3DXVECTOR3 _direction)const;
	DECLDIR bool isStatic()const { return m_static; }
	DECLDIR void move(FLOAT3 _distance);
	DECLDIR void move(D3DXVECTOR3 _distance);
	DECLDIR void rotate(float _yaw, float _pitch, float _roll);
	DECLDIR void setAlpha(float _alpha);
	DECLDIR void setPosition(D3DXVECTOR3 _position);
	DECLDIR void setScale(D3DXVECTOR3 _scale);
	DECLDIR void setTextureIndex(string _textureIndex);
	DECLDIR void setGlowIndex(string _glowIndex);
	void updateModelMatrix();

	DECLDIR void setPosition(FLOAT3 _position);
	DECLDIR void setScale(float x, float y, float z);
	DECLDIR void setRotation(FLOAT3 _rotation);
	DECLDIR void setStatic(bool _static);
	DECLDIR void setShadow(bool _shadow);
	bool getShadow();

	DECLDIR FLOAT3 getLeftHandPosition();
	DECLDIR FLOAT3 getRightHandPosition();
	DECLDIR void neutralize(); //Don't draw model behind buildings
	DECLDIR FLOAT2 getScreenPos(D3DXMATRIX viewProjectionMatrix);
};