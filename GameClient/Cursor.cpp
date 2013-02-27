#include "Cursor.h"

Cursor::Cursor()
{
	this->m_sprite = g_graphicsEngine->createSpriteSheet("menu_textures\\MouseCursor.png", FLOAT2(0.0f, 0.0f), FLOAT2(0.075f, 0.15f), INT2(3, 4), 20);
}

void Cursor::setPosition(INT2 position)
{
	INT2 screenSize = g_graphicsEngine->getRealScreenSize();
	this->m_sprite->setPosition(FLOAT2(((float)position.x / (float)screenSize.x) * 2 - 1, ((float)-position.y / (float)screenSize.y) * 2 + 1));
}

void Cursor::setFrame(CURSOR_TYPE cursor, int _priority)
{
	if(_priority >= this->m_priority)
	{
		int i = cursor;
		this->m_sprite->setCurrentFrame(INT2(i % 4, i / 4));
		this->m_priority = _priority;
	}
}

void Cursor::setPriority(int _priority)
{
	this->m_priority = _priority;
}