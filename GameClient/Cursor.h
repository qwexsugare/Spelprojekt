#ifndef CURSOR_H
#define CURSOR_H

#include "Graphics.h"
#include "SpriteSheet.h"

class Cursor
{
private:
	SpriteSheet *m_sprite;
public:
	Cursor();
	void setPosition(INT2 position);
	void setFrame(int i);
};

#endif