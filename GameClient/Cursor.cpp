#include "Cursor.h"

Cursor::Cursor()
{
	this->m_sprite = g_graphicsEngine->createSpriteSheet("MouseCursor.png", FLOAT2(0.0f, 0.0f), FLOAT2(0.1f, 0.1f), INT2(3, 1), 0);
}

void Cursor::setPosition(INT2 position)
{
	INT2 screenSize = g_graphicsEngine->getRealScreenSize();
	this->m_sprite->setPosition(FLOAT2(((float)position.x / (float)screenSize.x) * 2 - 1, ((float)-position.y / (float)screenSize.y) * 2 + 1));
}

void Cursor::setFrame(int i)
{
	this->m_sprite->setCurrentFrame(INT2(0, i));
}