#include "Text.h"

Text::Text()
{

}

Text::Text(ID3DX10Font* _font, string _str, INT2 _pos, D3DXCOLOR _color)
{
	this->m_font = _font;
	this->m_str = _str;
	this->m_pos.x = _pos.x;
	this->m_pos.y = _pos.y;
	this->m_color = _color;
}

Text::~Text()
{

}

void Text::move(FLOAT2 _distance)
{
	this->m_pos.x += _distance.x;
	this->m_pos.y += _distance.y;
}

void Text::render()
{
	RECT rc;
	rc.left = this->m_pos.x;
	rc.right = this->m_pos.x+1000;
	rc.top = this->m_pos.y;
	rc.bottom = this->m_pos.y+1000;

	this->m_font->DrawTextA(NULL, this->m_str.c_str(), -1, &rc, DT_NOCLIP, this->m_color);
}

void Text::setPos(INT2 _pos)
{
	this->m_pos.x = _pos.x;
	this->m_pos.y = _pos.y;
}

void Text::setString(string _str)
{
	this->m_str = _str;
}