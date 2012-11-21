#pragma once

#include "stdafx.h"

class EffectFile
{
protected:
	ID3D10Effect* m_effect;
public:
	EffectFile();
	EffectFile(ID3D10Device* _device, string _filename);
	~EffectFile();
};