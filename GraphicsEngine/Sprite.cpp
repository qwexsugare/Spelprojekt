#include "Sprite.h"

Sprite::Sprite(ID3D10Device *device, D3DXVECTOR2 position, D3DXVECTOR2 size,ID3D10Texture2D *_texture)
{
	D3DX10CreateSprite(device, 50, this->m_sprite);
}

Sprite::~Sprite()
{

}
