#pragma once

#include "stdafx.h"

class EffectFile
{
protected:
	ID3D10Effect* m_effect;
public:
	EffectFile();
	EffectFile(ID3D10Device* _device, string _filename);
	//For Anders's's's's's Particles
	EffectFile(ID3D10Device* _device, string _filename, bool fisk);
	~EffectFile();
};