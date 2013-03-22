#ifndef CURSOR_H
#define CURSOR_H

#include "Graphics.h"
#include "SpriteSheet.h"

class Cursor
{
private:
	SpriteSheet *m_sprite;
	int m_priority;
public:
	static enum CURSOR_TYPE{DEFAULT, TARGET, CLICK, CHAIN_STRIKE, CLOUD_OF_DARKNESS, TELEPORT, HEALING_TOUCH, WALL, HYPNOTIC_STARE, CAT_BEAR, TARGET_ACQUIRED, TIME_IS_MONEY};

	Cursor();
	~Cursor();
	void setPosition(INT2 position);
	void setFrame(CURSOR_TYPE cursor, int _priority);
	void setPriority(int _priority);
};

#endif