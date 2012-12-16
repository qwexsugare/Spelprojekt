//*****************
//	- 12-12-12 - Anders -
//	- Created
//	- 
//*****************

#pragma once

#include "stdafx.h"

struct SubMesh
{
	ID3D10Buffer* buffer;

	SubMesh()
	{

	}
	~SubMesh()
	{
		buffer->Release();
	}
};