#pragma once

#include "stdafx.h"
#include "DataStructures.h"

class Text
{
private:
	ID3DX10Font* m_font;
	string m_str;
	FLOAT2 m_pos;
	D3DXCOLOR m_color;
public:
	Text();
	Text(ID3DX10Font* _font, string _str, INT2 _pos, D3DXCOLOR _color);
	~Text();

	DECLDIR void move(FLOAT2 _distance);
	void render();
	DECLDIR void setPos(INT2 _pos);
	DECLDIR void setString(string _str);
};