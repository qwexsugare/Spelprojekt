#pragma once

#include <math.h>

struct WUFLOAT2
{
	float x;
	float y;

	WUFLOAT2()
	{

	}

	WUFLOAT2(float _x, float _y)
	{
		this->x = _x;
		this->y = _y;
	}

	WUFLOAT2 operator+(const WUFLOAT2& _k)const
	{
		return WUFLOAT2(x+_k.x, y+_k.y);
	}

	WUFLOAT2 operator-(const WUFLOAT2& _k)const
	{
		return WUFLOAT2(x-_k.x, y-_k.y);
	}

	WUFLOAT2 operator*(const WUFLOAT2& _k)const
	{
		return WUFLOAT2(x*_k.x, y*_k.y);
	}

	WUFLOAT2 operator/(const WUFLOAT2& _k)const
	{
		return WUFLOAT2(x/_k.x, y/_k.y);
	}

	template<typename T>
	WUFLOAT2 operator*(const T& _k)const
	{
		return WUFLOAT2(x*_k, y*_k);
	}
};

struct WUFLOAT3
{
	float x;
	float y;
	float z;

	WUFLOAT3()
	{

	}

	WUFLOAT3(float _x, float _y, float _z)
	{
		this->x = _x;
		this->y = _y;
		this->z = _z;
	}

	WUFLOAT3 operator+(const WUFLOAT3& _k)const
	{
		return WUFLOAT3(x+_k.x, y+_k.y, z+_k.z);
	}

	WUFLOAT3 operator-(const WUFLOAT3& _k)const
	{
		return WUFLOAT3(x-_k.x, y-_k.y, z-_k.z);
	}

	template<typename T>
	WUFLOAT3 operator*(const T& _k)const
	{
		return WUFLOAT3(x*_k, y*_k, z*_k);
	}

	template<typename T>
	WUFLOAT3 operator/(const T& _k)const
	{
		return WUFLOAT3(x/_k, y/_k, z/_k);
	}

	float length()const
	{
		return sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
	}

	float lengthSquared()const
	{
		return this->x * this->x + this->y * this->y + this->z * this->z;
	}
};

struct WUINT2
{
	int x;
	int y;

	WUINT2()
	{

	}

	WUINT2(int _x, int _y)
	{
		this->x = _x;
		this->y = _y;
	}
};

struct WUINT3
{
	int x;
	int y;
	int z;

	WUINT3()
	{

	}

	WUINT3(int _x, int _y,  int _z)
	{
		this->x = _x;
		this->y = _y;
		this->z = _z;
	}
};


