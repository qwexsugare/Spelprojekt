#pragma once

#include "stdafx.h"
#include <map>
#include "TexturePack.h"

#define MAX_BONES 100


class TextureHolder
{
private:
	map<string, ID3D10ShaderResourceView*> m_textures;
	map<string, TexturePack> m_boneTextures;
	ID3D10Device *m_device;

public:
	TextureHolder(ID3D10Device *_device);
	~TextureHolder(void);

	ID3D10ShaderResourceView* getTexture(string filename);
	TexturePack* getBoneTexture();
};

