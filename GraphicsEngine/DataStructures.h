#pragma once
#include "stdafx.h"

struct DECLDIR FLOAT2
{
	float x;
	float y;

	FLOAT2()
	{

	}

	FLOAT2(float _x, float _y)
	{
		this->x = _x;
		this->y = _y;
	}

	FLOAT2 operator+(const FLOAT2& _k)const
	{
		return FLOAT2(x+_k.x, y+_k.y);
	}

	FLOAT2 operator-(const FLOAT2& _k)const
	{
		return FLOAT2(x-_k.x, y-_k.y);
	}

	FLOAT2 operator*(const FLOAT2& _k)const
	{
		return FLOAT2(x*_k.x, y*_k.y);
	}

	FLOAT2 operator/(const FLOAT2& _k)const
	{
		return FLOAT2(x/_k.x, y/_k.y);
	}

	template<typename T>
	FLOAT2 operator*(const T& _k)const
	{
		return FLOAT2(x*_k, y*_k);
	}

	D3DXVECTOR2 toD3DXVector()
	{
		return D3DXVECTOR2(this->x, this->y);
	}
};

struct DECLDIR FLOAT3
{
	float x;
	float y;
	float z;

	FLOAT3()
	{

	}

	FLOAT3(float _x, float _y, float _z)
	{
		this->x = _x;
		this->y = _y;
		this->z = _z;
	}

	FLOAT3 operator+(const FLOAT3& _k)const
	{
		return FLOAT3(x+_k.x, y+_k.y, z+_k.z);
	}

	FLOAT3 operator-(const FLOAT3& _k)const
	{
		return FLOAT3(x-_k.x, y-_k.y, z-_k.z);
	}
	bool operator==(const FLOAT3& _k)const
	{
		return (x==_k.x&& y==_k.y&& z==_k.z);
	}
	bool operator!=(const FLOAT3& _k)const
	{
		return (x!=_k.x&& y!=_k.y&& z!=_k.z);
	}

	template<typename T>
	FLOAT3 operator*(const T& _k)const
	{
		return FLOAT3(x*_k, y*_k, z*_k);
	}

	template<typename T>
	FLOAT3 operator/(const T& _k)const
	{
		return FLOAT3(x/_k, y/_k, z/_k);
	}

	float length()const
	{
		return sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
	}

	float lengthSquared()const
	{
		return this->x * this->x + this->y * this->y + this->z * this->z;
	}

	D3DXVECTOR3 toD3DXVector()
	{
		return D3DXVECTOR3(this->x, this->y, this->z);
	}
};

struct DECLDIR FLOAT4
{
	float x;
	float y;
	float z;
	float w;

	FLOAT4()
	{

	}

	FLOAT4(float _x, float _y, float _z, float _w)
	{
		this->x = _x;
		this->y = _y;
		this->z = _z;
		this->w = _w;
	}

	FLOAT4 operator+(const FLOAT4& _k)
	{
		return FLOAT4(x+_k.x, y+_k.y, z+_k.z, w+_k.w);
	}

	FLOAT4 operator-(const FLOAT4& _k)
	{
		return FLOAT4(x-_k.x, y-_k.y, z-_k.z, w-_k.w);
	}

	template<typename T>
	FLOAT4 operator*(const T& _k)
	{
		return FLOAT4(x*_k, y*_k, z*_k, w*_k);
	}

	template<typename T>
	FLOAT4 operator/(const T& _k)
	{
		return FLOAT4(x/_k, y/_k, z/_k, w/_k);
	}

	float length()
	{
		return sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
	}

	D3DXVECTOR4 toD3DXVector()
	{
		return D3DXVECTOR4(this->x, this->y, this->z, this->w);
	}
};

struct DECLDIR INT2
{
	int x;
	int y;

	INT2()
	{

	}

	INT2(int _x, int _y)
	{
		this->x = _x;
		this->y = _y;
	}
};

struct DECLDIR INT3
{
	int x;
	int y;
	int z;

	INT3()
	{

	}

	INT3(int _x, int _y,  int _z)
	{
		this->x = _x;
		this->y = _y;
		this->z = _z;
	}
};


