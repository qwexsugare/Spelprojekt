#pragma once

#include "stdafx.h"
#include "DataStructures.h"

class Text
{
private:
	ID3DX10Font* m_font;
	string m_str;
	INT2 m_position;
public:
	Text();
	Text(ID3DX10Font* _font, string _str, INT2 _position);
	~Text();

	void render();
};