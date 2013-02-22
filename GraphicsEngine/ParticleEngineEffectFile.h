#pragma once
#include "effectfile.h"

class ParticleEngineEffectFile : public EffectFile
{
private:
	ID3D10EffectShaderResourceVariable* m_texture;
	ID3D10EffectTechnique *m_streamOutTechnique;
	ID3D10EffectTechnique *m_drawAddBlendTechnique;
	ID3D10InputLayout *m_vertexLayout;
public:
	ParticleEngineEffectFile();
	ParticleEngineEffectFile(ID3D10Device* _device);
	~ParticleEngineEffectFile();
	
	ID3D10EffectTechnique *getStreamOutTechnique();
	ID3D10EffectTechnique *getDrawAddBlendTechnique();

	void setTexture(ID3D10ShaderResourceView* _texture);
};