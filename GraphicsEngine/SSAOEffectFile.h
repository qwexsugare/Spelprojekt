#pragma once
#include "effectfile.h"

class SSAOEffectFile : public EffectFile
{
private:
	ID3D10EffectShaderResourceVariable* m_depthTexture;
	ID3D10EffectTechnique *m_techniqueVert;
	ID3D10EffectTechnique *m_techniqueHori;
	ID3D10EffectTechnique *m_technique;
	ID3D10InputLayout *m_vertexLayout;
public:
	SSAOEffectFile();
	SSAOEffectFile(ID3D10Device* _device);
	~SSAOEffectFile();

	ID3D10EffectTechnique *getTechniqueVert();
	ID3D10EffectTechnique *getTechniqueHori();
	ID3D10EffectTechnique *getTechnique();
};