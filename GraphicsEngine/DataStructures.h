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


