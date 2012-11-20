#pragma once

#include "stdafx.h"
#include <map>

class TextureHolder
{
private:
	map<string, ID3D10ShaderResourceView*> m_textures;
	ID3D10Device *m_device;

public:
	TextureHolder(ID3D10Device *_device);
	~TextureHolder(void);

	ID3D10ShaderResourceView* getTexture(string filename);
};

