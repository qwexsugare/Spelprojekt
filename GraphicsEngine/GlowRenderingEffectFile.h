#pragma once
#include "effectfile.h"

class GlowRenderingEffectFile : public EffectFile
{
private:
	ID3D10EffectShaderResourceVariable* m_glowTexture;
	ID3D10EffectTechnique *m_techniqueVert;
	ID3D10EffectTechnique *m_techniqueHori;
	ID3D10EffectTechnique *m_technique;
	ID3D10InputLayout *m_vertexLayout;
public:
	GlowRenderingEffectFile();
	GlowRenderingEffectFile(ID3D10Device* _device);
	~GlowRenderingEffectFile();

	ID3D10EffectTechnique *getTechniqueVert();
	ID3D10EffectTechnique *getTechniqueHori();
	ID3D10EffectTechnique *getTechnique();

	void setGlowTexture(ID3D10ShaderResourceView* _glowTexture);
};