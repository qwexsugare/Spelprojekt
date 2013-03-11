#pragma once

#include "ParticleEffect.h"
#include <fstream>

class ParticleEffectImporter
{
private:

public:
	static ParticleEffect* loadParticleEffect(string _filename);
};