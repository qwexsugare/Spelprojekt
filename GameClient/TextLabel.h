#pragma once

#include "MyText.h"

class TextLabel
{
private:
	string m_text;
	MyText* m_myText;
public:
	TextLabel();
	TextLabel(string _text, string _texture, INT2 _pos, int _size);
	~TextLabel();

	void setText(string _text);
};