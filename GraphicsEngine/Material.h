//*****************
//	- 16-12-12 - Anders och Alve -
//	- Created
//
//*****************
#pragma once

#include "stdafx.h"

struct Material
{
	map<string, ID3D10ShaderResourceView*> textures;

	Material()
	{

	}
	~Material()
	{

	}
};