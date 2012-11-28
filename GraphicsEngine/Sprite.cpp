#include "Sprite.h"

Sprite::Sprite(D3DXVECTOR2 position, D3DXVECTOR2 size,ID3D10ShaderResourceView *_texture)
{
	this->m_sprite.TexCoord = D3DXVECTOR2(0.0f, 0.0f);
	this->m_sprite.TexSize = D3DXVECTOR2(1.0f, 1.0f);
	this->m_sprite.pTexture = _texture;
	this->m_sprite.TextureIndex = 0;

	D3DXMatrixTransformation2D(&this->m_sprite.matWorld, &D3DXVECTOR2(0, 0), 0, &D3DXVECTOR2(32, 32), &D3DXVECTOR2(0, 0), 0, &D3DXVECTOR2(48, 48));
}

Sprite::~Sprite()
{

}

D3DX10_SPRITE Sprite::getSprite()
{
	return this->m_sprite;
}