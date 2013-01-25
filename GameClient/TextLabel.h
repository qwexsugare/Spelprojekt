#pragma once

#include "MyText.h"
#include <sstream>
class TextLabel
{
private:
	string m_text;
	MyText* m_myText;
public:
	TextLabel();
	TextLabel(string _text, string _texture, INT2 _pos, int _size);
	~TextLabel();

	string IntToString(int intInput);
	string getText();
	void setText(string _text);
};