#pragma once

#include "stdafx.h"
#include "DataStructures.h"

class DECLDIR Text
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

	void move(FLOAT2 _distance);
	void render();
	void setPos(INT2 _pos);
	void setString(string _str);
};