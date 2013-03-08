#include "EffectFile.h"

EffectFile::EffectFile()
{
	this->m_effect = NULL;
}

EffectFile::EffectFile(ID3D10Device* _device, string _filename)
{
	DWORD dwShaderFlags = D3D10_SHADER_ENABLE_BACKWARDS_COMPATIBILITY;
	HRESULT hr = D3DX10CreateEffectFromFile(_filename.c_str(), NULL, NULL, "fx_4_0", dwShaderFlags, 0, _device, NULL, NULL, &this->m_effect, NULL, NULL);
	if(FAILED(hr))
	{
		MessageBox(0, "Error compiling shader!", "Shader error!", 0);
	}
	hr;
}

EffectFile::EffectFile(ID3D10Device* _device, string _filename, bool fisk)
{
	DWORD dwShaderFlags = D3D10_SHADER_ENABLE_STRICTNESS;
	HRESULT hr = D3DX10CreateEffectFromFile(_filename.c_str(), NULL, NULL, "fx_4_0", dwShaderFlags, 0, _device, NULL, NULL, &this->m_effect, NULL, NULL);
	if(FAILED(hr))
	{
		MessageBox(0, "Error compiling shader!", "Shader error!", 0);
	}
	hr;
}

EffectFile::~EffectFile()
{
	if(this->m_effect)
	{
		this->m_effect->Release();
	}
}