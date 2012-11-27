#include "Text.h"

Text::Text()
{

}

Text::Text(ID3DX10Font* _font, string _str, INT2 _position)
{
	this->m_font = _font;
	this->m_str = _str;
	this->m_position = _position;
}

Text::~Text()
{

}

void Text::render()
{
	RECT rc;
	rc.left = this->m_position.x;
	rc.right = this->m_position.x+1000;
	rc.top = this->m_position.y;
	rc.bottom = this->m_position.y+1000;

	this->m_font->DrawTextA(NULL, this->m_str.c_str(), -1, &rc, DT_NOCLIP, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
}