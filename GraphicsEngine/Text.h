#pragma once

#include "stdafx.h"
#include "DataStructures.h"

class DECLDIR Text
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
	void setString(string _str);
};